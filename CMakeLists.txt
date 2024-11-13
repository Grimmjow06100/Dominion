cmake_minimum_required(VERSION 3.29)
project(Dominion)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dominion main.cpp
        Card.h
        TreasureCard.cpp
        TreasureCard.h
        VictoryCard.cpp
        VictoryCard.h
        KingdomCard.cpp
        KingdomCard.h
        Card.cpp
        Reserve.cpp
        Reserve.h
        Player.cpp
        Player.h
        Cardstream.cpp
        Cardstream.h
        Jeux.cpp
        Jeux.h
        Plateau.cpp
        Plateau.h
)



