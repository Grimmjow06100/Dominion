//
// Created by Asus on 08/11/2024.
//

#ifndef JEUX_H
#define JEUX_H
#include "Player.h"
#include "Reserve.h"
#include "vector"

class Reserve;


class Jeux {
private:
    std::vector<Reserve> m_reserve;
    std::vector<Player>&m_players;
    Player& m_actif;
public:
    //getters
    [[nodiscard]]std::vector<Reserve> getReserve()const;
    [[nodiscard]]std::vector<Player>&getPlayers()const;
    [[nodiscard]]Player& getActif()const;

    Jeux(std::vector<Player>& m_players, Player& m_actif)
        : m_players(m_players),
          m_actif(m_actif)
    {
    }
};



#endif //JEUX_H
