//
// Created by Asus on 03/11/2024.
//

#ifndef RESERVE_H
#define RESERVE_H

#include "Card.h"



class Reserve {
private:
    Card m_card;
    int m_taille;
public :
    Reserve(Card const&card,int taille);
    [[nodiscard]]bool isEmpty()const ;
    [[nodiscard]]Card getCard()const;
    [[nodiscard]]int getTaille()const;
    void setTaille(int taille);
};



#endif //RESERVE_H
