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
    m_reserveMap["CUIVRE"]=Reserve(TreasureCard("CUIVRE"),m_cuivre);
    m_reserveMap["ARGENT"]=Reserve(TreasureCard("ARGENT"),m_argent);
    m_reserveMap["OR"]=Reserve(TreasureCard("OR"),m_or);
    m_reserveMap["DOMAINE"]=Reserve(VictoryCard("DOMAINE"),m_victory);
    m_reserveMap["DUCHE"]=Reserve(VictoryCard("DUCHE"),m_victory);
    m_reserveMap["PROVINCE"]=Reserve(VictoryCard("PROVINCE"),m_victory);
    m_reserveMap["MALEDICTION"]=Reserve(VictoryCard("MALEDICTION"),m_curse);
    for(auto &i : base)
    {
        auto it = KingdomCard::KingdomCardMap.find(normalize(i));
        if (it != KingdomCard::KingdomCardMap.end())
        {
            m_reserveMap[it->second.getNom()]=Reserve(it->second, normalize(i) == "JARDIN" ? m_victory:m_kingdom);
        }

    }


}

bool Plateau::isEmpty() const
{
    int count=0;
    if(m_reserveMap.at("PROVINCE").isEmpty())
        return true;
    for(auto &it : m_reserveMap)
    {

        if(it.second.isEmpty())
            count++;
        if(count==3)
            return true;
    }
    return false;
}



void Plateau::affichage()const
{
    std::cout<<"//////////////////////////////////////////////RESERVE//////////////////////////////////////////////"<<std::endl;
    for(auto &it:m_reserveMap)
    {
        it.second.affichage();
    }
    std::cout<<"//////////////////////////////////////////////FIN RESERVE//////////////////////////////////////////////"<<std::endl;
}

void Plateau::updateReserve(const std::string& cardName,int nbr)
{
    m_reserveMap.at(cardName).setTaille(m_reserveMap.at(cardName).getTaille()-nbr);
}
std::unordered_map<std::string,Reserve>& Plateau::getReserveMap()
{
    return m_reserveMap;
}