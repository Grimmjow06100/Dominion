//
// Created by Asus on 03/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
class Card;





class Player {
private:
    std::vector<Card*> m_deck;
    std::vector<Card*> m_hand;
    std::vector<Card*> m_defausse;
    std::vector<Card*> m_played;
    int m_points;
    int m_money;
    int m_actions;
    int m_buys;
    std::string m_name;
    void shuffle();
public:
    explicit Player(std::string name);
    ~Player();
    void pioche(int x);
    void defausse();

    //LE DUR DE LA VIE
    void playBuy();
    void playAction();
    void Adjustment();



    //getters
    [[nodiscard]]std::vector<Card*> getDeck() const;
    [[nodiscard]]std::vector<Card*> getHand() const;
    [[nodiscard]]std::vector<Card*> getDefausse() const;
    [[nodiscard]]std::vector<Card*> getPlayed() const;
    [[nodiscard]]int getPoints() const;
    [[nodiscard]]int getMoney() const;
    [[nodiscard]]int getActions() const;
    [[nodiscard]]int getBuys() const;


    //setters
    void setDeck(std::vector<Card*> deck);
    void setHand(std::vector<Card*> hand);
    void setDefausse(std::vector<Card*> discard);
    void setPlayed(std::vector<Card*> played);
    void setPoints(int points);
    void setMoney(int money);
    void setActions(int actions);
    void setBuys(int buys);





};



#endif //PLAYER_H
