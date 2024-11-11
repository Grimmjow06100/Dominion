//
// Created by Asus on 07/11/2024.
//

#ifndef CARDSTREAM_H
#define CARDSTREAM_H
#include "Card.h"
#include <variant>
#include <unordered_map>
#include "KingdomCard.h"
#include "VictoryCard.h"
#include "TreasureCard.h"

using EnumCard = std::variant<Victory,Treasure>;
extern std::unordered_map<std::string,EnumCard> CardMap;

class CardStream {
private:
    Card* m_stream;
public:
    CardStream();
    ~CardStream();
    void streamCard();
    [[nodiscard]] Card* getStream() const;

};

std::string normalize(const std::string& s);
bool isFound(const std::string& s);



#endif //CARDSTREAM_H
