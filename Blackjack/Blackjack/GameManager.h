#pragma once
#include "Player.h"
#include "Deck.h"
#include <vector>

using std::vector;

class GameManager
{
private:
	//i have a lot of functions here maybe i should make a util class
	void playBlackjack(Player* player, Player* dealer, Deck* d);
	void printCard(vector<Card*>* cardPile, int i);
	void drawCard(Player* playerWhoDraws, vector<Card*>* deckToDrawFrom, int timesToDraw);
	void printHand(Player* player);
	int totalScore(Player* player);
	void displayCurrent();
	string getHitOrStand();
	string getPlayerName();
	void checkWin(int playerS, int dealerS);
	bool checkInstantWin(int playerS, int dealerS);
public:
	GameManager();
	~GameManager();
	
};

