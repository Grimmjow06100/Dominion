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
#include <set>

#include "GameCommand.h"






const std::string BLUE_TEXT = "\033[1;34m";  // Couleur bleu
const std::string BLINK_TEXT = "\033[5m";   // Texte clignotant
const std::string RESET_TEXT = "\033[0m";   // Réinitialisation des styles


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
    std::cout << std::endl << "/////////////////////////// BIENVENUE DANS LE JEU DU DOMINION //////////////////////////////////" << std::endl;

    int nbJoueurs = 0;

    // Demande le nombre de joueurs (entre 2 et 4)
    std::cout << "Choisissez le nombre de joueur (2-4) > ";
    while (nbJoueurs < 2 || nbJoueurs > 4) {
        std::cin >> nbJoueurs;
        if (nbJoueurs < 2 || nbJoueurs > 4) {
            std::cout <<std::endl<< "Le nombre de joueurs doit etre entre 2 et 4 ! > " ;
        }
    }

    std::string nom;

    // Demande les noms des joueurs
    for (int i = 0; i < nbJoueurs; ++i) {
        std::cout << "Nom du joueur " << i + 1 << " > ";
        std::cin >> nom;
        m_players.push_back(new Player(nom));
    }

    // Mélange aléatoire de l'ordre des joueurs
    std::random_device rd;  // Génère une graine aléatoire
    std::mt19937 g(rd());   // Générateur Mersenne Twister
    std::ranges::shuffle(m_players.begin(),m_players.end(), g);

    std::vector<std::string> royaume;
    royaume.insert(royaume.end(),BaseBoard.begin(),BaseBoard.end());
    royaume.insert(royaume.end(),bonus.begin(),bonus.end());

    std::cout<<"Voulez-vous choisir les cartes du royaume ? (Y/N) > ";
    std::string choix;
    while(choix!="Y"&&choix!="N")
    {
        std::cin>>choix;
        if(normalize(choix)=="Y")
        {
            //creation du plateau de jeu
            m_plateau = new Plateau(nbJoueurs);
            std::vector<std::string> reserve=choisirDixElements(royaume);
            m_plateau->built(reserve);
            break;
        }
        if(normalize(choix)=="N")
        {
            //creation du plateau de jeu
            m_plateau = new Plateau(nbJoueurs);
            m_plateau->built();
            break;
        }
        std::cout<<"Entrée invalide, veuillez entrer (Y/N) > ";
    }

    std::cin.ignore();


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
    DistributeCards();
    while(!m_plateau->isEmpty())
    {
        Player* player = m_players.at(actifIndex);
        setPlayer(player);
        actionPhase(player);
        buyPhase(player);
        endTurn(player);
        if(m_plateau->isEmpty()) {
            break;
        }
    }
    endGame();
}

void Jeux::endGame()
{
    //calcul des point bonus pour les cartes JARDINS
    for(auto player:m_players)
    {
        player->defausseAll();
        auto it=std::ranges::find_if(player->getDefausse().begin(),player->getDefausse().end(),[](const Card* c)
        {
            return c->getNom()=="JARDINS";
        });
        if(it!=player->getDefausse().end())
        {
            auto k=dynamic_cast<KingdomCard*>(*it);
            k->action(*this);
        }
    }
    //affichage des scores
    clearTerminal();
    afficheClassement();

}

void Jeux::afficheClassement() const {
    std::vector<Player*> sortedPlayers = m_players; // Copie des joueurs pour ne pas modifier l'ordre original

    // Trie les joueurs par points décroissants
    std::ranges::sort(sortedPlayers.begin(), sortedPlayers.end(), [](const Player* a, const Player* b) {
        return a->getPoints() > b->getPoints(); // Trie par points décroissants
    });

    std::cout << "-----------------------CLASSEMENT-----------------------" << std::endl;

    int rank = 1; // Classement initial
    for (auto player : sortedPlayers) {
        std::cout <<std::setw(14) << rank << " - " << player->getName() << " (" << player->getPoints() << " points)" << std::endl;
        ++rank;
    }
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

    playerBoard(player);
    phaseMessage(ACTION);
    bool exit(false);
    while(player->canPlayAction()&&!exit)
    {
        GameCommand::getInput(*this,ACTION,&exit);
    }
    std::cout<<"Fin de la phase d'action, passage a la phase d'achat"<<std::endl;
    appuyerPourContinuer();

}

void Jeux::buyPhase(Player* player)
{
    playerBoard(player);
    phaseMessage(BUY);
    bool exit(false);
    while(player->canBuy()&&!exit)
    {
        GameCommand::getInput(*this,BUY,&exit);
    }
    std::cout<<"Fin de la phase d'achat, le prochain joueur est "<<m_players[(actifIndex + 1) % m_players.size()]->getName()<<std::endl;
    appuyerPourContinuer();

}
void Jeux::phaseMessage(Phase phase)
{
    if(phase==ACTION)
    {
        std::cout << BLUE_TEXT << BLINK_TEXT
                  << "Jouez des cartes actions (-> play [nomCarte] )"
                  << RESET_TEXT << std::endl;
    }
    else if(phase==BUY)
    {
        std::cout << BLUE_TEXT << BLINK_TEXT
                 << "Achetez des cartes (-> buy [nomCarte] ou sell [nomCarte])"
                 << RESET_TEXT << std::endl;
    }
    else
        std::cout<<"Phase inconnue"<<std::endl;

    std::cout<<std::endl;
}

/**
 * Gere la fin d'un tour
 * @param player
 */
void Jeux::endTurn(Player* player)
{
    actifIndex = (actifIndex + 1) % m_players.size();
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

std::vector<std::string> choisirDixElements(const std::vector<std::string>& options) {
    if (options.size() < 10) {
        throw std::runtime_error("Le vecteur contient moins de 10 éléments. Impossible de choisir.");
    }

    std::vector<std::string> choix;
    std::set<int> indicesChoisis; // Pour éviter les doublons
    int choixUtilisateur = -1;

    std::cout << "Veuillez choisir 10 éléments parmi les cartes suivantes (entrez 0 pour quitter) : \n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << " " << options[i] << "\n"; // Affichage avec index (1-based)
    }

    while (choix.size() < 10) {
        std::cout << "\nChoix " << choix.size() + 1 << "> "<<std::endl;
        std::cin >> choixUtilisateur;
        if(choixUtilisateur==0)
            return std::vector<std::string>();

        if (std::cin.fail()) {
            std::cin.clear(); // Réinitialise l'état d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore la ligne courante
            std::cout << "Entrée invalide. Veuillez entrer un numéro valide.\n";
            continue;
        }

        // Ajuster l'index de 1-based à 0-based
        choixUtilisateur -= 1;

        if (choixUtilisateur < 0 || choixUtilisateur >= static_cast<int>(options.size())) {
            std::cout << "Numéro invalide. Veuillez choisir un numéro entre 1 et " << options.size() << ".\n";
        } else if (indicesChoisis.find(choixUtilisateur) != indicesChoisis.end()) {
            std::cout << "Vous avez déjà choisi cet élément. Veuillez en choisir un autre.\n";
        } else {
            choix.push_back(options[choixUtilisateur]);
            indicesChoisis.insert(choixUtilisateur);
        }
    }
    return choix;
}
