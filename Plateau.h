//
// Created by Asus on 13/11/2024.
//

#ifndef PLATEAU_H
#define PLATEAU_H
#include <map>
#include <string>
#include <vector>

#include "Reserve.h"
class Jeux;

class Plateau {
    std::map<std::string,Reserve>m_reserve;
    int m_cuivre;
    int m_argent;
    int m_or;
    int m_victory;
    int m_kingdom;
    int m_curse;
public :
    void affichage();
    explicit Plateau (int nbrJoueur);
    void built();
    void built(std::vector<std::string> choice);
    [[nodiscard]]bool isEmpty()const;
    void updateReserveByName(const std::string& cardName,int nbr);
    std::map<std::string,Reserve>& getReserve();

  };
inline std::vector<std::string>BaseBoard ={"atelier","bucheron","village","festin","laboratoire","douves","jardins","chapelle","voleur","sorciere"};

inline std::vector<std::string>bonus = {"festival","bandit","marche","manufacture","preteur","chancelier","salle_duconseil","messager","vassal","braconnier"};


#endif //PLATEAU_H
