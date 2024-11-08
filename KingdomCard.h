//
// Created by Asus on 03/11/2024.
//

#ifndef KINGDOMCARD_H
#define KINGDOMCARD_H
#include "Card.h"
#include "Player.h"

enum Kingdom
{
    ATELIER,
    AVENTURIER,
    BIBLIOTHEQUE,
    BUCHERON,
    BUREAUCRATE,
    CAVE,
    CHANCELIER,
    CHAMBRE_DU_CONSEIL,
    CHAPELLE,
    DOUVES,
    ESPION,
    FESTIN,
    FESTIVAL,
    FORGE,
    LABORATOIRE,
    MARCHE,
    MILICE,
    MINE,
    PRETEUR_SUR_GAGES,
    RENOVATION,
    SALLE_DU_TRONE,
    SORCIERE,
    VILLAGE,
    VOLEUR,
    JARDIN,

};



class KingdomCard : public Card{
private:
    Kingdom m_kingdom;
public :
    explicit KingdomCard(Kingdom kingdom);
    [[nodiscard]] Kingdom getKingdom()const;

    void affichage() override;
    void action(Player &p) override;
};



#endif //KINGDOMCARD_H
