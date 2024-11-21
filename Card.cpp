//
// Created by Asus on 03/11/2024.
//
#include "Card.h"
#include <algorithm>
#include <iostream>



Card::Card(std::string nom,int cost):m_nom(std::move(nom)),m_cost(cost){};
int Card::getCost() const
{
    return m_cost;
}

// Normalisation de la chaine de caractères (majuscule)
std::string normalize(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res;
}

std::string Card::getNom() const
{
    return m_nom;
}

