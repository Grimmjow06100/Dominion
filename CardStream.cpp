//
// Created by Asus on 07/11/2024.
//

#include "Cardstream.h"
#include "KingdomCard.h"
#include "TreasureCard.h"
#include "VictoryCard.h"
#include <sstream>
#include <iostream>




bool isFound(const std::string& s,int* index) {
    for(size_t i=0;i<KingdomCard::DataCards.size();i++)
    {
        if(KingdomCard::DataCards[i].getNom()==normalize(s))
        {
            *index=i;
            return true;
        }
    }
    return false;
}



// Recupération d'une carte saisi par le joueur
Card* CardStream::streamCard()
{
    Card* stream=nullptr;
    int* res=new int;
    std::string element;
    std::cin>>element;
    std::cin.ignore();
    std::string normalized=normalize(element);
    if ( normalized=="CUIVRE"||normalized=="ARGENT"||normalized=="OR")
    {
        stream=new TreasureCard(normalized);
    }
    else if (normalized=="DOMAINE"||normalized=="DUCHE"||normalized=="PROVINCE"||normalized=="MALEDICTION")
    {
        stream=new VictoryCard(normalized);
    }
    else if (isFound(normalized,res))
    {

        stream=new KingdomCard(KingdomCard::DataCards[*res]);
    }
    else
        std::cerr<<"Carte non reconnu"<<std::endl;

    delete res;
    return stream;
}

// Recupération d'une liste de carte saisi par le joueur
std::vector<Card*> CardStream::streamCardArray()
{
    std::vector<Card*> stream;
    int* res=new int;
    int registered(0);
    int failed(0);


    std::string ligne;
    std::getline (std::cin,ligne);
    std::string element;
    std::istringstream iss(ligne);
    while(iss>>element)
    {
        std::string normalized=normalize(element);
        if (normalized=="CUIVRE"||normalized=="ARGENT"||normalized=="OR")
        {
            stream.push_back(new TreasureCard(element));
            registered++;
        }
        else if (normalized=="DOMAINE"||normalized=="DUCHE"||normalized=="PROVINCE"||normalized=="MALEDICTION")
        {
            stream.push_back(new VictoryCard(element));
            registered++;
        }
        else if (isFound(normalized,res))
        {

            stream.push_back(new KingdomCard(KingdomCard::DataCards[*res]));
            registered++;
        }
        else
            failed++;

    }
    std::cout<<"Cartes enregistrees : "<<registered<<std::endl;
    if(failed>0)
        std::cerr<<"Cartes non reconnu : "<<failed<<std::endl;
    delete res;
    return stream;
}






