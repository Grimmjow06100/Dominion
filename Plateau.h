//
// Created by Asus on 13/11/2024.
//

#ifndef PLATEAU_H
#define PLATEAU_H

#include "Reserve.h"
#include <unordered_map>


class Plateau {
private:
    std::unordered_map<std::string,Reserve>m_reserveMap;
    int m_cuivre;
    int m_argent;
    int m_or;
    int m_victory;
    int m_kingdom;
    int m_curse;
public :
    explicit Plateau (int nbrJoueur);
    void built();
    void affichage()const;
    bool isEmpty()const;
    void updateReserve(const std::string& cardName,int nbr);
    std::unordered_map<std::string,Reserve>& getReserveMap();



  };


#endif //PLATEAU_H
