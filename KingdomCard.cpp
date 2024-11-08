//
// Created by Asus on 03/11/2024.
//

#include "KingdomCard.h"

#include <iostream>


KingdomCard::KingdomCard(Kingdom kingdom):m_kingdom(kingdom)
{
    if (m_kingdom == ATELIER || m_kingdom == BUCHERON || m_kingdom == CHANCELIER ||
    m_kingdom == RENOVATION || m_kingdom == VILLAGE) {
        m_cost = 3;
    }
    else if (m_kingdom == AVENTURIER) {
        m_cost = 6;
    }
    else if (m_kingdom == BIBLIOTHEQUE || m_kingdom == CHAMBRE_DU_CONSEIL ||
             m_kingdom == FESTIVAL || m_kingdom == LABORATOIRE ||
             m_kingdom == MARCHE || m_kingdom == MINE || m_kingdom == SORCIERE) {
        m_cost = 5;
             }
    else if (m_kingdom == BUREAUCRATE || m_kingdom == ESPION || m_kingdom == FESTIN ||
             m_kingdom == MILICE || m_kingdom == SALLE_DU_TRONE ||
             m_kingdom == VOLEUR || m_kingdom == JARDIN) {
        m_cost = 4;
             }
    else if (m_kingdom == CAVE || m_kingdom == CHAPELLE || m_kingdom == DOUVES ||
             m_kingdom == PRETEUR_SUR_GAGES) {
        m_cost = 2;
             }
    else if (m_kingdom == FORGE) {
        m_cost = 7;
    }
    else {
        m_cost = 0; // Valeur par défaut au cas où m_kingdom n'a pas de correspondance
    }

}

void KingdomCard::affichage()
{

    switch (m_kingdom) {
    case ATELIER:
        std::cout << "ATELIER " << m_cost << std::endl;
        break;
    case AVENTURIER:
        std::cout << "AVENTURIER " << m_cost << std::endl;
        break;
    case BIBLIOTHEQUE:
        std::cout << "BIBLIOTEQUE " << m_cost << std::endl;
        break;
    case BUCHERON:
        std::cout << "BUCHERON " << m_cost << std::endl;
        break;
    case BUREAUCRATE:
        std::cout << "BUREAUCRATE " << m_cost << std::endl;
        break;
    case CAVE:
        std::cout << "CAVE " << m_cost << std::endl;
        break;
    case CHANCELIER:
        std::cout << "CHANCELIER " << m_cost << std::endl;
        break;
    case CHAMBRE_DU_CONSEIL:
        std::cout << "CHAMBRE_DU_CONSEIL " << m_cost << std::endl;
        break;
    case CHAPELLE:
        std::cout << "CHAPPELLE " << m_cost << std::endl;
        break;
    case DOUVES:
        std::cout << "DOUVES " << m_cost << std::endl;
        break;
    case ESPION:
        std::cout << "ESPION " << m_cost << std::endl;
        break;
    case FESTIN:
        std::cout << "FESTIN " << m_cost << std::endl;
        break;
    case FESTIVAL:
        std::cout << "FESTIVAL " << m_cost << std::endl;
        break;
    case FORGE:
        std::cout << "FORGE " << m_cost << std::endl;
        break;
    case LABORATOIRE:
        std::cout << "LABORATOIRE " << m_cost << std::endl;
        break;
    case MARCHE:
        std::cout << "MARCHE " << m_cost << std::endl;
        break;
    case MILICE:
        std::cout << "MILICE " << m_cost << std::endl;
        break;
    case MINE:
        std::cout << "MINE " << m_cost << std::endl;
        break;
    case PRETEUR_SUR_GAGES:
        std::cout << "PRETEUR_SUR_GAGE " << m_cost << std::endl;
        break;
    case RENOVATION:
        std::cout << "RENOVATION " << m_cost << std::endl;
        break;
    case SALLE_DU_TRONE:
        std::cout << "SALLE_DU_TRONE " << m_cost << std::endl;
        break;
    case SORCIERE:
        std::cout << "SORCIERE " << m_cost << std::endl;
        break;
    case VILLAGE:
        std::cout << "VILLAGE " << m_cost << std::endl;
        break;
    case VOLEUR:
        std::cout << "VOLEUR " << m_cost << std::endl;
        break;
    case JARDIN:
        std::cout << "JARDIN " << m_cost << std::endl;
        break;
    default:
        std::cout << "Carte inconnue" << std::endl;
        break;
    }


}

Kingdom KingdomCard::getKingdom() const
{
    return m_kingdom;
}

void KingdomCard::action(Player &p)
{
    //TODO
}






/*
    if(m_kingdom==ATELIER)
        std::cout<<"Atelier : +1 carte +1 action"<<std::endl;
    else if(m_kingdom==AVENTURIER)
        std::cout<<"Aventurier : Piochez jusqu'à 2 cartes de votre deck. Révélez ces cartes et placez les cartes de trésor et de victoire dans votre main. Remettez les autres cartes sur votre deck dans l'ordre de votre choix."<<std::endl;
    else if(m_kingdom==BIBLIOTHEQUE)
        std::cout<<"Bibliothèque : Piochez jusqu'à 7 cartes. Pour chaque carte Action piochée, défaussez-la ou mettez-la sur votre deck. Pour chaque carte Trésor ou Victoire piochée, mettez-la sur votre deck."<<std::endl;
    else if(m_kingdom==BUCHERON)
        std::cout<<"Bûcheron : +1 achat +2 pièces"<<std::endl;
    else if(m_kingdom==BUREAUCRATE)
        std::cout<<"Bureaucrate : Piochez une carte Argent. Chaque autre joueur dévoile une carte Victoire de sa main et la met sur son deck (ou révèle une main sans carte Victoire)."<<std::endl;
    else if(m_kingdom==CAVE)
        std::cout<<"Cave : +1 carte +2 actions Défaussez autant de cartes que vous voulez. Pour chaque carte défaussée de cette façon, piochez une carte."<<std::endl;
    else if(m_kingdom==CHANCELIER)
        std::cout<<"Chancelier : Vous pouvez immédiatement défausser votre deck. Si vous le faites, vous pouvez regarder les cartes de votre deck et les remettre dans l'ordre de votre choix."<<std::endl;
    else if(m_kingdom==CHAMBRE_DU_CONSEIL)
        std::cout<<"Chambre du Conseil : +1 carte +1 action +1 achat +1 pièce"<<std::endl;
    else if(m_kingdom==CHAPELLE)
        std::cout<<"Chapelle : Écartez jusqu'à 4 cartes de votre main."<<std::endl;
    else if(m_kingdom==DOUVES)
        std::cout<<"Douves : +2 cartes +1 action Lorsqu'un autre joueur joue une carte Attaque, vous pouvez dévoiler cette carte de votre main. Si vous le faites, vous n'êtes pas affecté par l'Attaque."<<std::endl;
    else if(m_kingdom==ESPION)
        std::cout<<"Espion : +1 carte +1 action Chaque joueur dévoile la première carte de son deck. Si c'est une carte Action ou Trésor, le joueur la défausse. Si c'est une carte Victoire, le joueur la montre et la remet sur son deck."<<std::endl;
    else if(m_kingdom==FESTIN)
        std::cout<<"Festin : Gagnez une carte coûtant jusqu'à 5 pièces."<<std::endl;
    else if(m_kingdom==FESTIVAL)
       std::cout<<"Festival : +2 actions +1 achat +2 pièces"<<std::endl;
    else if(m_kingdom==FORGE)
       std::cout<<"Forge : Écartez des cartes de votre main d'une valeur totale de 3 pièces ou plus. Gagnez une carte coûtant jusqu'à 3 pièces de plus que la valeur totale des cartes écartées."<<std::endl;
    else if(m_kingdom==LABORATOIRE)
        std::cout<<"Laboratoire : +2 cartes +1 action"<<std::endl;
    else if(m_kingdom==MARCHE)
       std::cout<<"Marché : +1 carte +1 action +1 achat +1 pièce"<<std::endl;
    else if(m_kingdom==MILICE)
        std::cout<<"Milice : +2 pièces Chaque autre joueur défausse en premier vers le bas sa main pour ne conserver que 3 cartes."<<std::endl;
    else if(m_kingdom==MINE)
      std::cout<<"Mine : Écartez une carte Trésor de votre main. Gagnez une carte Trésor coûtant jusqu'à 3 pièces de plus que la carte écartée."<<std::endl;
    else if(m_kingdom==PRETEUR_SUR_GAGES)
        std::cout<<"Prêteur sur gages : +1 pièce +1 action Défaussez une carte Cuivre de votre main. Dans ce cas, +3 pièces."<<std::endl;
    else if(m_kingdom==RENOVATION)
        std::cout<<"Rénovation : Écartez une carte de votre main. Gagnez une carte coûtant jusqu'à 2 pièces de plus que la carte écartée."<<std::endl;
    else if(m_kingdom==SALLE_DU_TRONE)
        std::cout<<"Salle du Trône : Choisissez une carte Action de votre main. Jouez-la deux fois."<<std::endl;
    else if(m_kingdom==SORCIERE)
        std::cout<<"Sorcière : +2 cartes Chaque autre joueur gagne une Malédiction."<<std::endl;
    else if(m_kingdom==VILLAGE)
        std::cout<<"Village : +1 carte +2 actions"<<std::endl;
    else if(m_kingdom==VOLEUR)
        std::cout<<"Voleur : Chaque autre joueur révèle les 2 premières cartes de son deck. S'il révèle des cartes Trésor, il en écarte une de votre choix. S'il n'en révèle pas, ou s'il n'a plus de cartes dans son deck, il gagne une Malédiction."<<std::endl;
    else if(m_kingdom==JARDIN)
        std::cout<<"Jardin : Vale 1 point de victoire pour chaque groupe de 10 carte dans votre deck (arrondi à l'unité supérieure)."<<std::endl;
    */