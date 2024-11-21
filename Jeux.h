//
// Created by Asus on 08/11/2024.
//

#ifndef JEUX_H
#define JEUX_H
#include "Plateau.h"
#include "Player.h"
#include "vector"

class Reserve;
class Player;


class Jeux {
private:
    Plateau* m_plateau;
    std::vector<Player*>m_players;
    size_t actifIndex=0;
    void DistributeCards();

    void afficheClassement() const;

    static void afficheMain(Player* player);

    static void playerData(Player *player);

public:
    Jeux();
    ~Jeux();
    void initGame();
    void playGame();
    void playerBoard(Player *player) const;
    void actionPhase(Player* player);
    void buyPhase(Player* player);
    void endTurn(Player* player);
    //getters
    [[nodiscard]]std::vector<Player*>getPlayers()const;
    [[nodiscard]]Player& getActif()const;
    [[nodiscard]]size_t getActifIndex()const;


};



#endif //JEUX_H
