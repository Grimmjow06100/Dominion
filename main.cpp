
#include <fstream>
#include "Player.h"
#include "CardStream.h"


int main()
{
    Player p("samy");
    CardStream card;
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    for(auto i : KingdomCard::DataCards)
    {
        i.affichage();
    }

    return 0;
}