//
// Created by Asus on 08/11/2024.
//
#include<iostream>
#include "Jeux.h"
#include "Player.h"
#include "Plateau.h"
#include "TreasureCard.h"
#include "VictoryCard.h"
#include "KingdomCard.h"
#include <algorithm>
#include <random>
#include <cstdlib> // pour std::system
#include <iomanip>

#include "GameCommand.h"

/**
 * Constructeur vide
 */
Jeux::Jeux()
    : m_plateau(nullptr),actifIndex(0){}

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
    std::ranges::shuffle(m_players.begin(),m_players.end(), g);

    //creation du plateau de jeu
    m_plateau = new Plateau(nbJoueurs);
    m_plateau->built();


}
//pour les test
void Jeux::initGame(std::string const&nom1, std::string const&nom2)
{
    m_players.push_back(new Player(nom1));
    m_players.push_back(new Player(nom2));
    m_plateau = new Plateau(2);
    m_plateau->built();

}


/**
 * Lance une partie de Dominion
 */
void Jeux::playGame(){
    clearTerminal();
    std::cout << std::endl << "Le jeu peut commencer ! Bonne chance a tous !" << std::endl;
    DistributeCards();
    while(!m_plateau->isEmpty())
    {
        for(auto* player : m_players)
        {
            setPlayer(player);
            playerBoard(player);
            actionPhase(player);
            buyPhase(player);
            endTurn(player);
        }
    }



}

void Jeux::endGame()
{
    //calcul des point bonus pour les cartes JARDINS
    for(auto player:m_players)
    {
        player->defausseAll();
        for(auto it:player->getDefausse())
        {
            if(auto* k=dynamic_cast<KingdomCard*>(it))
            {
                if(k->getNom()=="JARDINS")
                {
                    k->action(*this);
                }
            }
        }
    }
    //affichage des scores
    std::cout<<"Fin de la partie"<<std::endl;

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
void Jeux::playerBoard(const Player* player) const {
    clearTerminal();
    m_plateau->affichage();
    player->afficheHand();
    player->info();
}


void Jeux::actionPhase(Player* player)
{
    //Phase d'action du joueur actif
    std::cout<<std::endl<<"Phase d'action pour le joueur "<<player->getName()<<std::endl;
    bool* exit=new bool(false);
    std::string consigne ="Jouez une carte action ou passez a la phase d'achat ";
    while(player->canPlayAction()&&!*exit)
    {
        GameCommand::getInput(*this,ACTION,exit,consigne);
    }
    std::cout<<"Fin de la phase d'action"<<std::endl;
    delete exit;

}

void Jeux::buyPhase(Player* player)
{
    //Phase d'achat du joueur actif
    std::cout<<std::endl<<"Phase d'achat pour le joueur "<<player->getName()<<std::endl;
    bool* exit=new bool(false);
    std::string consigne="Achetez/Vendez une ou plusieurs cartes ou passez au tour suivant";
    while(player->canBuy()&&!*exit)
    {
        GameCommand::getInput(*this,BUY,exit,consigne);
    }
    std::cout<<"Fin de la phase d'achat"<<std::endl;
    delete exit;

}

/**
 * Gere la fin d'un tour
 * @param player
 */
void Jeux::endTurn(Player* player)
{
    size_t range=m_players.size();
    actifIndex = (actifIndex + 1) % range;
    std::cout<<std::endl<<"Fin du tour pour le joueur "<<player->getName()<<std::endl;
    std::cout<<"Passage au joueur "<<m_players.at(actifIndex)->getName()<<std::endl;
    player->defausseAll();
    player->pioche(5);

}

void Jeux::setPlayer(Player* player)
{
    player->setActions(1);
    player->setBuys(1);
    player->setCoins(0);
}

Plateau& Jeux::getPlateau() const
{
    return *m_plateau;
}


std::vector<Player*>Jeux::getPlayers()const
{
    return m_players;
}

Player& Jeux::getActifPlayer() const
{
    return *m_players.at(actifIndex);
}

size_t Jeux::getActifIndex() const
{
    return actifIndex;
}
