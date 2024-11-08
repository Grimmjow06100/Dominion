//
// Created by Asus on 03/11/2024.
//

#ifndef TREASURECARD_H
#define TREASURECARD_H
#include "Card.h"

enum Treasure
{
    CUIVRE=1,
    ARGENT,
    OR
};

class TreasureCard : public Card{
private:
    Treasure m_treasure;
public:
    explicit TreasureCard(Treasure treasure);
    [[nodiscard]]Treasure getTreasure() const;
    void affichage() override;
    void action(Jeux &j) override;
};



#endif //TREASURECARD_H
