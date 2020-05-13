#pragma once
#include <string>
using std::string;

struct Card
{
	Card(string Face, string Suit, int cardValue);
	string Face;
	string Suit;
	int cardValue;
};

