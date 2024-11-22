
#include <fstream>
#include <iostream>
#include "Player.h"
#include "KingdomCard.h"
#include "Jeux.h"
/*
*Liste des commandes disponibles :
Commande	Description
PICK [nomCarte]	Permet de choisir une carte par son nom dans la réserve. Si la carte n'est pas reconnue, un message d'erreur s'affiche.
HELP [nomCarte]	Affiche les détails d'une carte spécifique (Royaume, Trésor, ou Victoire) disponible dans la réserve.
SELL [nomCarte]	Permet de vendre une carte trésor lors de la phase d'achat. Si ALL est spécifié, toutes les cartes trésor sont vendues.
INFO	Affiche des informations détaillées sur l'état du joueur actif (main, trésors, actions restantes, etc.).
?	Affiche un message personnalisé (dépendant de la phase ou de l'étape en cours du jeu).
BOARD	Affiche l'état actuel du plateau de jeu (contenu de la réserve, cartes disponibles, etc.).
DECK	Affiche la main du joueur actif (les cartes en main).
END	Termine le tour en cours, si la phase et les règles le permettent. Sinon, affiche un message d'erreur.
COMMAND NON RECONNUE	Si une commande non valide est saisie, un message d'erreur s'affiche avec des suggestions de commandes valides.
 *
 *
 **/

int main()
{
    std::system("cls");
    Player p("samy");
    KingdomCard::GenerateKingdomFromFile("royaume.txt");
    Jeux j;
    j.initGame("samy","yohan");

    j.playGame();


    return 0;
}
