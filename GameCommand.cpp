//
// Created by Asus on 07/11/2024.
//

#include "GameCommand.h"

#include "KingdomCard.h"
#include "Jeux.h"
#include "Reserve.h"
#include "Player.h"
#include "Plateau.h"
#include <fstream>
#include <iomanip>
#include "TreasureCard.h"
#include "VictoryCard.h"



void GameCommand::getInput(Jeux& j,Phase phase,bool* exitOption, const std::string& messageOption,std::string* cardNameOption) {
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
        }if (commande.find("SELL ") == 0)
        {
            handleSell(commande.substr(5), j, phase);
            continue;
        }if(commande.find("BUY ") == 0){
            handleBuy(commande.substr(4), j, phase);
            break;
        }
        if(commande.find("PLAY ") == 0){
            handlePlay(commande.substr(5), j, phase);
            break;
        }if(commande.find("PICK ") == 0)
        {
            if(cardNameOption==nullptr)
            {
                std::cout<<"Commande indisponible"<<std::endl;
                continue;
            }
            *cardNameOption=handlePick(commande.substr(5), j);
            break;
        }
        if (commande == "INFO") {
            j.getActifPlayer().info();
            continue;
        }if (commande == "?") {
            displayMessage(messageOption);
            continue;
        }if (commande == "BOARD") {
            j.getPlateau().affichage();
            continue;
        }if (commande == "DECK") {
            j.getActifPlayer().afficheHand();
            continue;
        }if (commande == "END")
        {
            if (exitOption==nullptr) {
                std::cout << "Vous ne pouvez pas terminer le tour maintenant." << std::endl;
                continue;
            }
            *exitOption = true;
            break;
        }
        std::cout << "Commande non reconnue. Essayez 'help [nomCarte]', 'pick [nomCarte]',play [nomCarte],buy[nomCarte], 'board', 'deck', ou 'end'." << std::endl;
    }
}

void GameCommand::handleHelp(const std::string& nomCarte, const Jeux& j) {
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

std::string GameCommand::handlePick(const std::string& nomCarte, const Jeux& j) {
    Plateau& p=j.getPlateau();
    auto it=p.getReserve().find(normalize(nomCarte));
    if(it!=p.getReserve().end())
    {
        return nomCarte;
    }
    std::cout<<"carte inexistant"<<std::endl;
    return "";
}



void GameCommand::handleBuy(const std::string& nomCarte, Jeux& j, Phase phase) {
    if (phase!=BUY) {
        std::cout << "Commande indisponible" << std::endl;
        return;
    }

    Player& player = j.getActifPlayer();
    player.buyCard(nomCarte,j);
}


void GameCommand::handlePlay(const std::string& nomCarte, Jeux& j, Phase phase) {
    if (phase!=ACTION) {
        std::cout << "Commande indisponible " << std::endl;
        return;
    }

    Player& player = j.getActifPlayer();
    player.playAction(nomCarte,j);


}

void GameCommand::handleSell(const std::string& nomCarte, const Jeux& j, Phase phase) {
    if (phase!=BUY) {
        std::cout << "Commande indisponible" << std::endl;
        return;
    }

    Player& player = j.getActifPlayer();
    if (nomCarte == "ALL") {
        player.sellAllTreasure();
    }
    player.sellCard(nomCarte);
}


void GameCommand::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}


std::string GameCommand::normalizeCommand(const std::string& input) {
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