//
// Created by Asus on 03/11/2024.
//

#include "KingdomCard.h"
#include "Jeux.h"
#include <iostream>
#include <fstream>
#include "CardStream.h"



std::vector<KingdomCard> KingdomCard::DataCards;
std::map<std::string,KingdomCard> KingdomCard::KingdomCardMap;


KingdomCard::KingdomCard(std::string nom, int cost, bool attack, bool reaction, std::string description,int cards,int actions,int coins,int buys)
    :Card(std::move(nom),cost),m_attack(attack),m_reaction(reaction),m_description(std::move(description)),m_cards(cards),m_actions(actions),m_coins(coins),m_buys(buys)
{}
KingdomCard::KingdomCard()
    : Card("",0), m_attack(false), m_reaction(false), m_description(""),m_cards(0),m_actions(0),m_coins(0),m_buys(0)
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


void KingdomCard::affichage()
{
    std::cout<<normalize(m_nom)<<" "<<m_cost<<std::endl;
    std::cout<<m_description<<std::endl;
    if(m_attack)
    {
        std::cout<<"ACTION-ATTAQUE"<<std::endl;
    }
    else if(m_reaction)
    {
        std::cout<<"ACTION-REACTION"<<std::endl;
    }
    else if(normalize(m_nom)== "JARDINS")
    {
        std::cout<<"VICTOIRE"<<std::endl;
    }
    else
        std::cout<<"ACTION"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}

std::string KingdomCard::getNom() const
{
    return m_nom;
}

void KingdomCard::action(Jeux &j)
{

    Player& player=j.getActif();
    player.setActions(player.getActions()+m_actions);
    player.pioche(m_cards);
    player.setCoins(player.getCoins()+m_coins);
    player.setBuys(player.getBuys()+m_buys);


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
                KingdomCardMap[normalize(nom)] = KingdomCard(nom, cout, attack, reaction, description,cards,actions,coins,buys);
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
        KingdomCardMap[normalize(nom)] = KingdomCard(nom, cout, attack, reaction, description,cards,actions,coins,buys);
    }
    fichier.close();
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
