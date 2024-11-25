//
// Created by Asus on 03/11/2024.
//

#include "KingdomCard.h"
#include "Jeux.h"
#include "Player.h"
#include "Plateau.h"
#include "GameCommand.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "TreasureCard.h"



std::vector<KingdomCard> KingdomCard::DataCards;
std::map<std::string,KingdomCard> KingdomCard::KingdomCardMap;




KingdomCard::KingdomCard(std::string nom, int cost, bool attack, bool reaction, std::string description,int cards,int actions,int coins,int buys)
    :Card(std::move(nom),cost),m_attack(attack),m_reaction(reaction),m_description(std::move(description)),m_cards(cards),m_actions(actions),m_coins(coins),m_buys(buys)
{}
KingdomCard::KingdomCard()
    : Card("",0), m_attack(false), m_reaction(false),m_cards(0),m_actions(0),m_coins(0),m_buys(0)
{}
KingdomCard::KingdomCard(KingdomCard const&card)
    :Card(card.m_nom,card.m_cost),m_attack(card.m_attack),m_reaction(card.m_reaction),m_description(card.m_description),m_cards(card.m_cards),m_actions(card.m_actions),m_coins(card.m_coins),m_buys(card.m_buys)
{}

KingdomCard& KingdomCard::operator=(KingdomCard const& other) {
    if (this != &other) {  // Vérification d'auto-affectation
        m_nom = other.m_nom;
        m_cost = other.m_cost;
        m_attack = other.m_attack;
        m_reaction = other.m_reaction;
        m_description = other.m_description;
        m_cards = other.m_cards;
        m_actions = other.m_actions;
        m_coins = other.m_coins;
        m_buys = other.m_buys;
    }
    return *this;
}

void KingdomCard::affichage() const{
    std::string type=actionType(*this);
    std::cout << "\033[31m+--------------+\033[0m\n";
    std::cout << "\033[31m|\033[0m " << std::setw(13) << std::left << m_nom << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Type: " << std::setw(7) << type << "\033[31m|\033[0m\n";
    std::cout << "\033[31m|\033[0m Cout: " << std::setw(7) << m_cost << "\033[31m|\033[0m\n";
    std::cout << "\033[31m+--------------+\033[0m\n";
}

void KingdomCard::details()const
{
    std::string type=actionType(*this);
    std::cout<<"Nom : "<<m_nom<<std::endl;
    std::cout<<"Type : "<<type<<std::endl;
    std::cout<<"Cout : "<<m_cost<<std::endl;
    std::cout<<"Description : "<<m_description<<std::endl;
}

std::string KingdomCard::actionType(KingdomCard const&k)
{

    if(k.isAttack())
    {
        return "ACTION-ATTAQUE";
    }
    if(k.isReaction())
    {
        return "ACTION-REACTION";
    }
    if(k.getNom()== "JARDINS")
    {
        return "VICTOIRE";
    }
    return "ACTION";

}

void KingdomCard::action(Jeux &j) {
    Player& player=j.getActifPlayer();
    if(m_actions or m_coins or m_buys or m_cards) {
        player.AddAction(m_actions);
        player.AddCoin(m_coins);
        player.AddBuy(m_buys);
        player.pioche(m_cards);
        if(m_actions)
        {
            std::string action=m_actions>1?" actions":" action";
            notif("Vous avez gagne "+std::to_string(m_actions)+action);
        }
        if(m_coins)
        {
            std::string coin=m_coins>1?" pieces":" piece";
            notif("Vous avez gagne "+std::to_string(m_coins)+coin);
        }
        if(m_buys)
        {
            std::string buy=m_buys>1?" achats":" achat";
            notif("vous avez gagne "+std::to_string(m_buys)+buy);
        }
        if(m_cards)
        {
            std::string card=m_cards>1?" cartes":" carte";
            notif("vous piochez "+std::to_string(m_cards)+card);
        }
    }
    if(m_nom=="ATELIER")
    {
        Atelier(j);
    }
    else if(m_nom=="CAVE")
    {

        Cave(j);
    }
    else if(m_nom=="JARDINS")
    {
        Jardins(player);
    }
    else if(m_nom=="BANDIT")
    {
        Bandit(j);
    }
    else if(m_nom=="SORCIERE")
    {
        Sorciere(j);
    }
    else if(m_nom=="CHAPELLE")
    {
        Chapelle(j);
    }
    else if(m_nom=="MESSAGER")
    {
        Messager(j);
    }
    else if(m_nom=="VASSAL")
    {
        Vassal(j);
    }
}


void KingdomCard::GenerateKingdomFromFile(const std::string& nomFichier) {
    std::ifstream fichier(nomFichier);

    if (!fichier) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << nomFichier << std::endl;

    }

    std::string ligne;
    std::string nom;
    int cout;
    bool attack;
    bool reaction;
    std::string description;
    int cards;
    int actions;
    int coins;
    int buys;

    int ligneCompteur=0;

    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) {
            // Créer une nouvelle carte quand une ligne vide est rencontrée
            if (!nom.empty() && !description.empty() ) {
                DataCards.emplace_back(normalize(nom),cout,attack,reaction,description,cards,actions,coins,buys);
                KingdomCardMap[normalize(nom)] = KingdomCard(normalize(nom), cout, attack, reaction, description,cards,actions,coins,buys);
            }
            ligneCompteur = 0;
        } else {
            switch (ligneCompteur) {
            case 0: nom = ligne; break;
            case 1: cout = std::stoi(ligne); break;
            case 2: if(ligne=="true") attack=true; else attack=false; break;
            case 3: if(ligne=="true") reaction=true;else reaction=false;break;
            case 4:cards=std::stoi(ligne);break;
            case 5:actions=std::stoi(ligne);break;
            case 6:coins=std::stoi(ligne);break;
            case 7:buys=std::stoi(ligne);break;
            case 8: description=ligne;break;
            default: break;
            }
            ligneCompteur++;
        }
    }

    // Ajouter la dernière carte si elle n'est pas vide
    if (!nom.empty() && !description.empty()) {
        DataCards.emplace_back(normalize(nom),cout,attack,reaction,description,cards,actions,coins,buys);
        KingdomCardMap[normalize(nom)] = KingdomCard(normalize(nom), cout, attack, reaction, description,cards,actions,coins,buys);
    }
    fichier.close();
}

void KingdomCard::Braconnier(Jeux &j)
{
    Player &p=j.getActifPlayer();
    Plateau& plateau=j.getPlateau();
    std::map<std::string,Reserve>& reserve=plateau.getReserve();
    std::string message="Defausse une carte par pile de reserve vide";
    std::cout<<message<<std::endl;
    int count(0);
    std::string card;
    for(auto it:reserve)
    {
        if(it.second.getTaille()==0)
        {
            count++;
        }
    }
    if(count==0)
    {
        notif("Aucune pile de reserve n'est vide");
        return;
    }
    while(count>0)
    {
        card.clear();
        std::cout<<"Carte "<<count<<" ";
        GameCommand::getInput(j,NONE,nullptr,&card);
        if(!card.empty())
        {
            if(p.defausseFromHand(card))
            {
                count--;
            }
        }
    }

}

void KingdomCard::Atelier(Jeux &j)
{
    Plateau& p=j.getPlateau();
    Player& player=j.getActifPlayer();
    std::string nom;
    std::string message="Gagnez une carte coutant jusqu'a 4 pieces";
    std::cout<<message<<std::endl;
    std::string card;
    bool valid(false);
    while(card.empty() || !valid)
    {
        card.clear();
        GameCommand::getInput(j,NONE,nullptr,&card);
        if(!card.empty())
        {
            if(player.gainCard(card,p,0,4))
            {
                valid=true;
            }

        }
    }

}

void KingdomCard::Chapelle(Jeux & j)
{
    Player &p=j.getActifPlayer();
    std::string message="Trashez jusqu'a 4 cartes de votre main";
    std::cout<<message<<std::endl;
    int count(1);
    bool exit(false);
    std::string card;
    while (count<=4){
        card.clear();
        std::cout<<"Carte "<<count<<" ";
        GameCommand::getInput(j,NONE,&exit,&card);
        std::cout<<std::endl;
        if(!card.empty())
        {
            if(p.trashCardFromHand(card))
                count++;
        }
        if(exit || p.getHand().empty())
            break;
    }

}

void KingdomCard::Sorciere(Jeux const&j)
{
    Player &p=j.getActifPlayer();
    for(auto &joueur:j.getPlayers())
    {
        if(joueur->getName()!=p.getName())
        {
            // Réaction à l'attaque
            int index;
            if (joueur->ReactTo(index))
            {
                notif(joueur->getName()+" annule votre attaque avec la carte "+joueur->getHand().at(index)->getNom());
                continue;
            }
            joueur->gainCard("MALEDICTION",j.getPlateau());
            notif(joueur->getName()+" a gagne une MALEDICTION");

        }
    }

}

void KingdomCard::Vassal(Jeux& j) {
    Player& p = j.getActifPlayer();
    std::string message = "Défaussez la première carte de votre deck. Si c'est une carte action, vous pouvez la jouer.";
    std::cout << message << std::endl;

    Card* c = p.drawCard();
    if (!c) {
        notif("Votre deck est vide, vous ne pouvez pas defausse de carte.");
        return;
    }

    if (auto* k = dynamic_cast<KingdomCard*>(c)) {  // Vérifiez si c'est une carte action
        std::string choix;
        do {
            std::cout << "Voulez-vous jouer la carte " << c->getNom() << " ? (y/n) > ";
            GameCommand::getInput(j, NONE, nullptr, nullptr,&choix);
            if (choix == "Y") {
                k->action(j);  // Jouez l'action
                return;        // Terminez la fonction
            }
            if (choix == "N") {
                break;  // Passez au bloc pour défausser la carte
            }
            std::cout << "Entrée invalide. Veuillez répondre par 'y' ou 'n'." << std::endl;

        } while (true);
    }

    // Si ce n'est pas une carte action ou si le joueur refuse de jouer l'action
    p.getDefausse().push_back(c);
    notif("La carte " + c->getNom() + " a été défaussée.");
}


void KingdomCard::Cave(Jeux & j)
{
    Player &p=j.getActifPlayer();
    std::string message="Defaussez autant de cartes que vous voulez";
    std::cout<<message<<std::endl;
    int count(1);
    bool exit(false);
    std::string card;
    while(true){
        card.clear();
        std::cout<<"Carte "<<count<<" ";
        GameCommand::getInput(j,NONE,&exit,&card);
        if(!card.empty())
        {
            if(p.defausseFromHand(card))
            {
                count++;
            }
        }
        if(exit||p.getHand().empty())
            break;
    }
    notif("vous piochez "+std::to_string(count)+" cartes");
    p.pioche(count);
}

void KingdomCard::Jardins(Player& p)
{
    int point=static_cast<int>(p.getDeck().size())/10;
    p.AddPoint(point);
}

void KingdomCard::Messager(Jeux &j)
{
    std::cout<<"Regarde ta pile de defausse, tu peux mettre une carte dans ton deck."<<std::endl;
    Player &p=j.getActifPlayer();
    bool exit(false);
    auto*card=new std::string();
    if(p.getDefausse().empty())
    {
        notif("la defausse est vide, pas de carte a deplacer");
    }
    afficheCards(p.getDefausse());
    while(true)
    {
        card->clear();
        GameCommand::getInput(j,NONE,&exit,card);
        if(!card->empty())
        {
            if(p.moveCardFromDefausseToDeck(*card))
            {
                break;
            }
        }
        if(exit)
            break;
    }
    appuyerPourContinuer();
}
void KingdomCard::Bandit(Jeux const&j)
{
    // 1. Le joueur actif gagne une carte Or
    Player& actif = j.getActifPlayer();
    actif.gainCard("OR", j.getPlateau());
    notif("vous gagnez la carte OR");
    // 2. Pour chaque autre joueur
    for (auto& joueur : j.getPlayers())
    {
        if (joueur->getName() != actif.getName()) // Ignorer le joueur actif
        {
            // Réaction à l'attaque
            int index;
            if (joueur->ReactTo(index))
            {
                notif(joueur->getName() + " annule votre attaque avec la carte " + joueur->getHand().at(index)->getNom());
                continue;
            }
            // Révéler les deux premières cartes du deck
            std::vector<Card*> revealedCards;
            for (int i = 0; i < 2 && !joueur->getDeck().empty(); ++i)
            {
                revealedCards.push_back(joueur->drawCard());
            }
            std::endl(std::cout);
            std::string enter;
            std::cout << "REVELATION DES CARTES DE " << joueur->getName() << std::endl;
            afficheCards(revealedCards);
            // Chercher une carte Trésor non-Cuivre à trasher
            bool trashed = false;
            for (auto it = revealedCards.begin(); it != revealedCards.end(); ++it)
            {
                auto* treasureCard = dynamic_cast<TreasureCard*>(*it);
                if (treasureCard && treasureCard->getNom() != "CUIVRE")
                {
                    notif( joueur->getName() + " trash la carte " + treasureCard->getNom());
                    Player::trashCard(*it);
                    revealedCards.erase(it);
                    trashed = true;
                    break;
                }
            }

            if (!trashed)
            {
                notif( joueur->getName() + " ne trash aucune des cartes revelees");
            }

            // Défausser les cartes restantes
            joueur->defausseArray(revealedCards);
        }
    }
    
}


int KingdomCard::getActions() const
{
    return m_actions;
}
int KingdomCard::getCards()const
{
    return m_cards;
}

bool KingdomCard::isAttack() const
{
    return m_attack;
}

bool KingdomCard::isReaction() const
{
    return m_reaction;
}

int KingdomCard::getCoins() const
{
    return m_coins;
}

int KingdomCard::getBuys() const
{
    return m_buys;
}

std::string KingdomCard::getDescription() const
{
    return m_description;
}
