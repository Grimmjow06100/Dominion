//
// Created by Asus on 07/11/2024.
//

#ifndef CARDSTREAM_H
#define CARDSTREAM_H
#include "Card.h"
#include <vector>





class CardStream {

public:
     Card* streamCard();
     std::vector<Card*> streamCardArray();


};




#endif //CARDSTREAM_H
