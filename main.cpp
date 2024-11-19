
#include <fstream>
#include <iostream>

#include "Player.h"
#include "Plateau.h"


int main()
{

    Player p("samy");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    Jeux j;
    j.initGame();
    j.playGame();




    return 0;
}
