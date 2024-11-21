//
// Created by Asus on 03/11/2024.
//

#ifndef RESERVE_H
#define RESERVE_H

class Card;
class TreasureCard;
class VictoryCard;
class KingdomCard;




class Reserve {
private:
    Card* m_card;
    int m_taille;
public :
    Reserve(TreasureCard const&card,int taille);
    Reserve(VictoryCard const&card ,int taille );
    Reserve(KingdomCard const&card,int taille);
    Reserve(Reserve &&other) noexcept ;
    Reserve(const Reserve& other);
    Reserve& operator=(Reserve const& other);
    Reserve();
    ~Reserve();
    [[nodiscard]]bool isEmpty()const ;
    [[nodiscard]]Card* getCard()const;
    [[nodiscard]]int getTaille()const ;
    void DimTaille(int nbr);
    void setTaille(int taille);
    void affichage() const;
};



#endif //RESERVE_H
