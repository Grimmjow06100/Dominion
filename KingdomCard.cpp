//
// Created by Asus on 03/11/2024.
//

#include "KingdomCard.h"
#include "Jeux.h"
#include "Reserve.h"
#include "Player.h"
#include "Plateau.h"
#include "GameCommand.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TreasureCard.h"



std::vector<KingdomCard> KingdomCard::DataCards;
std::map<std::string,KingdomCard> KingdomCard::KingdomCardMap;


KingdomCard::KingdomCard(std::string nom, int cost, bool attack, bool reaction, std::string description,int cards,int actions,int coins,int buys)
    :Card(std::move(nom),cost),m_attack(attack),m_reaction(reaction),m_description(std::move(description)),m_cards(cards),m_actions(actions),m_coins(coins),m_buys(buys)
{}
KingdomCard::KingdomCard()
    : Card("",0), m_attack(false), m_reaction(false),m_cards(0),m_actions(0),m_coins(0),m_buys(0)
{}
KingdomCard::KingdomCard(KingdomCard const&card)
    :Card(card.m_nom,card.m_cost),m_attack(card.m_attack),m_reaction(card.m_reaction),m_description(card.m_description),m_cards(card.m_cards),m_actions(card.m_actions),m_coins(card.m_coins),m_buys(card.m_buys)
{}

KingdomCard& KingdomCard::operator=(KingdomCard const& other) {
    if (this != &other) {  // Vérification d'auto-affectation
        m_nom = other.m_nom;
        m_cost = other.m_cost;
        m_attack = other.m_attack;
        m_reaction = other.m_reaction;
        m_description = other.m_description;
        m_cards = other.m_cards;
        m_actions = other.m_actions;
        m_coins = other.m_coins;
        m_buys = other.m_buys;
    }
    return *this;
}

void KingdomCard::affichage() const{
    std::string type=actionType(*this);
    std::cout << "\033[31m+--------------+\033[0m\n";
    std::cout << "\033[31m|\033[0m " << std::setw(13) << std::left << m_nom << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Type: " << std::setw(7) << type << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Cout: " << std::setw(7) << m_cost << "\033[31m|\033[0m\n";
    std::cout << "\033[31m+--------------+\033[0m\n";
}

void KingdomCard::details()const
{
    std::string type=actionType(*this);
    std::cout<<"Nom : "<<m_nom<<std::endl;
    std::cout<<"Type : "<<type<<std::endl;
    std::cout<<"Cout : "<<m_cost<<std::endl;
    std::cout<<"Description : "<<m_description<<std::endl;
}

std::string KingdomCard::actionType(KingdomCard const&k)
{

    if(k.isAttack())
    {
        return "ACTION-ATTAQUE";
    }
    if(k.isReaction())
    {
        return "ACTION-REACTION";
    }
    if(k.getNom()== "JARDINS")
    {
        return "VICTOIRE";
    }
    return "ACTION";

}

void KingdomCard::action(Jeux &j)
{

    std::cout<<"Vous avez joue la carte "<<m_nom<<std::endl;
    Player& player=j.getActifPlayer();
    player.AddAction(m_actions);
    std::cout<<"Vous avez gagne "<<m_actions<<" actions"<<std::endl;
    player.AddCoin(m_coins);
    std::cout<<"Vous avez gagne "<<m_coins<<" pieces"<<std::endl;
    player.AddBuy(m_buys);
    std::cout<<"Vous avez gagne "<<m_buys<<" achats"<<std::endl;
    player.pioche(m_cards);
    std::cout<<"Vous avez pioche "<<m_cards<<" cartes"<<std::endl;
    if(m_nom=="ATELIER")
    {
        Atelier(j);
    }
    else if(m_nom=="CAVE")
    {

        Cave(j);
    }
    else if(m_nom=="JARDINS")
    {
        Jardins(player);
    }
    else if(m_nom=="BANDIT")
    {
        Bandit(j);
    }
    else if(m_nom=="SORCIERE")
    {
        Sorciere(j);
    }
    else if(m_nom=="CHAPELLE")
    {
        Chapelle(j);
    }


}


void KingdomCard::GenerateKingdomFromFile(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);

    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << nomFichier << std::endl;

    }

    std::string ligne;
    std::string nom;
    int cout;
    bool attack;
    bool reaction;
    std::string description;
    int cards;
    int actions;
    int coins;
    int buys;

    int ligneCompteur=0;

    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) {
            // Créer une nouvelle carte quand une ligne vide est rencontrée
            if (!nom.empty() && !description.empty() ) {
                DataCards.emplace_back(normalize(nom),cout,attack,reaction,description,cards,actions,coins,buys);
                KingdomCardMap[normalize(nom)] = KingdomCard(normalize(nom), cout, attack, reaction, description,cards,actions,coins,buys);
            }
            ligneCompteur = 0;
        } else {
            switch (ligneCompteur) {
            case 0: nom = ligne; break;
            case 1: cout = std::stoi(ligne); break;
            case 2: if(ligne=="true") attack=true; else attack=false; break;
            case 3: if(ligne=="true") reaction=true;else reaction=false;break;
            case 4:cards=std::stoi(ligne);break;
            case 5:actions=std::stoi(ligne);break;
            case 6:coins=std::stoi(ligne);break;
            case 7:buys=std::stoi(ligne);break;
            case 8: description=ligne;break;
            default: break;
            }
            ligneCompteur++;
        }
    }

    // Ajouter la dernière carte si elle n'est pas vide
    if (!nom.empty() && !description.empty()) {
        DataCards.emplace_back(normalize(nom),cout,attack,reaction,description,cards,actions,coins,buys);
        KingdomCardMap[normalize(nom)] = KingdomCard(normalize(nom), cout, attack, reaction, description,cards,actions,coins,buys);
    }
    fichier.close();
}

void KingdomCard::Atelier(Jeux const&j)
{
    Plateau& p=j.getPlateau();
    Player& player=j.getActifPlayer();
    std::string nom;
    std::string message="Gagnez une carte coutant jusqu'a 4 pieces (commande : pick [nomCarte])";
    std::cout<<message<<std::endl;
    std::string card;
    bool valid(false);
    do
    {
        card.clear();
        GameCommand<std::string>::getInput(j,card,nullptr,false,message);
        if(!card.empty()&&player.gainCard(card,p,0,4))
        {
            valid=true;
        }
        else
            std::cout<<"La carte n'existe pas ou est trop chere ";
    }while(card.empty() || !valid);

}

void KingdomCard::Chapelle(Jeux const& j)
{
    Player &p=j.getActifPlayer();

    int size=static_cast<int>(j.getActifPlayer().getHand().size());
    j.getActifPlayer().afficheHand();
    std::string message="Trashing jusqu'a 4 cartes de votre main (commande : pick [nomCarte])";
    std::cout<<message<<std::endl;
    int count(1);
    bool* exit=new bool(false);
    std::string card;
    while (count<=4){
        card.clear();
        std::cout<<"Carte "<<count<<" ";
        GameCommand<std::string>::getInput(j,card,exit,false,message);
        if(!card.empty()&&p.trashCardFromHand(card))
        {
            count++;
        }
        if (count==size)
        {
            std::cout<<"Vous avez trasher toutes vos cartes"<<std::endl;
            break;
        }
        if(*exit)
            break;
    }
}

void KingdomCard::Sorciere(Jeux const&j)
{
    Player &p=j.getActifPlayer();
    for(auto &joueur:j.getPlayers())
    {
        if(joueur->getName()!=p.getName())
        {
            // Réaction à l'attaque
            int index;
            if (joueur->ReactTo(index))
            {
                std::cout << "Le joueur " << joueur->getName()
                          << " annule votre attaque avec la carte "
                          << joueur->getHand().at(index)->getNom() << std::endl;
                continue;
            }
            std::cout<<"Le joueur "<<joueur->getName()<<" a gagne une malediction "<<std::endl;
            joueur->gainCard("MALEDICTION",j.getPlateau());

        }
    }
}

void KingdomCard::Cave(Jeux const& j)
{
    Player &p=j.getActifPlayer();
    int size=static_cast<int>(p.getHand().size());
    p.afficheHand();
     std::string message="Defaussez autant de cartes que vous voulez (commande : pick [nomCarte])";
    std::cout<<message<<std::endl;
    int count(1);
    bool* exit=new bool(false);
    std::string card;
    while(count<=size){
        card.clear();
        std::cout<<"Carte "<<count<<" ";
        GameCommand<std::string>::getInput(j,card,exit,false,message);
        if(!card.empty()&& p.defausseFromHand(card)){
            count++;
        }
        if(*exit)
            break;
    }
    std::cout<<"Vous piochez "<<count<<" cartes"<<std::endl;
    p.pioche(count);
}

void KingdomCard::Jardins(Player& p)
{
    int point=static_cast<int>(p.getDeck().size())/10;
    p.AddPoint(point);
}
void KingdomCard::Bandit(Jeux const&j)
{
    // 1. Le joueur actif gagne une carte Or
    Player& actif = j.getActifPlayer();
    actif.gainCard("OR", j.getPlateau());

    // 2. Pour chaque autre joueur
    for (auto& joueur : j.getPlayers())
    {
        if (joueur->getName() != actif.getName()) // Ignorer le joueur actif
        {
            // Réaction à l'attaque
            int index;
            if (joueur->ReactTo(index))
            {
                std::cout << "Le joueur " << joueur->getName()
                          << " annule votre attaque avec la carte "
                          << joueur->getHand().at(index)->getNom() << std::endl;
                continue;
            }
            // Révéler les deux premières cartes du deck
            std::vector<Card*> revealedCards;
            for (int i = 0; i < 2 && !joueur->getDeck().empty(); ++i)
            {
                revealedCards.push_back(joueur->drawCard());
            }

            std::cout << "Le joueur " << joueur->getName() << " revele : ";
            for (auto* card : revealedCards)
                std::cout << card->getNom() << " ";
            std::cout << std::endl;

            // Chercher une carte Trésor non-Cuivre à trasher
            bool trashed = false;
            for (auto it = revealedCards.begin(); it != revealedCards.end(); ++it)
            {
                auto* treasureCard = dynamic_cast<TreasureCard*>(*it);
                if (treasureCard && treasureCard->getNom() != "CUIVRE")
                {
                    std::cout << "Le joueur " << joueur->getName()
                              << " trashe la carte : " << treasureCard->getNom() << std::endl;
                    Player::trashCard(*it);
                    revealedCards.erase(it);
                    trashed = true;
                    break;
                }
            }

            if (!trashed)
            {
                std::cout << "Le joueur " << joueur->getName()
                          << " n'a pas de carte Tresor non-Cuivre a trasher " << std::endl;
            }
            // Défausser les cartes restantes
            joueur->defausseArray(revealedCards);
        }
    }
}


int KingdomCard::getActions() const
{
    return m_actions;
}
int KingdomCard::getCards()const
{
    return m_cards;
}

bool KingdomCard::isAttack() const
{
    return m_attack;
}

bool KingdomCard::isReaction() const
{
    return m_reaction;
}

int KingdomCard::getCoins() const
{
    return m_coins;
}

int KingdomCard::getBuys() const
{
    return m_buys;
}

std::string KingdomCard::getDescription() const
{
    return m_description;
}
