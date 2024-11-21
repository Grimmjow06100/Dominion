//
// Created by Asus on 07/11/2024.
//

#include "GameCommand.h"

#include <algorithm>
#include <iostream>

#include "Card.h"
#include "Jeux.h"
#include "Plateau.h"
#include "TreasureCard.h"
#include "KingdomCard.h"
#include "Player.h"
#include "VictoryCard.h"
#include <sstream>

void GameCommand::getInput(const Jeux& j, int& nombre)  {
    std::string commande;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, commande);

        // Normalisation de la commande
        commande = normalizeCommand(commande);

        if (commande.empty()) {
            std::cout << "Commande vide. Veuillez réessayer." << std::endl;
            continue;
        }

        if (commande.find("help ") == 0) {
            std::string nomCarte = commande.substr(5);
            help(nomCarte, j);
        } else if (commande.find("pick ") == 0) {
            std::cout << "Vous devez saisir un nombre et non pas une carte" << std::endl;
        } else if (commande == "board") {
            j.getPlateau().affichage();
        } else if (commande == "deck") {
            j.getActif().afficheHand();
        } else if (commande == "cancel") {
            break;
        } else {
            try {
                nombre = std::stoi(commande);
                break;
            } catch (const std::invalid_argument&) {
                std::cout << "Entrée invalide. Veuillez saisir un nombre." << std::endl;
            }
        }
    }
}


// Recupération du nom de la carte saisi par le joueur
void GameCommand::getInput(Jeux const&j,std::string& cardName,bool buyPhase) {
    std::string commande;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, commande);

        // Normalisation de la commande
        commande = normalizeCommand(commande);

        if (commande.empty()) {
            std::cout << "Commande vide. Veuillez reessayer." << std::endl;
            continue;
        }
        if (commande.find("help ") == 0) {
            std::string nomCarte = commande.substr(5);
            help(nomCarte,j);
        } else if (commande.find("pick ") == 0 ) {
            std::string nom = normalize(commande.substr(5));
            auto it = j.getPlateau().getReserve().find(nom);

            if (it != j.getPlateau().getReserve().end()) {
                cardName = nom;
                break;
            }
            std::cout << "La carte '" << nom << "' n'est pas reconnue ou n'est pas disponible dans le jeux." << std::endl;

        }
        else if(commande.find("sell ")==0)
        {
            if(buyPhase)
            {
                std::string nom = commande.substr(5);
                Player& p=j.getActif();
                bool success=p.sellCard(nom);
                if(success)
                {
                    std::cout<<"La carte a ete vendu"<<std::endl;
                }
                else
                    std::cout<<"impossible de vendre cette carte"<<std::endl;
            }
            else
                std::cout<<"vous ne pouvez pas vendre de carte tresor en dehors de la phase d'achat"<<std::endl;
        }
        else if (commande == "board") {
            j.getPlateau().affichage();
        } else if (commande == "deck") {
            j.getActif().afficheHand();
        } else if (commande == "exit") {
            break;
        } else {
            std::cout << "Commande non reconnue. Essayez 'help [nomCarte]', 'pick [nomCarte]', 'board', 'deck', ou 'exit'." << std::endl;
        }
    }
}


void GameCommand::help(const std::string& nomCarte,Jeux const&j)
{
    Plateau &p=j.getPlateau();
    if(p.getReserve().find(normalize(nomCarte))!=p.getReserve().end())
    {
        Card* c=p.getReserve().at(normalize(nomCarte)).getCard();
        if(auto* t=dynamic_cast<TreasureCard*>(c))
        {
            t->affichage();
        }
        else if(auto* k=dynamic_cast<KingdomCard*>(c))
        {
            k->affichage();
        }
        else if(auto* v=dynamic_cast<VictoryCard*>(c))
        {
            v->affichage();
        }
    }
    else
        std::cout<<"La carte n'est pas reconnu"<<std::endl;
}

std::string GameCommand::normalizeCommand(const std::string& input) {
    // Étape 1 : Supprimer les espaces en début et en fin
    std::string result = input;
    result.erase(0, result.find_first_not_of(" \t\n\r")); // Trim début
    result.erase(result.find_last_not_of(" \t\n\r") + 1); // Trim fin

    // Étape 2 : Convertir en minuscules
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);

    // Étape 3 : Réduire les espaces multiples à un seul espace
    std::istringstream iss(result);
    std::ostringstream oss;
    std::string word;
    bool firstWord = true;

    while (iss >> word) {
        if (!firstWord) oss << " ";
        oss << word;
        firstWord = false;
    }

    return oss.str();
}





