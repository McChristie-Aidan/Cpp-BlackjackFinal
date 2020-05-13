#pragma once
#include <vector>
#include "Card.h"

class Deck
{
private:
    std::vector<Card*>* m_cards;

public:
    Deck();
    ~Deck();
    std::vector<Card*>* get_cards();
    void printCard(int i);
    void createDeck();
    void shuffle();
};
