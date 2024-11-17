//
// Created by Asus on 13/11/2024.
//

#include "Plateau.h"
#include "KingdomCard.h"
#include <iostream>
#include "VictoryCard.h"
#include "CardStream.h"
#include "TreasureCard.h"

std::vector<std::string> base ={"atelier","bucheron","village","festin","laboratoire","douves","jardins","chapelle","bandit","sorciere"};


Plateau::Plateau( int nbrJoueur):m_cuivre(60),m_argent(40),m_or(30)
{
    if(nbrJoueur==2)
    {
        m_victory=8;
        m_kingdom=10;
        m_curse=10;
    }
    else if(nbrJoueur==3)
    {
        m_victory=12;
        m_kingdom=12;
        m_curse=20;
    }
    else if(nbrJoueur==4)
    {
        m_victory=12;
        m_kingdom=12;
        m_curse=30;
    }
    else
    {
        m_victory=0;
        m_kingdom=0;
        m_curse=0;
    }
}
void Plateau::built()
{
    std::cout<<"test"<<std::endl;
    m_reserve.emplace_back(TreasureCard("CUIVRE"),m_cuivre);
    m_reserve.emplace_back(TreasureCard("ARGENT"),m_argent);
    m_reserve.emplace_back(TreasureCard("OR"),m_or);
    m_reserve.emplace_back(VictoryCard("DOMAINE"),m_victory);
    m_reserve.emplace_back(VictoryCard("PROVINCE"),m_victory);
    m_reserve.emplace_back(VictoryCard("DUCHE"),m_victory);
    m_reserve.emplace_back(VictoryCard("MALEDICTION"),m_curse);
    for(auto &i : base)
    {
        auto it = KingdomCard::KingdomCardMap.find(normalize(i));
        if (it != KingdomCard::KingdomCardMap.end())
        {
            Reserve r(it->second, normalize(i) == "JARDIN" ? 12 : 10);
            m_reserve.push_back(r);  // Ajout direct de l'objet
        }

    }


}

void Plateau::affichage()const
{
    std::cout<<"//////////////////////////////////////////////RESERVE//////////////////////////////////////////////"<<std::endl;
    for(auto &i:m_reserve)
    {
        i.affichage();
    }
    std::cout<<"//////////////////////////////////////////////FIN RESERVE//////////////////////////////////////////////"<<std::endl;
}