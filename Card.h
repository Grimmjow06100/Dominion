//
// Created by Asus on 03/11/2024.
//

#ifndef CARD_H
#define CARD_H
#include "Player.h"



class Card
{
protected:
    int m_cost=0;
public :
    virtual ~Card()=default;
    virtual void affichage();
    virtual void action(Player &p);
    [[nodiscard ]] int getCost() const;
};



#endif //CARD_H
