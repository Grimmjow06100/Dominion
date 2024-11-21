//
// Created by Asus on 03/11/2024.
//

#ifndef TREASURECARD_H
#define TREASURECARD_H
#include "Card.h"



class TreasureCard : public Card{
private:
    int m_treasure;
public:
    explicit TreasureCard(std::string const& nom);
    TreasureCard(TreasureCard const& card);
    [[nodiscard]]int getTreasure() const ;
    void affichage() const override;
    void action(Jeux &j) override;
    void details() const override;
};



#endif //TREASURECARD_H
