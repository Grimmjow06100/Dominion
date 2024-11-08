//
// Created by Asus on 03/11/2024.
//
#include "Card.h"
#include <iostream>
int Card::getCost() const
{
    return m_cost;
}

void Card::affichage()
{std::cout<<"This is a card"<<std::endl;}

void Card::action(Player &p)
{
    std::cout<<"This is a card"<<std::endl;
}

