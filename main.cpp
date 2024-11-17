
#include <fstream>
#include <iostream>

#include "Jeux.h"
#include "Player.h"
#include "CardStream.h"
#include "Plateau.h"


int main()
{

    Player p("samy");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    /*
    for(auto &i:KingdomCard::DataCards)
    {
        std::string name=i.getNom();
        int a=i.getCards();
        int b=i.getActions();
        std::cout<<name<<" : "<<"cartes : "<<a<<" actions : "<<b<<std::endl;
    }
    std::cout<<std::endl<<std::endl;*/
    Jeux::playGame();



    return 0;
}
