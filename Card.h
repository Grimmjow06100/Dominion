//
// Created by Asus on 03/11/2024.
//

#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

class Jeux;


class Card{
protected:
    std::string m_nom;
    int m_cost=0;


public:
    Card(std::string nom,int cost);
    static void afficheCards(const std::vector<Card*>& cards);
    virtual ~Card()=default;
    virtual void affichage()const=0;
    virtual void details()const=0;
    [[nodiscard ]] int getCost() const;
    [[nodiscard]] std::string getNom() const;
};

std::string normalize(const std::string& s);
void notif(std::string const& message);
void alert(std::string const& message);

#endif //CARD_H
