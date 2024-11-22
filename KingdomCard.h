//
// Created by Asus on 03/11/2024.
//

#ifndef KINGDOMCARD_H
#define KINGDOMCARD_H
#include <string>
#include <vector>
#include <map>
#include "Card.h"
class Player;
class Jeux;


class KingdomCard : public Card{
    bool m_attack;
    bool m_reaction;
    std::string m_description;
    int m_cards;
    int m_actions;
    int m_coins;
    int m_buys;
    static void Atelier(Jeux &j);
    static void Cave(Jeux &j);
    static void Jardins(Player& p);
    static void Bandit(Jeux const&j);
    static void Sorciere(Jeux const&j);
    static void Chapelle(Jeux &j);
public :
    static std::vector<KingdomCard> DataCards;
    static std::map<std::string,KingdomCard> KingdomCardMap;
    static void GenerateKingdomFromFile(const std::string& nomFichier);
    static std::string actionType(KingdomCard const&k);


    KingdomCard(std::string nom,int cost,bool attack,bool reaction,std::string description,int cards,int actions,int coins,int buys);
    KingdomCard(KingdomCard const& card);
    KingdomCard();
    ~KingdomCard() override = default;
    KingdomCard& operator=(KingdomCard const& other) ;

    void affichage() const override;
    void action(Jeux &j);
    void details()const override;


    [[nodiscard]] bool isAttack()const;
    [[nodiscard]] bool isReaction()const;
    [[nodiscard]] int getCards()const;
    [[nodiscard]] int getActions()const;
    [[nodiscard]] int getCoins()const;
    [[nodiscard]] int getBuys()const;
    [[nodiscard]] std::string getDescription()const;
};



#endif //KINGDOMCARD_H
