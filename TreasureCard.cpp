//
// Created by Asus on 03/11/2024.
//

#include "TreasureCard.h"

#include <iostream>


TreasureCard::TreasureCard( Treasure treasure) :  m_treasure(treasure)
{
    if(m_treasure == CUIVRE)
    {
        m_cost = 0;
    }
    else if(m_treasure == ARGENT)
    {
        m_cost = 3;
    }
    else if(m_treasure == OR)
    {
        m_cost = 6;
    }
}
void TreasureCard::affichage()
{
    switch (m_treasure)
    {
        case CUIVRE:
            std::cout<<"CUIVRE "<<m_cost<<std::endl;
            break;
        case ARGENT:
            std::cout<<"ARGENT "<<m_cost<<std::endl;
            break;
        case OR:
            std::cout<<"OR "<<m_cost<<std::endl;
            break;
    }
}

Treasure TreasureCard::getTreasure() const
{
    return m_treasure;
}

void TreasureCard::action(Player &p)
{
    p.setMoney(p.getMoney()+m_treasure);
}
