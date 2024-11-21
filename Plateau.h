//
// Created by Asus on 13/11/2024.
//

#ifndef PLATEAU_H
#define PLATEAU_H
#include <map>
#include <string>
#include "Reserve.h"


class Plateau {
private:
    std::map<std::string,Reserve>m_reserve;
    int m_cuivre;
    int m_argent;
    int m_or;
    int m_victory;
    int m_kingdom;
    int m_curse;
public :
    void affichePlateau();
    explicit Plateau (int nbrJoueur);
    void built();
    void affichage()const;
    [[nodiscard]]bool isEmpty()const;
    void updateReserveByName(const std::string& cardName,int nbr);
    std::map<std::string,Reserve>& getReserve();





  };


#endif //PLATEAU_H
