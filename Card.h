//
// Created by Asus on 03/11/2024.
//

#ifndef CARD_H
#define CARD_H
#include <string>

class Jeux;

class Card{
protected:
    std::string m_nom;
    int m_cost=0;


public:
    Card(std::string nom,int cost);
    virtual ~Card()=default;
    virtual void affichage();
    virtual void action(Jeux &j);
    [[nodiscard ]] int getCost() const;
};

std::string normalize(const std::string& s);

#endif //CARD_H
