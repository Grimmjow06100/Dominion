//
// Created by Asus on 13/11/2024.
//

#include "Plateau.h"
#include "KingdomCard.h"
#include <iostream>
#include "VictoryCard.h"
#include "CardStream.h"
#include "TreasureCard.h"
#include <iomanip>

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

std::vector<std::string> base ={"atelier","bucheron","village","festin","laboratoire","douves","jardins","chapelle","bandit","sorciere"};

void triCartes(std::vector<std::tuple<std::string, int, std::string, std::string, std::string>>& cartes) {
    // Fonction pour attribuer une priorité basée sur le type
    auto getPriority = [](const std::string& type) {
        if (type == "Victoire") return 0;
        if (type == "Tresor") return 1;
        if (type == "Royaume") return 2;
        return 3;  // Type inconnu ou par défaut
    };

    // Trier les cartes en utilisant std::sort
    std::sort(cartes.begin(), cartes.end(), [&](const auto& a, const auto& b) {
        return getPriority(std::get<2>(a)) < getPriority(std::get<2>(b));
    });
}

void Plateau::affichePlateau() {
    constexpr int maxCartesParLigne = 5;  // Maximum de cartes par ligne
    const auto& reserves = this->getReserveMap();  // Nombre total de cartes

    std::cout << "______________________________________ RESERVE _________________________________________" << std::endl;
    std::vector<std::tuple<std::string, int, std::string, std::string, std::string>> cartes;

    for (const auto& [nomCarte, reserve] : reserves) {
        if (reserve.getCard()) {  // Vérifiez que la carte n'est pas nulle
            std::string type;
            std::string extraInfo;
            std::string colorCode;
            Card* card = reserve.getCard();

            if (dynamic_cast<KingdomCard*>(card)) {
                type = "Royaume";
                extraInfo = "FONCTION ";
                colorCode = "\033[34m";  // Bleu pour Royaume
            } else if (auto* treasureCard = dynamic_cast<TreasureCard*>(card)) {
                type = "Tresor";
                extraInfo = "Value : " + std::to_string(treasureCard->getTreasure());
                colorCode = "\033[33m";  // Jaune pour Trésor
            } else if (auto* victoryCard = dynamic_cast<VictoryCard*>(card)) {
                type = "Victoire";
                extraInfo = "Value : " + std::to_string(victoryCard->getVictory());
                colorCode = "\033[32m";  // Vert pour Victoire
            } else {
                type = "Inconnu";
                extraInfo = "N/A";
                colorCode = "\033[0m";  // Réinitialiser pour inconnu
            }

            cartes.emplace_back(colorCode + card->getNom() + "\033[0m", card->getCost(), type, extraInfo, colorCode);
        }
    }

    // Affichage des cartes
    triCartes(cartes);
    const size_t totalCartes = cartes.size();

    for (size_t i = 0; i < totalCartes; i += maxCartesParLigne) {
        // Bordures supérieures des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m+--------------+\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le nom des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(22) << std::left
                      << std::get<0>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le type des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m Type:" << std::setw(8) << std::left
                      << std::get<2>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant le coût des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m Cout: " << std::setw(7) << std::left
                      << std::get<1>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Ligne contenant les informations supplémentaires
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m|\033[0m " << std::setw(13) << std::left
                      << std::get<3>(cartes[j]) << "\033[31m|\033[0m  ";
        }
        std::cout << std::endl;

        // Bordures inférieures des cartes
        for (size_t j = i; j < i + maxCartesParLigne && j < totalCartes; ++j) {
            std::cout << "\033[31m+--------------+\033[0m  ";
        }
        std::cout << std::endl << std::endl;  // Espace entre les rangées de cartes
    }

}

Plateau::Plateau( int nbrJoueur):m_cuivre(60),m_argent(40),m_or(30)
{
    if(nbrJoueur==2)
    {
        m_victory=8;
        m_kingdom=10;
        m_curse=10;
    }
    else if(nbrJoueur==3)
    {
        m_victory=12;
        m_kingdom=12;
        m_curse=20;
    }
    else if(nbrJoueur==4)
    {
        m_victory=12;
        m_kingdom=12;
        m_curse=30;
    }
    else
    {
        m_victory=0;
        m_kingdom=0;
        m_curse=0;
    }
}
void Plateau::built()
{
    m_reserveMap["CUIVRE"]=Reserve(TreasureCard("CUIVRE"),m_cuivre);
    m_reserveMap["ARGENT"]=Reserve(TreasureCard("ARGENT"),m_argent);
    m_reserveMap["OR"]=Reserve(TreasureCard("OR"),m_or);
    m_reserveMap["DOMAINE"]=Reserve(VictoryCard("DOMAINE"),m_victory);
    m_reserveMap["DUCHE"]=Reserve(VictoryCard("DUCHE"),m_victory);
    m_reserveMap["PROVINCE"]=Reserve(VictoryCard("PROVINCE"),m_victory);
    m_reserveMap["MALEDICTION"]=Reserve(VictoryCard("MALEDICTION"),m_curse);
    for(auto &i : base)
    {
        auto it = KingdomCard::KingdomCardMap.find(normalize(i));
        if (it != KingdomCard::KingdomCardMap.end())
        {
            m_reserveMap[it->second.getNom()]=Reserve(it->second, normalize(i) == "JARDIN" ? m_victory:m_kingdom);
        }

    }



}

bool Plateau::isEmpty() const
{
    int count=0;
    if(m_reserveMap.at("PROVINCE").isEmpty())
        return true;
    for(auto &it : m_reserveMap)
    {

        if(it.second.isEmpty())
            count++;
        if(count==3)
            return true;
    }
    return false;
}

void Plateau::affichage()const
{
    std::cout<<"//////////////////////////////////////////////RESERVE//////////////////////////////////////////////"<<std::endl;
    for(auto &it:m_reserveMap)
    {
        it.second.affichage();
    }
    std::cout<<"//////////////////////////////////////////////FIN RESERVE//////////////////////////////////////////////"<<std::endl;
}

void Plateau::updateReserve(const std::string& cardName,int nbr)
{
    m_reserveMap.at(cardName).setTaille(m_reserveMap.at(cardName).getTaille()-nbr);
}
std::unordered_map<std::string,Reserve>& Plateau::getReserveMap()
{
    return m_reserveMap;
}