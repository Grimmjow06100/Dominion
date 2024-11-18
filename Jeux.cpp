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
    std::cout << std::endl << "Le jeu peut commencer ! Bonne chance a tous !" << std::endl;
    //à faire : distribuer les cartes de départ et commencer la partie
    for (auto* player : m_players)
    {
        //mélange du deck de départ
        player->shuffle();
        //pioche de 5 cartes
        player->pioche(5);
    }
    /*while(//condition de fin de partie)
    {
        Player* actif = m_players[actifIndex];
        actionPhase(actif);
        buyPhase(actif);
        endTurn(actif);
    }
    //ne pas oublier de compter les points et de déclarer le vainqueur
    //ne pas oublier l'affichage du plateau de jeu si besoin en fonction de l'évolution du jeu
    */

}

void Jeux::playerBoard(Player* player)
{
    /*affiche la main du joueur actif , les cartes qu'il a joué,son nombre d'actions restantes,d'achats
    ,de pièces etc...Toute les informations necessaires pour le joueur actif*/

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

void Jeux::endTurn(Player* player)
{
    /*Fin du tour du joueur actif
     effectue les actions de fin de tour (défausse de la main et des cartes jouées, pioche de 5 cartes)
     et on passe au joueur suivant
     */
    actifIndex = (actifIndex + 1) % m_players.size();
    //ne pas oublier de réinitialiser les actions, achats et pièces du joueur actif

}


std::vector<Player*>Jeux::getPlayers()const
{
    return m_players;
}

Player& Jeux::getActif() const
{
    return *m_players.at(actifIndex);
}

int Jeux::getActifIndex() const
{
    return actifIndex;
}
