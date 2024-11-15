//
// Created by Asus on 03/11/2024.
//

#include "KingdomCard.h"
#include "Jeux.h"
#include <iostream>
#include <fstream>
#include "CardStream.h"
#include "Reserve.h"



std::vector<KingdomCard> KingdomCard::DataCards;
std::map<std::string,KingdomCard> KingdomCard::KingdomCardMap;


KingdomCard::KingdomCard(std::string nom, int cost, bool attack, bool reaction, std::string description)
    :Card(std::move(nom),cost),m_attack(attack),m_reaction(reaction),m_description(std::move(description))
{}
KingdomCard::KingdomCard()
    : Card("",0), m_attack(false), m_reaction(false), m_description("")
{}
KingdomCard::KingdomCard(KingdomCard const&card)
    :Card(card.m_nom,card.m_cost),m_attack(card.m_attack),m_reaction(card.m_reaction),m_description(card.m_description)
{}

KingdomCard& KingdomCard::operator=(KingdomCard const& other) {
    if (this != &other) {  // Vérification d'auto-affectation
        m_nom = other.m_nom;
        m_cost = other.m_cost;
        m_attack = other.m_attack;
        m_reaction = other.m_reaction;
        m_description = other.m_description;
    }
    return *this;
}


void KingdomCard::affichage()
{
    std::cout<<normalize(m_nom)<<" "<<m_cost<<std::endl;
    std::cout<<m_description<<std::endl;
    if(m_attack)
    {
        std::cout<<"ACTION-ATTAQUE"<<std::endl;
    }
    else if(m_reaction)
    {
        std::cout<<"ACTION-REACTION"<<std::endl;
    }
    else if(normalize(m_nom)== "JARDINS")
    {
        std::cout<<"VICTOIRE"<<std::endl;
    }
    else
        std::cout<<"ACTION"<<std::endl;
    std::cout<<"---------------------------------"<<std::endl;
}

std::string KingdomCard::getNom() const
{
    return m_nom;
}

void KingdomCard::action(Jeux &j)
{
    //TODO
    //Player& player=j.getActif();
    //player.pioche(2);

    if(m_nom == "ARTISAN") {
        std::cout<<"cas artisan"<<std::endl;
        std::cout<<"Choisissez une carte :"<< std::endl;

        CardStream card;
        card.streamCard();
        /*Card* carteChoisi = card.getStream();
        for (const auto& i : j.getReserve()) {
            //trouver un moyen de lier a la carte reserve pour voir le nb de carte
        }
        while(carteChoisi == nullptr or carteChoisi->getCost()>5) {
            card.streamCard();
            carteChoisi = card.getStream();
            std::cout<<"Choisissez une autre carte :"<< std::endl;
        }*/
        //deplacement carte


    }
        //Gagnez une carte coûtant jusqu'à 5 pièces
        //dans votre main. Placez une carte de votre main sur votre deck.
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
                KingdomCardMap[normalize(nom)] = KingdomCard(nom, cout, attack, reaction, description);
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
        KingdomCardMap[normalize(nom)] = KingdomCard(nom, cout, attack, reaction, description);
    }
    fichier.close();
}