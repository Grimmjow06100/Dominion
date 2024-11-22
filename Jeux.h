//
// Created by Asus on 08/11/2024.
//

#ifndef JEUX_H
#define JEUX_H
#include "vector"



class Plateau;
class Player;


class Jeux {
private:
    Plateau* m_plateau;
    std::vector<Player*>m_players;
    size_t actifIndex;
    void DistributeCards();
    void setPlayer(Player* player);
    void playerBoard(Player *player) const;
    void actionPhase(Player* player);
    void buyPhase(Player* player);
    void endTurn(Player* player);

public:
    Jeux();
    ~Jeux();
    void initGame();
    void initGame(std::string nom1,std::string nom2);
    void playGame();

    //getters
    [[nodiscard]]std::vector<Player*>getPlayers()const;
    [[nodiscard]]Player& getActifPlayer()const;
    [[nodiscard]]size_t getActifIndex()const;
    [[nodiscard]]Plateau& getPlateau()const;


};



#endif //JEUX_H
