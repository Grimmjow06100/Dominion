//
// Created by Asus on 08/11/2024.
//

#ifndef JEUX_H
#define JEUX_H
#include "Plateau.h"
#include "Player.h"
#include "vector"

class Reserve;


class Jeux {
private:
    Plateau m_plateau;
    std::vector<Player*>m_players;
    int actifIndex=0;
public:
    //getters

    [[nodiscard]]std::vector<Player*>getPlayers()const;
    [[nodiscard]]Player& getActif()const;
    [[nodiscard]]int getActifIndex()const;


};



#endif //JEUX_H
