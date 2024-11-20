//
// Created by Asus on 08/11/2024.
//
#include<iostream>
#include "Jeux.h"
#include <algorithm>
#include <random>
#include <cstdlib> // pour std::system
#include <iomanip>

Jeux::Jeux()
    : m_plateau(nullptr){}

Jeux::~Jeux()
{
    delete m_plateau;
    for (auto& player : m_players)
    {
        delete player;
    }
    m_players.clear();
}

void clearTerminal() {
    std::system("cls");
}

void Jeux::initGame() {
    std::cout << "Bienvenue dans le jeu Dominion !" << std::endl;

    int nbJoueurs = 0;

    // Demande le nombre de joueurs (entre 2 et 4)
    while (nbJoueurs < 2 || nbJoueurs > 4) {
        std::cout << "Combien etes-vous de joueurs ? (entre 2 et 4) : ";
        std::cin >> nbJoueurs;
        if (nbJoueurs < 2 || nbJoueurs > 4) {
            std::cout <<std::endl<< "Le nombre de joueurs doit etre entre 2 et 4 !" << std::endl;
        }
    }

    std::string nom;

    // Demande les noms des joueurs
    std::cout <<std::endl<< "Entrez les noms des " << nbJoueurs << " joueurs :" << std::endl;
    for (int i = 0; i < nbJoueurs; ++i) {
        std::cout << "Nom du joueur " << i + 1 << " : ";
        std::cin >> nom;
        m_players.push_back(new Player(nom));
    }

    // Mélange aléatoire de l'ordre des joueurs
    std::random_device rd;  // Génère une graine aléatoire
    std::mt19937 g(rd());   // Générateur Mersenne Twister
    std::shuffle(m_players.begin(),m_players.end(), g);

    //creation du plateau de jeu
    m_plateau = new Plateau(nbJoueurs);
    m_plateau->built();
}

void Jeux::playGame(){
    clearTerminal();
    std::cout << std::endl << "Le jeu peut commencer ! Bonne chance a tous !" << std::endl;
    DistributeCards();
    this->playerBoard(m_players[actifIndex]);
    for(int i=0;i<10;i++) {
        actifIndex = (actifIndex + 1)%(m_players.size());//maj du joueur qui joue
    }
    /*
    while(!m_plateau->isEmpty())
    {


       actifIndex = (actifIndex + 1)%(m_players.size());
    }*/



}

void Jeux::DistributeCards()
{
    std::vector<Card*> deck;
    for(auto i=0;i<10;i++)
    {
        if(i<7)
        {
            deck.push_back(new TreasureCard("CUIVRE"));

        }
        else
        {
            deck.push_back(new VictoryCard("DOMAINE"));
        }
    }
    for (auto* player : m_players)
    {
        //attribution du deck de départ
        player->setDeck(deck);
        //mélange du deck de départ
        player->shuffle();
        //pioche de 5 cartes
        player->pioche(5);

    }
    //mise à jour de la réserve de cartes
    m_plateau->updateReserve("DOMAINE",3*static_cast<int>(m_players.size()));
    m_plateau->updateReserve("CUIVRE",7*static_cast<int>(m_players.size()));
}

void Jeux::afficheMain(Player* player) {
    if (!player) {
        std::cerr << "Erreur : joueur invalide." << std::endl;
        return;
    }

    constexpr int maxCartesParLigne = 5;  // Maximum de cartes par ligne
    const auto& main = player->getHand(); // Récupérer la main du joueur

    std::cout << "______________________________________ MAIN DU JOUEUR ________________________________________" << std::endl;

    // Stockage temporaire des cartes avec leurs informations
    std::vector<std::tuple<std::string, int, std::string, std::string>> cartes;

    for (const auto& card : main) {
        if (card) { // Vérifiez que la carte n'est pas nulle
            std::string type;
            std::string extraInfo;
            std::string colorCode;

            if (dynamic_cast<KingdomCard*>(card)) {
                type = "Royaume";
                extraInfo = "FONCTION";
                colorCode = "\033[34m";  // Bleu pour Royaume
            } else if (auto* treasureCard = dynamic_cast<TreasureCard*>(card)) {
                type = "Tresor";
                extraInfo = "+" + std::to_string(treasureCard->getTreasure());
                colorCode = "\033[33m";  // Jaune pour Trésor
            } else if (auto* victoryCard = dynamic_cast<VictoryCard*>(card)) {
                type = "Victoire";
                extraInfo = "+" + std::to_string(victoryCard->getVictory());
                colorCode = "\033[32m";  // Vert pour Victoire
            } else {
                type = "Inconnu";
                extraInfo = "N/A";
                colorCode = "\033[0m";  // Réinitialiser pour inconnu
            }

            cartes.emplace_back(colorCode + card->getNom() + "\033[0m", card->getCost(), type, extraInfo);
        }
    }

    // Affichage des cartes
    const size_t totalCartes = cartes.size();

    for (size_t i = 0; i < totalCartes; i += maxCartesParLigne) {
        // Bordures supérieures des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m+--------------+\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le nom des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(22) << std::left
                      << std::get<0>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le type des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m Type:" << std::setw(8) << std::left
                      << std::get<2>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le coût des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m Cout: " << std::setw(7) << std::left
                      << std::get<1>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant les informations supplémentaires
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(13) << std::left
                      << std::get<3>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Bordures inférieures des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m+--------------+\033[0m  ";
        }
        std::cout << std::endl << std::endl;  // Espace entre les rangées de cartes
    }
}

void Jeux::playerBoard(Player* player)
{
    clearTerminal();
    m_plateau->affichePlateau();
    Jeux::afficheMain(player);
    /*affiche la main du joueur actif , les cartes qu'il a joué,son nombre d'actions restantes,d'achats
    ,de pièces etc...Toute les informations necessaires pour le joueur actif*/

}

void Jeux::actionPhase(Player* player)
{
    std::cout<<player->getActions();//juste pour compiler
    /*Phase d'action du joueur actif, il peut jouer autant de cartes actions qu'il le souhaite
    tant qu'il lui reste des actions*/

    //ne pas oublier d'afficher le playerBoard si nécessaire

}

void Jeux::buyPhase(Player* player)
{
    std::cout<<player->getActions();//juste pour compiler
    /*Phase d'achat du joueur actif, il peut acheter autant de cartes qu'il le souhaite
    tant qu'il lui reste des achats*/

    //ne pas oublier d'afficher le playerBoard si nécessaire
    //ne pas oublier de modifier la réserve de cartes du plateau

}

void Jeux::endTurn(Player* player)
{
    /*Fin du tour du joueur actif
     effectue les actions de fin de tour (défausse de la main et des cartes jouées, pioche de 5 cartes)
     et on passe au joueur suivant
     */
    size_t range=m_players.size();
    actifIndex = (actifIndex + 1) % range;
    player->reset();

}


std::vector<Player*>Jeux::getPlayers()const
{
    return m_players;
}

Player& Jeux::getActif() const
{
    return *m_players.at(actifIndex);
}

size_t Jeux::getActifIndex() const
{
    return actifIndex;
}
