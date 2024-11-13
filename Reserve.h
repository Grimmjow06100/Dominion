//
// Created by Asus on 03/11/2024.
//

#ifndef RESERVE_H
#define RESERVE_H

#include "Card.h"
#include "KingdomCard.h"
#include "TreasureCard.h"
#include "VictoryCard.h"

class Reserve {
private:
    Card* m_card;
    int m_taille;
public :
    Reserve( KingdomCard const&card,int taille);
    Reserve(TreasureCard const&card,int taille);
    Reserve(VictoryCard const&card ,int taille );
    Reserve(Reserve &&other) noexcept ;
    Reserve();
    ~Reserve();
    [[nodiscard]]bool isEmpty()const ;
    [[nodiscard]]Card* getCard()const;
    [[nodiscard]]int getTaille()const;
    void setTaille(int taille);
    void affichage() const;
};



#endif //RESERVE_H
