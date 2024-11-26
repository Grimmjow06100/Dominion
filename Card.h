//
// Created by Asus on 03/11/2024.
//

#ifndef CARD_H
#define CARD_H
#include <string>
#include <vector>

class Jeux;

/*Classe representant une classe du jeu dominion*/
class Card{
protected:
    std::string m_nom;//son nom
    int m_cost=0;//son cout


public:
    /**
     * Constructeur de Card
     * @param nom
     * @param cost
     */
    Card(std::string nom,int cost);

    /**
     * Permet d'afficher des cartes dans le terminal
     * @param cards un vecteur de pointeur de cartes
     */
    static void afficheCards(const std::vector<Card*>& cards);

    /**
     * Destructeur de carte
     */
    virtual ~Card()=default;

    /**
     * Methode virtuelle de l'affichage d'une carte
     */
    virtual void affichage()const=0;

    /**
     * Methode virtuelle de l'affichage des details d'une carte
     */
    virtual void details()const=0;

    /**
     * accesseur de cout
     * @return
     */
    [[nodiscard ]] int getCost() const;

    /**
     * accesseur de nom
     * @return
     */
    [[nodiscard]] std::string getNom() const;
};

/**
 * Normalise une chaine de caractere
 * @param s une chaine de caractere passe par reference
 * @return la chaine de caractere apres normalisation
 */
std::string normalize(const std::string& s);

/**
 * Affiche un message sous forme de notification
 * @param message
 */
void notif(std::string const& message);

/**
 * Affiche un message sous forme d'alerte
 * @param message
 */
void alert(std::string const& message);

/**
 * Permet a l'utiliateur d'appuyer sur une touche avant de continuer
 */
void appuyerPourContinuer();

#endif //CARD_H
