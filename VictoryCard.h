//
// Created by Asus on 03/11/2024.
//

#ifndef VICTORYCARD_H
#define VICTORYCARD_H
#include "Card.h"
enum Victory
{
    DOMAINE=1,
    DUCHE=3,
    PROVINCE=6,
    MALÉDICTION=-1
};

class VictoryCard : public Card{
private:
    Victory m_victory;
public:
    explicit VictoryCard( Victory victory);
    [[nodiscard]]Victory getVictory() const ;
    void affichage() override;
    void action(Player &p) override;
};



#endif //VICTORYCARD_H
