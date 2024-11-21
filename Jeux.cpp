//
// Created by Asus on 08/11/2024.
//
#include<iostream>
#include "Jeux.h"
#include "Player.h"
#include "Plateau.h"
#include "TreasureCard.h"
#include "VictoryCard.h"
#include <algorithm>
#include <random>
#include <cstdlib> // pour std::system
#include <iomanip>

/**
 * Constructeur vide
 */
Jeux::Jeux()
    : m_plateau(nullptr){}

/**
 * Destructeur vide
 */
Jeux::~Jeux()
{
    delete m_plateau;
    for (auto& player : m_players)
    {
        delete player;
    }
    m_players.clear();
}

/**
 * Reinitialise le terminal
 */
void clearTerminal() {
    std::system("cls");
}

/**
 * Initialise une partie avec les infos
 */
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
//pour les test
void Jeux::initGame(std::string nom1, std::string nom2)
{
    m_players.push_back(new Player(std::move(nom1)));
    m_players.push_back(new Player(std::move(nom2)));
    m_plateau = new Plateau(2);
    m_plateau->built();
    DistributeCards();

}


/**
 * Lance une partie de Dominion
 */
void Jeux::playGame(){
    clearTerminal();
    std::cout << std::endl << "Le jeu peut commencer ! Bonne chance a tous !" << std::endl;
    DistributeCards();
    playerBoard(m_players[actifIndex]);
    /*
    while(!m_plateau->isEmpty())
    {

    }
    */


}

/**
 * Distribue les cartes de departs aux joueurs
 */
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
    m_plateau->updateReserveByName("DOMAINE",3*static_cast<int>(m_players.size()));
    m_plateau->updateReserveByName("CUIVRE",7*static_cast<int>(m_players.size()));
}
/**
 * Affiche l'ecran de jeu du joueur (plateau,main,infos...)
 * @param player
 */
void Jeux::playerBoard(Player* player) const {
    clearTerminal();
    m_plateau->affichage();
    player->afficheHand();
    player->info();
}


void Jeux::actionPhase(Player* player)
{
    /*Phase d'action du joueur actif, il peut jouer autant de cartes actions qu'il le souhaite
    tant qu'il lui reste des actions*/

    //ne pas oublier d'afficher le playerBoard si nécessaire

}

void Jeux::buyPhase(Player* player)
{
    /*Phase d'achat du joueur actif, il peut acheter autant de cartes qu'il le souhaite
    tant qu'il lui reste des achats*/

    //ne pas oublier d'afficher le playerBoard si nécessaire
    //ne pas oublier de modifier la réserve de cartes du plateau

}

/**
 * Gere la fin d'un tour
 * @param player
 */
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

Plateau& Jeux::getPlateau() const
{
    return *m_plateau;
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
