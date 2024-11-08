//
// Created by Asus on 07/11/2024.
//

#ifndef CARDSTREAM_H
#define CARDSTREAM_H
#include <vector>
#include "Card.h"



class CardStream {
private:
    std::vector<Card*> m_stream;
    void clean();
public:
    CardStream();
    ~CardStream();
    void stream();
    [[nodiscard]] std::vector<Card*> getStream() const;

};



#endif //CARDSTREAM_H
