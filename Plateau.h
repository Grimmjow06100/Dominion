//
// Created by Asus on 13/11/2024.
//

#ifndef PLATEAU_H
#define PLATEAU_H
#include <vector>
#include "Reserve.h"


class Plateau {
private:
    std::vector<Reserve> m_reserve;
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

  };


////////////////////////////////////////////////////////////////////////////////////////

#endif //PLATEAU_H
