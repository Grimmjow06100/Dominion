
#include <fstream>

#include "Player.h"
#include "Plateau.h"


int main()
{

    Player p("samy");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    Plateau plateau(2);
    plateau.built();
    plateau.affichage();
    std::unordered_map<std::string,Reserve> reserveMap=plateau.getReserveMap();
    reserveMap["DOMAINE"].affichage();

    /*
    for(auto &i:KingdomCard::DataCards)
    {
        std::string name=i.getNom();
        int a=i.getCards();
        int b=i.getActions();
        std::cout<<name<<" : "<<"cartes : "<<a<<" actions : "<<b<<std::endl;
    }
    std::cout<<std::endl<<std::endl;*/




    return 0;
}
