//
// Created by Asus on 08/11/2024.
//
#include<iostream>
#include "Jeux.h"
#include <algorithm>
#include <random>

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

void Jeux::initGame() {
    std::cout <<std::endl<<std::endl<< "Bienvenue dans le jeu Dominion !" << std::endl;

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
    std::cout << std::endl << "Le jeu peut commencer ! Bonne chance a tous !" << std::endl;
    DistributeCards();
    m_plateau->affichePlateau();
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
    std::cout<<player->getActions();//juste pour compiler
}

void Jeux::playerBoard(Player* player)
{

    std::cout<<player->getActions();//juste pour compiler
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
