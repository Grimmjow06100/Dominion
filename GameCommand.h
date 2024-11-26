//
// Created by Asus on 07/11/2024.
//

#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H
#include <string>
#include <iostream>
#include <vector>

#include "Player.h"

class Player;



class Jeux;

/**
 * enum pour gerer les phases actuelles de la partie
 */
enum Phase {ACTION,BUY,NONE};

/**
 * Classe permettant de gerer les interaction avec les utilisateur
 */
class GameCommand {
    /**
     * Traite les entrees clavier "help" des joueurs
     * @param nomCarte
     * @param j
     */
    static void handleHelp(const std::string& nomCarte,  const Jeux& j);

    /**
     * Traite les ventes de pieces des joueurs
     * @param nomCarte
     * @param j
     * @param phase
     */
    static void handleSell(const std::string& nomCarte,  const Jeux& j, Phase phase);

    /**
     * Traite l'utilisation d'une carte royaume durant la phase action
     * @param nomCarte
     * @param j
     * @param phase
     */
    static void handlePlay(const std::string& nomCarte,  Jeux& j, Phase phase);

    /**
     * Traite l'achat d'une carte
     * @param nomCarte
     * @param j
     * @param phase
     */
    static void handleBuy(const std::string& nomCarte,  Jeux& j, Phase phase);

    /**
     * Traite les entrees clavier "info" du joueur sur le terminal
     * @param j
     */
    static void handleInfo(const Jeux& j);

    /**
     * Selectionne une carte :
     * renvoie le nom de la carte qu'un joueur tape dans le clavier apres un pick
     * @param nomCarte
     * @param j
     * @return
     */
    static std::string handlePick(const std::string& nomCarte,  const Jeux& j);

    /**
     * Affiche un message dans le terminal
     * @param message
     */
    static void displayMessage(const std::string& message);

    /**
     * Normalise la commande tape par le joueur dans le terminal
     * @param input
     * @return
     */
    static std::string normalizeCommand(const std::string& input);

public:
    /**
     * Permet de gerer les entree clavier de l'utilisateur
     * @param j le jeu en cours
     * @param phase la phase actuelle du jeu
     * @param exitOption option pour quitter la phase du jeu
     * @param cardNameOption pointeur de string qui va stocker le nom de la carte tape par le joueur
     * @param otherInput
     */
    static void getInput( Jeux& j, Phase phase=NONE ,bool* exitOption =nullptr,std::string* cardNameOption=nullptr,std::string* otherInput=nullptr);
};




#endif //GAMECOMMAND_H
