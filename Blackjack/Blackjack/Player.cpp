#include "Player.h"

Player::Player(std::string name, std::vector<Card*>* hand)
{
    this->name = name;
    this->hand = hand;
    handTotal = 0;
}

Player::~Player()
{
    delete this->hand;
}