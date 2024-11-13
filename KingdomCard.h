//
// Created by Asus on 03/11/2024.
//

#ifndef KINGDOMCARD_H
#define KINGDOMCARD_H
#include <string>
#include <vector>
#include "Card.h"
#include <map>




class KingdomCard : public Card{
private:
    bool m_attack;
    bool m_reaction;
    std::string m_description;
public :
    static std::vector<KingdomCard> DataCards;
    static std::map<std::string,KingdomCard> KingdomCardMap;
    static void GenerateKingdomFromFile(const std::string& nomFichier);


    KingdomCard(std::string nom,int cost,bool attack,bool reaction,std::string description);
    KingdomCard(KingdomCard const& card);
    KingdomCard();
    ~KingdomCard() override = default;
    KingdomCard& operator=(KingdomCard const& other) ;

    void affichage() override;
    void action(Jeux &j) override;

    [[nodiscard]] std::string getNom()const;
};



#endif //KINGDOMCARD_H
