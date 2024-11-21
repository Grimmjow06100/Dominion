
#include <fstream>
#include <iostream>
#include "Player.h"
#include "KingdomCard.h"
#include "Jeux.h"
#include "Card.h"


int main()
{
    std::system("cls");
    Player p("samy");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    Jeux j;
    j.initGame("samy","toto");
    KingdomCard atelier=KingdomCard::KingdomCardMap.at("ATELIER");
    KingdomCard jardins=KingdomCard::KingdomCardMap.at("JARDINS");
    KingdomCard cave=KingdomCard::KingdomCardMap.at("CAVE");
    KingdomCard douves=KingdomCard::KingdomCardMap.at("DOUVES");
    KingdomCard bandit=KingdomCard::KingdomCardMap.at("BANDIT");
    KingdomCard chapelle=KingdomCard::KingdomCardMap.at("CHAPELLE");
    KingdomCard sorciere=KingdomCard::KingdomCardMap.at("SORCIERE");
    j.getPlayers().at(1)->getHand().push_back(&douves);
    cave.action(j);

    return 0;
}
