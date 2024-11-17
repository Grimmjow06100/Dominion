//
// Created by Asus on 03/11/2024.
//

#include "TreasureCard.h"

#include <iostream>

#include "Player.h"
#include "Jeux.h"


TreasureCard::TreasureCard(std::string const&nom) :  Card(normalize(nom),0),m_treasure(0)
{
    if(m_nom=="CUIVRE")
    {
        m_cost = 0;
        m_treasure = 1;
    }
    else if( m_nom == "ARGENT")
    {
        m_cost = 3;
        m_treasure = 2;
    }
    else if(m_nom == "OR")
    {
        m_cost = 6;
        m_treasure = 3;
    }
    else
        std::cerr<<"erreur la carte ne fait pas partie du jeu"<<std::endl;
}

TreasureCard::TreasureCard(TreasureCard const& card):Card(card.m_nom,card.m_cost),m_treasure(card.m_treasure)
{}

int TreasureCard::getTreasure() const
{
    return m_treasure;
}


void TreasureCard::affichage()
{

    std::cout<<m_nom<<" "<<m_cost<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}



void TreasureCard::action(Jeux &j)
{
    Player &p=j.getActif();
    p.setCoins(p.getCoins()+m_treasure);

}
