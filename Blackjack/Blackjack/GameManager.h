#pragma once
#include "Player.h"
#include "Deck.h"
#include <vector>

using std::vector;

class GameManager
{
public:
	GameManager();
	~GameManager();
	void playBlackjack(Player* player, Player* dealer, Deck* d);
	void printCard(vector<Card*>* cardPile, int i);
	void drawCard(Player* playerWhoDraws, vector<Card*>* deckToDrawFrom, int timesToDraw);
	void printHand(Player* player);
	int totalScore(Player* player);
	void displayCurrent();
	string getHitOrStand();
	string getPlayerName();
};

