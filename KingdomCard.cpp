//
// Created by Asus on 03/11/2024.
//

#include "KingdomCard.h"
#include "Jeux.h"
#include <iostream>
#include <fstream>

#include "CardStream.h"


std::vector<KingdomCard> KingdomCard::DataCards;
KingdomCard::KingdomCard(std::string nom, int cost, bool attack, bool reaction, std::string description)
    :m_nom(std::move(nom)),m_attack(attack),m_reaction(reaction),m_description(std::move(description))
{
    m_cost=cost;
}
KingdomCard::KingdomCard(const KingdomCard& card)
    :m_nom(card.m_nom),m_attack(card.m_attack),m_reaction(card.m_reaction),m_description(card.m_description)
{
    m_cost=card.m_cost;
}


void KingdomCard::affichage()
{
    std::cout<<"Nom : "<<m_nom<<std::endl;
    std::cout<<"Cout : "<<m_cost<<std::endl;
    std::cout<<"Description : "<<m_description<<std::endl;
    if(m_attack)
    {
        std::cout<<"Carte d'attaque"<<std::endl;
    }
    if(m_reaction)
    {
        std::cout<<"Carte de reaction"<<std::endl;
    }
}

std::string KingdomCard::getNom() const
{
    return m_nom;
}

void KingdomCard::action(Jeux &j)
{
    //TODO
    Player& player=j.getActif();
    player.pioche(2);


}

void KingdomCard::GenerateKingdomFromFile(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);

    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << nomFichier << std::endl;

    }

    std::string ligne;
    std::string nom;
    int cout = 0;
    bool attack=false;
    bool reaction=false;
    std::string description;

    int ligneCompteur = 0;

    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) {
            // Créer une nouvelle carte quand une ligne vide est rencontrée
            if (!nom.empty() && !description.empty() ) {
                DataCards.emplace_back(normalize(nom),cout,attack,reaction,description);
            }
            // Réinitialiser les attributs pour la prochaine carte
            nom.clear();
            cout = 0;
            description.clear();
            ligneCompteur = 0;
        } else {
            switch (ligneCompteur) {
            case 0: nom = ligne; break;           // Ligne 1 : Nom
            case 1: cout = std::stoi(ligne); break; // Ligne 2 : Coût
            case 2:  if(ligne=="true") attack=true; else attack=false; break; // Ligne 3 : attack
            case 3: if(ligne=="true") reaction=true;else reaction=false;break;   // Ligne 3 : reaction
            case 4: description=ligne;break;
            default: break;
            }
            ligneCompteur++;
        }
    }

    // Ajouter la dernière carte si elle n'est pas vide
    if (!nom.empty() && !description.empty()) {
        DataCards.emplace_back(normalize(nom),cout,attack,reaction,description);
    }
    fichier.close();
}