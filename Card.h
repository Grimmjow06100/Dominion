//
// Created by Asus on 03/11/2024.
//

#ifndef CARD_H
#define CARD_H
#include <string>

class Jeux;

class Card{
protected:
    int m_cost=0;

public:
    virtual ~Card()=default;
    virtual void affichage();
    virtual void action(Jeux &j);
    [[nodiscard ]] int getCost() const;
};

#endif //CARD_H
