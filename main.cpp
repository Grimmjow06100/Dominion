
#include <fstream>
#include <iostream>

#include "Player.h"
#include "CardStream.h"
#include "Plateau.h"


int main()
{
    Player p("samy");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    for(auto &i:KingdomCard::DataCards)
    {
        std::string name=i.getNom();
        int a=i.getCards();
        int b=i.getActions();
        std::cout<<name<<" : "<<"cartes : "<<a<<" actions : "<<b<<std::endl;
    }




    return 0;
}
