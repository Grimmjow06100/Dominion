//
// Created by Asus on 07/11/2024.
//

#include "Cardstream.h"
#include "KingdomCard.h"
#include <algorithm>
#include <sstream>
#include <iostream>


std::unordered_map<std::string,EnumCard> CardMap={
    {"DOMAINE",DOMAINE},
    {"DUCHE",DUCHE},
    {"PROVINCE",PROVINCE},
    {"CUIVRE",CUIVRE},
    {"ARGENT",ARGENT},
    {"OR",OR},
};



// Normalisation de la chaine de caractères (majuscule)
std::string normalize(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res;
}
// Vérification de l'existence de la carte
bool isFound(const std::string& s) {
    return CardMap.find(normalize(s)) != CardMap.end();
}
CardStream::CardStream()
{
    m_stream = nullptr;
}
CardStream::~CardStream()
{
    delete m_stream;
}



// Recupération du flux de carte saisi par le joueur
void CardStream::streamCard()
{
    std::string element;
    std::cin>>element;
    bool existe=false;
    if(isFound(element))
    {
        EnumCard c = CardMap.at(normalize(element));
        if (std::holds_alternative<Victory>(c)) {
            m_stream=new VictoryCard(std::get<Victory>(c));
            existe=true;
        }
        else if (std::holds_alternative<Treasure>(c)) {
            m_stream=new TreasureCard(std::get<Treasure>(c));
            existe=true;
        }
    }
    else
        for(auto i:KingdomCard::DataCards)
        {
            if(i.getNom()==normalize(element))
            {
                i.affichage();
                m_stream=new KingdomCard(i);
                existe=true;
                break;
            }
        }
    if (existe==false)
        std::cerr<<"Carte inexistante"<<std::endl;
}




Card* CardStream::getStream() const
{
    return m_stream;
}


