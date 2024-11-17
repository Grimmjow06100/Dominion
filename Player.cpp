//
// Created by Asus on 03/11/2024.
//

#include "Player.h"


#include "TreasureCard.h"
#include <algorithm>
#include <random>


/**
 * Constructeur de Player
 */
Player::Player(std::string name):m_name(std::move(name)){
    m_actions = 1;
    m_buys = 1;
    m_coins = 0;
    m_points = 0;
}

Player::~Player()
{
    for (Card* const&i: m_deck)
    {
        delete i;
    }
    for (Card* const&i: m_hand)
    {
        delete i;
    }
    for (Card* const&i: m_defausse)
    {
        delete i;
    }
    for (Card* const&i: m_played)
    {
        delete i;
    }
}

void Player::pioche(int x)
{
    for (int i = 0; i < x; i++)
    {
        if (m_deck.empty())
        {
            if (m_defausse.empty())
            {
                break;
            }
            m_deck = std::move(m_defausse);  // Déplace les cartes de defausse vers deck
            m_defausse.clear();
            shuffle();

        }
        m_hand.push_back(m_deck.back());// Déplace la carte de deck vers hand
        m_deck.pop_back();


    }

}

void Player::defausse()
{
    for(Card* const&i: m_hand)
    {
        m_defausse.push_back(i);

    }
    m_hand.clear();
    for(Card* const&i: m_played)
    {
        m_defausse.push_back(i);

    }
    m_played.clear();
}

void Player::shuffle() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::shuffle(m_deck.begin(), m_deck.end(), engine);
}


//getters
std::vector<Card*> Player::getDeck() const
{
    return m_deck;
}
std::vector<Card*> Player::getHand() const
{
    return m_hand;
}
std::vector<Card*> Player::getDefausse() const
{
    return m_defausse;
}
std::vector<Card*> Player::getPlayed() const
{
    return m_played;
}
int Player::getPoints() const
{
    return m_points;
}
int Player::getCoins() const
{
    return m_coins;
}
int Player::getActions() const
{
    return m_actions;
}
int Player::getBuys() const
{
    return m_buys;
}

//setters
void Player::setDeck(std::vector<Card*> deck)
{
    m_deck = std::move(deck);
}
void Player::setHand(std::vector<Card*> hand)
{
    m_hand = std::move(hand);
}
void Player::setDefausse(std::vector<Card*> defausse)
{
    m_defausse = std::move(defausse);
}
void Player::setPlayed(std::vector<Card*> played)
{
    m_played = std::move(played);
}
void Player::setPoints(int points)
{
    m_points = points;
}
void Player::setCoins(int Coins)
{
    m_coins = Coins;
}
void Player::setActions(int actions)
{
    m_actions = actions;
}
void Player::setBuys(int buys)
{
    m_buys = buys;
}

