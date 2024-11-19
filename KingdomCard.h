//
// Created by Asus on 03/11/2024.
//

#ifndef KINGDOMCARD_H
#define KINGDOMCARD_H
#include <string>
#include <vector>
#include "Card.h"
#include <map>




class KingdomCard : public Card{
private:
    bool m_attack;
    bool m_reaction;
    std::string m_description;
    int m_cards;
    int m_actions;
    int m_coins;
    int m_buys;
public :
    static std::vector<KingdomCard> DataCards;
    static std::map<std::string,KingdomCard> KingdomCardMap;
    static void GenerateKingdomFromFile(const std::string& nomFichier);


    KingdomCard(std::string nom,int cost,bool attack,bool reaction,std::string description,int cards,int actions,int coins,int buys);
    KingdomCard(KingdomCard const& card);
    KingdomCard();
    ~KingdomCard() override = default;
    KingdomCard& operator=(KingdomCard const& other) ;

    void affichage() override;
    void action(Jeux &j) override;


    [[nodiscard]] bool isAttack()const;
    [[nodiscard]] bool isReaction()const;
    [[nodiscard]] int getCards()const;
    [[nodiscard]] int getActions()const;
    [[nodiscard]] int getCoins()const;
    [[nodiscard]] int getBuys()const;
    [[nodiscard]] std::string getDescription()const;
};



#endif //KINGDOMCARD_H
