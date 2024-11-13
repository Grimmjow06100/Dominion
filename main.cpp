
#include <fstream>
#include <iostream>

#include "Player.h"
#include "CardStream.h"
#include "Plateau.h"


int main()
{
    Player p("samy");
    CardStream c;
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    for(auto &i:KingdomCard::DataCards)
    {
        std::string a=i.getNom();
        std::cout<<a<<std::endl;
    }

    Card* card=c.streamCard();
    card->affichage();
    std::vector<Card*> cardArray=c.streamCardArray();
    for(auto &i:cardArray)
    {
        i->affichage();
    }


    return 0;
}
