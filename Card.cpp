//
// Created by Asus on 03/11/2024.
//
#include "Card.h"
#include <iostream>

#include "Jeux.h"

int Card::getCost() const
{
    return m_cost;
}

void Card::affichage()
{std::cout<<"This is a card"<<std::endl;}

void Card::action(Jeux &p)
{
    Player& player=p.getActif();
    player.pioche(2);
    std::cout<<"This is a card"<<std::endl;
}

