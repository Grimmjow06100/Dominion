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
    static void handleHelp(const std::string& nomCarte,  const Jeux& j);
    static void handleSell(const std::string& nomCarte,  const Jeux& j, bool buyPhase);
    static void displayMessage(const std::string& message);
    static std::string normalizeCommand(const std::string& input);

public:
    static void getInput(const Jeux& j, T& input, bool* exit = nullptr, bool buyPhase = false, const std::string& message = "");
};

template <typename T>
void GameCommand<T>::getInput(const Jeux& j, T& input, bool* exit, bool buyPhase, const std::string& message) {
    while (true) {
        std::cout << "> ";
        std::string commande;
        std::getline(std::cin, commande);

        // Normalisation de la commande
        commande = normalizeCommand(commande);

        // Vérification des commandes communes
        if (commande.find("HELP ") == 0) {
            handleHelp(commande.substr(5), j);
            continue;
        }if (commande.find("SELL ") == 0) {
            handleSell(commande.substr(5), j, buyPhase);
            continue;
        }if (commande == "INFO") {
            j.getActifPlayer().info();
            continue;
        }if (commande == "?") {
            displayMessage(message);
            continue;
        }if (commande == "BOARD") {
            j.getPlateau().affichage();
            continue;
        }if (commande == "DECK") {
            j.getActifPlayer().afficheHand();
            continue;
        }if (commande == "END") {
            if (exit) {
                *exit = true;
                break;
            }
            std::cout << "Vous ne pouvez pas terminer le tour maintenant." << std::endl;
            continue;
        }

        // Commandes spécifiques au type T
        if constexpr (std::is_same_v<T, std::string>) {
            if (commande.find("PICK ") == 0) {
                std::string nom = normalize(commande.substr(5));
                auto it = j.getPlateau().getReserve().find(nom);
                if (it != j.getPlateau().getReserve().end()) {
                    input = nom;
                    break;
                }
                std::cout << "La carte '" << nom << "' n'est pas reconnue ou n'est pas disponible dans le jeu." << std::endl;
            } else {
                std::cout << "Commande non reconnue. Essayez 'help [nomCarte]', 'pick [nomCarte]', 'board', 'deck', ?, ou 'end'." << std::endl;
            }
        } else if constexpr (std::is_same_v<T, int>) {
            try {
                input = std::stoi(commande);
                break;
            } catch (const std::invalid_argument&) {
                std::cout << "Entrée invalide. Un nombre est attendu." << std::endl;
            }
        } else {
            std::cout << "Commande non reconnue." << std::endl;
        }
    }
}

// Fonctions auxiliaires
template <typename T>
void GameCommand<T>::handleHelp(const std::string& nomCarte, const Jeux& j) {
    Plateau& plateau = j.getPlateau();
    auto it = plateau.getReserve().find(normalize(nomCarte));
    if (it != plateau.getReserve().end()) {
        Card* card = it->second.getCard();
        if (auto* treasure = dynamic_cast<TreasureCard*>(card)) {
            treasure->details();
        } else if (auto* kingdom = dynamic_cast<KingdomCard*>(card)) {
            kingdom->details();
        } else if (auto* victory = dynamic_cast<VictoryCard*>(card)) {
            victory->details();
        } else {
            std::cout << "Type de carte inconnu." << std::endl;
        }
    } else {
        std::cout << "La carte '" << nomCarte << "' n'est pas reconnue." << std::endl;
    }
}

template <typename T>
void GameCommand<T>::handleSell(const std::string& nomCarte, const Jeux& j, bool buyPhase) {
    if (!buyPhase) {
        std::cout << "Vous ne pouvez pas vendre de carte en dehors de la phase d'achat." << std::endl;
        return;
    }

    Player& player = j.getActifPlayer();
    if (nomCarte == "ALL") {
        player.sellAllTreasure();
    } else if (player.sellCard(nomCarte)) {
        std::cout << "La carte"<<nomCarte<<"a ete vendue." << std::endl;
    } else {
        std::cout << "Impossible de vendre cette carte." << std::endl;
    }
}

template <typename T>
void GameCommand<T>::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}

template <typename T>
std::string GameCommand<T>::normalizeCommand(const std::string& input) {
    // Étape 1 : Supprimer les espaces en début et en fin
    std::string result = input;
    result.erase(0, result.find_first_not_of(" \t\n\r")); // Trim début
    result.erase(result.find_last_not_of(" \t\n\r") + 1); // Trim fin

    // Étape 2 : Convertir en minuscules
    std::ranges::transform(result.begin(), result.end(), result.begin(), ::toupper);

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
