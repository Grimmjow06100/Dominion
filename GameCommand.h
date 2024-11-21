//
// Created by Asus on 07/11/2024.
//

#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H
#include <algorithm>
#include <string>
#include <iostream>
#include "KingdomCard.h"
#include "Jeux.h"
#include "Reserve.h"
#include "Player.h"
#include "Plateau.h"
#include "GameCommand.h"
#include <fstream>
#include <iomanip>
#include "TreasureCard.h"
#include "VictoryCard.h"

class Jeux;

template <typename T>
class GameCommand {
     static void help(const std::string& nomCarte,Jeux const&j);
     static std::string normalizeCommand(const std::string& input);
public:
     static void getInput(Jeux const&j,T& input,bool buyPhase=false,std::string const&message="");
};
template <typename T>
void GameCommand<T>::getInput(const Jeux& j, T& input, bool buyPhase,std::string const&message)
{
    std::string commande;
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, commande);

        // Normalisation de la commande
        commande = normalizeCommand(commande);
        if constexpr (std::is_same<T,std::string>::value)
        {
            if (commande.find("pick ") == 0 ) {
                std::string nom = normalize(commande.substr(5));
                auto it = j.getPlateau().getReserve().find(nom);
                if (it != j.getPlateau().getReserve().end()) {
                    input = nom;
                    break;
                }
                std::cout << "La carte '" << nom << "' n'est pas reconnue ou n'est pas disponible dans le jeux." << std::endl;

            }
            else if (commande.find("help ") == 0) {
                std::string nomCarte = commande.substr(5);
                help(nomCarte,j);
            }
            else if(commande.find("sell ")==0)
            {
                if(buyPhase)
                {
                    std::string nom = commande.substr(5);
                    Player& p=j.getActif();
                    if(p.sellCard(nom))
                    {
                        std::cout<<"La carte a ete vendu"<<std::endl;
                    }
                    else
                        std::cout<<"impossible de vendre cette carte"<<std::endl;
                }
                else
                    std::cout<<"Vous ne pouvez pas vendre de carte en dehors de la phase d'achat"<<std::endl;
            }
            else if(commande == "info")
            {
                j.getActif().info();
            }
            else if(commande == "?")
            {
                std::cout<<message<<std::endl;
            }
            else if (commande == "board") {
                j.getPlateau().affichage();
            } else if (commande == "deck") {
                j.getActif().afficheHand();
            } else if (commande == "exit") {
                break;
            }
            else {
                std::cout<<"La commande n'est pas reconnue. Essayez 'help [nomCarte]', 'pick [nomCarte]', 'board', 'deck', ?, ou 'exit'."<<std::endl;
            }
        }
        else if constexpr (std::is_same<T,int>::value)
        {
            if (commande.find("pick ") == 0) {
                std::cout << "un nombre est attendu" << std::endl;
            }
            else if (commande.find("help ") == 0) {
                std::string nomCarte = commande.substr(5);
                help(nomCarte,j);
            }
            else if(commande.find("sell ")==0)
            {
                std::cout<<"un nombre est attendu ";
            }

            else if(commande == "info")
            {
                j.getActif().info();
            }
            else if(commande == "?")
            {
                std::cout<<message<<std::endl;
            }
            else if (commande == "board") {
                j.getPlateau().affichage();
            } else if (commande == "deck") {
                j.getActif().afficheHand();
            } else if (commande == "exit") {
                break;
            }
            else {
                try {
                    input = std::stoi(commande);
                    break;
                } catch (const std::invalid_argument&) {
                    std::cout << "Entree invalide. un nombre est attendu." << std::endl;
                }
            }
        }
    }

}

template <typename T>
void GameCommand<T>::help(const std::string& nomCarte,Jeux const&j)
{
    Plateau &p=j.getPlateau();
    if(p.getReserve().find(normalize(nomCarte))!=p.getReserve().end())
    {
        Card* c=p.getReserve().at(normalize(nomCarte)).getCard();
        if(auto* t=dynamic_cast<TreasureCard*>(c))
        {
            t->details();
        }
        else if(auto* k=dynamic_cast<KingdomCard*>(c))
        {
            k->details();
        }
        else if(auto* v=dynamic_cast<VictoryCard*>(c))
        {
            v->details();
        }
    }
    else
        std::cout<<"La carte n'est pas reconnu"<<std::endl;
}

template <typename T>
std::string GameCommand<T>::normalizeCommand(const std::string& input) {
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

#endif //GAMECOMMAND_H
