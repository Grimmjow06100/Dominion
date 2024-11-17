//
// Created by Asus on 08/11/2024.
//
#include<iostream>
#include "Jeux.h"
#include <algorithm>
#include <random>

Jeux::Jeux(Plateau plateau, const std::vector<Player*>& players, int actifIndex)
    : m_plateau(std::move(plateau)), m_players(players), actifIndex(actifIndex) {}

Jeux Jeux::initGame() {
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

    std::vector<Player*>players;
    std::string nom;

    // Demande les noms des joueurs
    std::cout <<std::endl<< "Entrez les noms des " << nbJoueurs << " joueurs :" << std::endl;
    for (int i = 0; i < nbJoueurs; ++i) {
        std::cout << "Nom du joueur " << i + 1 << " : ";
        std::cin >> nom;
        players.push_back(new Player(nom));
    }

    // Mélange aléatoire de l'ordre des joueurs
    std::random_device rd;  // Génère une graine aléatoire
    std::mt19937 g(rd());   // Générateur Mersenne Twister
    std::ranges::shuffle(players, g);

    // Affiche l'ordre aléatoire des joueurs
    std::cout << std::endl << "L'ordre des joueurs est le suivant : " << std::endl;
    for (size_t i = 0; i < players.size(); ++i) {
        std::cout << "Joueur " << i + 1 << " : " << players[i]->getName() << std::endl;
    }

    //creation du plateau de jeu
    auto plateau = Plateau(nbJoueurs);
    plateau.built();

    //creation du jeu
    auto jeux = Jeux(plateau,players,0);
    return(jeux);
}

void Jeux::playGame(){
    std::cout << std::endl << "Le jeu peut commencer ! Bonne chance a tous !" << std::endl;
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
