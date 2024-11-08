//
// Created by Asus on 03/11/2024.
//

#include "Reserve.h"


Reserve::Reserve(Card const&card,int taille):m_card(card),m_taille(taille){}

bool Reserve::isEmpty() const {
    return (m_taille==0);
}

Card Reserve::getCard() const {
    return m_card;
}

int Reserve::getTaille() const {
    return m_taille;
}

void Reserve::setTaille(int taille) {
    m_taille=taille;
}
