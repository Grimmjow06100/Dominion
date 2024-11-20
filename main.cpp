
#include <fstream>
#include <iostream>
#include "Player.h"
#include "Plateau.h"
#include <string>


int main()
{
    std::system("cls");
    Player p("samy");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    Jeux j;
    j.initGame();
    j.playGame();

    return 0;
}
