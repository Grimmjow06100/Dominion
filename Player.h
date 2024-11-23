//
// Created by Asus on 03/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>



class Card;
class Jeux;
class Plateau;



class Player {
    std::vector<Card*> m_deck;
    std::vector<Card*> m_hand;
    std::vector<Card*> m_defausse;
    std::vector<Card*> m_played;
    std::string m_name;
    int m_actions;
    int m_buys;
    int m_coins;
    int m_points;
public:
    explicit Player(std::string const&name);
    ~Player();
    void pioche(int x);
    void defausseAll();
    void info()const ;
    bool defausseFromHand(std::string const &cardName);
    bool defausseArray(std::vector<Card*>& cards);
    bool playAction(std::string const&cardName,Jeux &jeux);
    bool gainCard(std::string const&cardName,Plateau &p,int minCost=0,int maxCost=10);
    void afficheHand()const;
    void shuffle();
    void AddPoint(int points);
    void AddTreasure(int treasure);
    void AddAction(int action);
    void AddBuy(int buy);
    void AddCoin(int coin);
    bool ReactTo(int&index)const;
    bool sellCard(const std::string&cardName);
    void sellAllTreasure();
    bool buyCard(std::string const&cardName,Jeux const&j);
    Card* drawCard();
    static void trashCard(const Card* card);
    bool trashCardFromHand(std::string const&cardName);
    bool canPlayAction();
    bool canBuy()const;


    //getters
    [[nodiscard]]std::vector<Card*>& getDeck();
    [[nodiscard]]std::vector<Card*>& getHand();
    [[nodiscard]]std::vector<Card*>& getDefausse() ;
    [[nodiscard]]std::vector<Card*>& getPlayed();
    [[nodiscard]]int getPoints() const;
    [[nodiscard]]int getCoins() const;
    [[nodiscard]]int getActions() const;
    [[nodiscard]]int getBuys() const;
    [[nodiscard]] std::string getName() const;

    //setters
    void setDeck(std::vector<Card*> deck);
    void setHand(std::vector<Card*> hand);
    void setDefausse(std::vector<Card*> discard);
    void setPlayed(std::vector<Card*> played);
    void setCoins(int coins);
    void setActions(int actions);
    void setBuys(int buys);

};



#endif //PLAYER_H
