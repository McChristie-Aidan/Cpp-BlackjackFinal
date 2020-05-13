#pragma once


#include "Card.h"
#include <vector>
#include <string>

class Player
{
public:
    Player(std::string name, std::vector<Card*>* hand);
    ~Player();
    std::string name;
    int handTotal;
    std::vector<Card*>* hand;
};

