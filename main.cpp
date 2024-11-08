#include <iostream>
#include "Player.h"
#include "Card.h"
#include "CardStream.h"



int main()
{

    Player p;
    CardStream card;
    std::cout<<"la taille du deck initial est de "<<p.getDeck().size()<<std::endl;
    std::cout<<"affichage du deck du joueur"<<std::endl;
    for(auto i : p.getDeck())
    {
        i->affichage();
        i->action(p);
    }
    card.stream();
    std::vector<Card*> c=std::move(card.getStream());
    p.setDefausse(c);

    std::cout<<"le joueur pioche 11 cartes"<<std::endl;
    p.pioche(11);

    std::cout<<"la taille du deck est de "<<p.getDeck().size()<<std::endl;
    std::cout<<"la taille de la defausse est de "<<p.getDefausse().size()<<std::endl;
    std::cout<<"la taille de la main du joueur est de "<<p.getHand().size()<<std::endl;

    std::cout<<"affichage de la main du joueur"<<std::endl;
    for(auto i : p.getHand())
    {
        i->affichage();
    }

    std::cout<<"le joueur defausse sa main et ses cartes jouees"<<std::endl;
    p.defausse();

    std::cout<<"la taille de la defausse est de "<<p.getDefausse().size()<<std::endl;
    std::cout<<"le joueur a "<<p.getPoints()<<" points"<<std::endl;
    std::cout<<"le joueur a "<<p.getMoney()<<" pieces"<<std::endl;
    std::cout<<"samy est un bg"<<std::endl;

    return 0;
}