//
// Created by Asus on 08/11/2024.
//

#include "Jeux.h"


std::vector<Reserve> Jeux::getReserve()const
{
    return m_reserve;
}

std::vector<Player*>Jeux::getPlayers()const
{
    return m_players;
}

Player& Jeux::getActif() const
{
    return *m_players.at(actifIndex);
}

int Jeux::getActifIndex() const
{
    return actifIndex;
}
