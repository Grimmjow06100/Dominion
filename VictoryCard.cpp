//
// Created by Asus on 03/11/2024.
//

#include "VictoryCard.h"
#include <iostream>
#include "Jeux.h"
#include "Player.h"

VictoryCard::VictoryCard(std::string const&nom) : Card(normalize(nom),0), m_victory(0)
{
    if(m_nom=="DOMAINE")
    {
        m_cost=2;
        m_victory=1;
    }
    else if(m_nom=="DUCHE")
    {
        m_cost=5;
        m_victory=3;
    }
    else if(m_nom=="PROVINCE")
    {
        m_cost=8;
        m_victory=6;
    }
    else if(m_nom=="MALEDICTION")
    {
        m_cost=0;
        m_victory=-1;
    }
    else
        std::cerr<<"erreur la carte ne fait pas partie du jeu"<<std::endl;

}

VictoryCard::VictoryCard(VictoryCard const &card) : Card(card.m_nom,card.m_cost), m_victory(card.m_victory)
{}

void VictoryCard::affichage() const
{
    std::cout<<m_nom<<" "<<m_cost<<std::endl;
    std::cout<<"+ "<<m_victory<<" points de victoire"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}

int VictoryCard::getVictory() const {
    return m_victory;
}

void VictoryCard::action(Jeux &j) {
    Player &p=j.getActif();
    p.AddPoint(m_victory);
}