//
// Created by Asus on 03/11/2024.
//

#include "Reserve.h"


Reserve::Reserve():m_card(nullptr),m_taille(0)
{}
Reserve::Reserve(KingdomCard const&card,int taille):m_card(new KingdomCard(card)),m_taille(taille)
{}
Reserve::Reserve(TreasureCard const&card,int taille ):m_card(new TreasureCard(card)),m_taille(taille)
{}
Reserve::Reserve(VictoryCard const&card ,int taille ):m_card(new VictoryCard(card)),m_taille(taille)
{}
Reserve::~Reserve()
{
    delete m_card;
}
Reserve::Reserve(Reserve &&other) noexcept :m_card(other.m_card),m_taille(other.m_taille)
{
    other.m_card=nullptr;
    other.m_taille=0;
}

Reserve::Reserve(const Reserve& other) {
    if (other.m_card != nullptr) {
        // On doit savoir quel type de carte c'est pour dupliquer l'objet correctement
        if (dynamic_cast<KingdomCard*>(other.m_card)) {
            m_card = new KingdomCard(*dynamic_cast<KingdomCard*>(other.m_card));
        } else if (dynamic_cast<TreasureCard*>(other.m_card)) {
            m_card = new TreasureCard(*dynamic_cast<TreasureCard*>(other.m_card));
        } else if (dynamic_cast<VictoryCard*>(other.m_card)) {
            m_card = new VictoryCard(*dynamic_cast<VictoryCard*>(other.m_card));
        }
    } else {
        m_card = nullptr;
    }

    // Copie de la taille
    m_taille = other.m_taille;
}


void Reserve::affichage() const {
    m_card->affichage();

}

bool Reserve::isEmpty() const {
    return (m_taille==0);
}

Card* Reserve::getCard() const {
    return m_card;
}

int Reserve::getTaille() const {
    return m_taille;
}

void Reserve::setTaille(int taille) {
    m_taille=taille;
}
