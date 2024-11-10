//
// Created by Asus on 07/11/2024.
//

#include "Cardstream.h"
#include <algorithm>
#include "KingdomCard.h"
#include "VictoryCard.h"
#include "TreasureCard.h"
#include <sstream>
#include <variant>
#include <unordered_map>
#include <iostream>




using EnumCard = std::variant<Kingdom,Victory,Treasure>;
std::unordered_map<std::string,EnumCard> CardMap={
    {"DOMAINE",DOMAINE},
    {"DUCHE",DUCHE},
    {"PROVINCE",PROVINCE},
    {"CUIVRE",CUIVRE},
    {"ARGENT",ARGENT},
    {"OR",OR},
    //------------------------------------------
    {"ATELIER",ATELIER},
    {"BUCHERON",BUCHERON},
    {"CHANCELIER",CHANCELIER},
    {"AVENTURIER",AVENTURIER},
    {"BIBLIOTHEQUE",BIBLIOTHEQUE},
    {"CHAMBRE_DU_CONSEIL",CHAMBRE_DU_CONSEIL},
    {"FESTIVAL",FESTIVAL},
    {"LABORATOIRE",LABORATOIRE},
    {"MARCHE",MARCHE},
    {"MINE",MINE},
    {"SALLE_DU_TRONE",SALLE_DU_TRONE},
    {"SORCIERE",SORCIERE},
    {"VILLAGE",VILLAGE},
    {"BUREAUCRATE",BUREAUCRATE},
    {"ESPION",ESPION},
    {"FESTIN",FESTIN},
    {"MILICE",MILICE},
    {"VOLEUR",VOLEUR},
    {"JARDIN",JARDIN},
    {"CAVE",CAVE},
    {"CHAPELLE",CHAPELLE},
    {"DOUVES",DOUVES},
    {"PRETEUR_SUR_GAGES",PRETEUR_SUR_GAGES},
    {"FORGE",FORGE}
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
    m_stream = std::vector<Card*>();
}
CardStream::~CardStream()
{
    clean();
}

void CardStream::clean()
{
    for(Card* const&i: m_stream)
    {
        delete i;
    }
    m_stream.clear();
}





// Recupération du flux de carte saisi par le joueur
void CardStream::stream() {
    clean();
    std::string ligne;
    std::getline(std::cin, ligne);
    std::istringstream flux(ligne);
    std::string element;
    while (flux >> element)
    {
        if(isFound( element))
        {
            EnumCard c = CardMap.at(normalize(element));
            if (std::holds_alternative<Kingdom>(c)) {
                m_stream.push_back(new KingdomCard(std::get<Kingdom>(c)));
            } else if (std::holds_alternative<Victory>(c)) {
                m_stream.push_back(new VictoryCard(std::get<Victory>(c)));
            } else {
                m_stream.push_back(new TreasureCard(std::get<Treasure>(c)));
            }
        }
        else
            std::cerr<<"Carte non reconnue"<<std::endl;
    }
}

std::vector<Card*> CardStream::getStream() const
{
    return m_stream;
}


