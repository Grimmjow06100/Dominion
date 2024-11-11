//
// Created by Asus on 03/11/2024.
//

#ifndef KINGDOMCARD_H
#define KINGDOMCARD_H
#include <string>
#include <vector>

#include "Card.h"



class KingdomCard : public Card{
private:
    std::string m_nom;
    bool m_attack;
    bool m_reaction;
    std::string m_description;
public :
    static std::vector<KingdomCard> DataCards;
    static void GenerateKingdomFromFile(const std::string& nomFichier);

    KingdomCard(std::string nom,int cost,bool attack,bool reaction,std::string description);
    KingdomCard(KingdomCard& card);
    ~KingdomCard() override = default;

    void affichage() override;
    void action(Jeux &j) override;

    [[nodiscard]] std::string getNom()const;
};



#endif //KINGDOMCARD_H
