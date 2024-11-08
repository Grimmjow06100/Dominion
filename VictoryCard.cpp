//
// Created by Asus on 03/11/2024.
//

#include "VictoryCard.h"
#include <iostream>
#include "Jeux.h"
#include "Player.h"

VictoryCard::VictoryCard(Victory victory) :  m_victory(victory)
{
    if(m_victory==DOMAINE)
        m_cost=2;
    else if(m_victory==DUCHE)
        m_cost=5;
    else if(m_victory==PROVINCE)
        m_cost=8;
    else if(m_victory==MALÉDICTION)
        m_cost=0;

}

void VictoryCard::affichage()
{
    switch (m_victory){
        case (DOMAINE):
            std::cout << "DOMAINE "<<m_cost<< std::endl;
            break;
        case DUCHE:
            std::cout<<"DUCHE "<<m_cost<<std::endl;
            break;
        case PROVINCE:
            std::cout<<"PROVINCE "<<m_cost<<std::endl;
            break;
        case MALÉDICTION:
            std::cout<<"MALEDICTION "<<m_cost<<std::endl;
            break;

    }
}

Victory VictoryCard::getVictory() const {
    return m_victory;
}

void VictoryCard::action(Jeux &j) {
    Player &p=j.getActif();
    p.setPoints(p.getPoints()+m_victory);
}