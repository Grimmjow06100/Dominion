#include "Player.h"
#include <algorithm>
#include <iostream>
#include <random>
#include "TreasureCard.h"
#include "VictoryCard.h"
#include "KingdomCard.h"
#include "Plateau.h"
#include "Reserve.h"

/**
 * Constructeur de Player
 */
Player::Player(std::string name) : m_name(std::move(name)), m_actions(1), m_buys(1), m_coins(0), m_points(0) {}

Player::~Player() {
    for (auto* card : m_deck) {
        delete card;
    }
    for (auto* card : m_hand) {
        delete card;
    }
    for (auto* card : m_defausse) {
        delete card;
    }
    for (auto* card : m_played) {
        delete card;
    }
    m_deck.clear();
    m_hand.clear();
    m_defausse.clear();
    m_played.clear();
}

void Player::pioche(int x) {
    for (int i = 0; i < x; i++) {
        if (m_deck.empty()) {
            if (m_defausse.empty()) {
                break;
            }
            m_deck = std::move(m_defausse);  // Déplace les cartes de defausse vers deck
            m_defausse.clear();
            shuffle();
        }
        m_hand.push_back(m_deck.back()); // Déplace la carte de deck vers hand
        m_deck.pop_back();
    }
}

void Player::reset() {
    m_actions = 1;
    m_buys = 1;
    m_coins = 0;
}

void Player::afficheHand() const {
    std::cout << "Votre main :" << std::endl;
    for (const auto& card : m_hand) {
        card->affichage();
    }
}

bool Player::playCard(const std::string& cardName, Jeux& jeux) {
    auto it = std::find_if(m_hand.begin(), m_hand.end(), [&cardName](const Card* card) {
        return card->getNom() == cardName;
    });
    if (it != m_hand.end()) {
        (*it)->action(jeux);
        m_played.push_back(*it);
        m_hand.erase(it);
        return true;
    }
    std::cout << "La carte n'existe pas" << std::endl;
    return false;
}

void Player::defausseAll() {
    m_defausse.insert(m_defausse.end(), std::make_move_iterator(m_hand.begin()), std::make_move_iterator(m_hand.end()));
    m_hand.clear();
    m_defausse.insert(m_defausse.end(), std::make_move_iterator(m_played.begin()), std::make_move_iterator(m_played.end()));
    m_played.clear();
}

bool Player::defausseFromHand(const std::string& cardName) {
    auto it = std::find_if(m_hand.begin(), m_hand.end(), [&cardName](const Card* card) {
        return card->getNom() == cardName;
    });
    if (it != m_hand.end()) {
        m_defausse.push_back(*it);
        m_hand.erase(it);
        std::cout << "La carte a ete place dans la defausse" << std::endl;
        return true;
    }
    return false;
}

bool Player::defausseArray(std::vector<Card*>& cards) {
    if (cards.empty()) {
        return false; // Rien à faire
    }
    m_defausse.insert(m_defausse.end(), std::make_move_iterator(cards.begin()), std::make_move_iterator(cards.end()));
    std::cout<<"Les cartes ont ete place dans la defausse"<<std::endl;
    cards.clear();
    return true;
}

bool Player::gainCard(const std::string& cardName, Plateau& p,int minCost,int maxCost) {
    auto& reserve = p.getReserve();
    std::string str = normalize(cardName);
    auto it = reserve.find(str);
    if (it != reserve.end()) {
        auto& res = it->second;
        auto* card = res.getCard();
        if (res.getTaille() > 0 && card->getCost() >= minCost && card->getCost() <= maxCost) {
            if (auto* kingdom = dynamic_cast<KingdomCard*>(card)) {
                m_defausse.push_back(new KingdomCard(*kingdom));
                p.updateReserveByName(str, 1);
                std::cout << "la carte "<<card->getNom()<<" a ete place dans la defausse "<<std::endl;
                return true;
            }
            if (auto* treasure = dynamic_cast<TreasureCard*>(card)) {
                m_defausse.push_back(new TreasureCard(*treasure));
                p.updateReserveByName(str, 1);
                std::cout << "la carte "<<card->getNom()<<" a ete place dans la defausse"<<std::endl;
                return true;
            }
            if (auto* victory = dynamic_cast<VictoryCard*>(card)) {
                m_defausse.push_back(new VictoryCard(*victory));
                p.updateReserveByName(str, 1);
                std::cout << "la carte "<<card->getNom()<<" a ete place dans la defausse"<<std::endl;
                return true;
            }
        }
        std::cout << "La carte n'est plus disponible ou ne remplie pas les conditions de selection" << std::endl;

    } else {
        std::cout << "cette carte n'est pas presente dans le jeu";
    }
    return false;
}

Card* Player::drawCard() {
    if (m_deck.empty()) {
        if (m_defausse.empty()) {
            return nullptr;
        }
        m_deck = std::move(m_defausse);
        m_defausse.clear();
        shuffle();
    }
    auto* card =m_deck.back();
    m_deck.pop_back();
    return card;
}

void Player::trashCard(Card* card) {
    delete card;
}

bool Player::buyCard(std::string const& cardName, Plateau& p)
{

    std::map<std::string, Reserve>& reserve = p.getReserve();
    auto it = reserve.find(normalize(cardName));
    if(it!=reserve.end())
    {
        if(it->second.getTaille()>0)
        {

            if(it->second.getCard()->getCost()<=(*this).getCoins())
            {
                if(auto* k=dynamic_cast<KingdomCard*>(it->second.getCard()))
                {
                    (*this).getDefausse().push_back(new KingdomCard(*k));
                    (*this).AddBuy(-1);
                    (*this).AddCoin(-k->getCost());
                    p.updateReserveByName(k->getNom(),1);
                    std::cout<<"Vous avez acheté la carte "<<k->getNom()<<std::endl;
                    return true;

                }
                if(auto* t=dynamic_cast<TreasureCard*>(it->second.getCard()))
                {
                    m_defausse.push_back(new TreasureCard(*t));
                    AddBuy(-1);
                    AddCoin(-t->getCost());
                    p.updateReserveByName(t->getNom(),1);
                    std::cout<<"Vous avez acheté la carte "<<t->getNom()<<std::endl;
                    return true;
                }
                if(auto* v=dynamic_cast<VictoryCard*>(it->second.getCard()))
                {
                    m_defausse.push_back(new VictoryCard(*v));
                    AddBuy(-1);
                    AddCoin(-v->getCost());
                    p.updateReserveByName(v->getNom(),1);
                    std::cout<<"Vous avez acheté la carte "<<v->getNom()<<std::endl;
                    return true;
                }

            }
            std::cout<<"Vous n'avez pas assez de pièces pour acheter cette carte"<<std::endl;
            return false;
        }
        std::cout<<"La carte n'est plus disponible"<<std::endl;
    }
    std::cout<<"La carte n'existe pas"<<std::endl;
    return false;
}


bool Player::trashCardFromHand(const std::string& cardName) {
    auto it = std::find_if(m_hand.begin(), m_hand.end(), [&cardName](const Card* card) {
        return card->getNom() == cardName;
    });
    if (it != m_hand.end()) {
        delete *it;
        m_hand.erase(it);
        return true;
    }
    std::cout<<"La carte n'est pas dans votre main"<<std::endl;
    return false;
}

void Player::shuffle() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::shuffle(m_deck.begin(), m_deck.end(), engine);
}

void Player::AddPoint(int points) {
    m_points += points;
}

void Player::AddTreasure(int treasure) {
    m_coins += treasure;
}
void Player::AddAction(int action) {
    m_actions += action;
}
void Player::AddBuy(int buy) {
    m_buys += buy;
}
void Player::AddCoin(int coin) {
    m_coins += coin;
}

bool Player::sellCard(const std::string& cardName) {

    auto it =std::find_if(m_hand.begin(),m_hand.end(),[&cardName](const Card* c)
    {
        return c->getNom()==cardName;
    });
    if(it!=m_hand.end())
    {
        if(auto* treasure=dynamic_cast<TreasureCard*>(*it))
        {
            m_coins+=treasure->getTreasure();
            m_defausse.push_back(*it);
            m_hand.erase(it);
            return true;
        }
    }
    return false;
}

bool Player::ReactTo(int& index) {
    for (size_t i = 0; i < m_hand.size(); ++i) {
        if (auto* kingdom = dynamic_cast<KingdomCard*>(m_hand[i])) {
            if (kingdom->isReaction()) {
                index = static_cast<int>(i);
                return true;
            }
        }
    }
    return false;
}

std::vector<Card*>& Player::getDeck() {
    return m_deck;
}

std::vector<Card*>& Player::getHand() {
    return m_hand;
}

std::vector<Card*>& Player::getDefausse() {
    return m_defausse;
}

std::vector<Card*>& Player::getPlayed() {
    return m_played;
}

int Player::getPoints() const {
    return m_points;
}

int Player::getCoins() const {
    return m_coins;
}

int Player::getActions() const {
    return m_actions;
}

std::string Player::getName() const {
    return m_name;
}

int Player::getBuys() const {
    return m_buys;
}

// setters
void Player::setDeck(std::vector<Card*> deck) {
    m_deck = std::move(deck);
}

void Player::setHand(std::vector<Card*> hand) {
    m_hand = std::move(hand);
}

void Player::setDefausse(std::vector<Card*> defausse) {
    m_defausse = std::move(defausse);
}

void Player::setPlayed(std::vector<Card*> played) {
    m_played = std::move(played);
}

void Player::setCoins(int coins) {
    m_coins = coins;
}

void Player::setActions(int actions) {
    m_actions = actions;
}

void Player::setBuys(int buys) {
    m_buys = buys;
}