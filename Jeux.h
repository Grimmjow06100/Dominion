//
// Created by Asus on 08/11/2024.
//

#ifndef JEUX_H
#define JEUX_H
#include "vector"
#include "GameCommand.h"



class Plateau;
class Player;


class Jeux {
    Plateau* m_plateau;
    std::vector<Player*>m_players;
    size_t actifIndex;
    void DistributeCards();
    static void setPlayer(Player* player);
    void actionPhase(Player* player);
    void buyPhase(Player* player);
    void endTurn(Player* player);
    void endGame();

    void afficheClassement() const;

public:
    Jeux();
    ~Jeux();
    void initGame();
    void playerBoard(const Player* player) const;
    void initGame(std::string const&nom1,std::string const&nom2);
    void playGame();
    static void phaseMessage(Phase phase);

    //getters
    [[nodiscard]]std::vector<Player*>getPlayers()const;
    [[nodiscard]]Player& getActifPlayer()const;
    [[nodiscard]]size_t getActifIndex()const;
    [[nodiscard]]Plateau& getPlateau()const;


};

std::vector<std::string> choisirDixElements(const std::vector<std::string> &options);


#endif //JEUX_H
