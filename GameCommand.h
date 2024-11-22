//
// Created by Asus on 07/11/2024.
//

#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H
#include <string>
#include <iostream>


class Jeux;
enum Phase {ACTION,BUY,NONE};

class GameCommand {
    static void handleHelp(const std::string& nomCarte,  const Jeux& j);
    static void handleSell(const std::string& nomCarte,  const Jeux& j, Phase phase);
    static void handlePlay(const std::string& nomCarte,  Jeux& j, Phase phase);
    static void handleBuy(const std::string& nomCarte,  Jeux& j, Phase phase);
    static std::string handlePick(const std::string& nomCarte,  const Jeux& j);
    static void displayMessage(const std::string& message);
    static std::string normalizeCommand(const std::string& input);

public:
    static void getInput( Jeux& j, Phase phase=NONE ,bool* exitOption =nullptr,const std::string& messageOption = "",std::string* cardNameOption=nullptr);
};




#endif //GAMECOMMAND_H
