//
// Created by Asus on 07/11/2024.
//

#ifndef CARDSTREAM_H
#define CARDSTREAM_H
#include <string>




class Jeux;


class GameCommand {
     static void help(const std::string& nomCarte,Jeux const&j);
     static std::string normalizeCommand(const std::string& input);
public:
     static void getInput(Jeux const&j,std::string& cardName,bool buyPhase=false);
     static void getInput(Jeux const&j,int& nombre);
};





#endif //CARDSTREAM_H
