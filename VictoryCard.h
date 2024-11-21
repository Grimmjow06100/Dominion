//
// Created by Asus on 03/11/2024.
//

#ifndef VICTORYCARD_H
#define VICTORYCARD_H
#include "Card.h"

class VictoryCard : public Card{
private:
    int m_victory;
public:
    explicit VictoryCard(std::string const& nom);
    VictoryCard(VictoryCard const& card);
    [[nodiscard]]int getVictory() const ;
    void affichage() const override;
    void action(Jeux &j) override;
};



#endif //VICTORYCARD_H
