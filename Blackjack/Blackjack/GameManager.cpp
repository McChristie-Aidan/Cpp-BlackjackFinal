#include "GameManager.h"
#include "Deck.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

Deck* deck;
Player* player;
Player* dealer;
string dealerName = "Dealer";
string playerName = "Player";
vector<Card*>* dealerHand;

GameManager::GameManager()
{
	Deck* deck = new Deck();
	vector<Card*>* playerHand = new vector<Card*>();
	vector<Card*>* dealerHand = new vector<Card*>();
	player = new Player(getPlayerName(), playerHand);
	dealer = new Player(dealerName, dealerHand);

	playBlackjack(player, dealer, deck);
}

//runs the blackjack game
void GameManager::playBlackjack(Player* player, Player* dealer, Deck* d)
{
	Deck* deck = d;
	vector<Card*>* cardPile = deck->get_cards();
	
	// first draw
	drawCard(player, cardPile, 2);
	drawCard(dealer, cardPile, 2);

	displayCurrent();
	
	//my win conditions are a little messy i should clean those up if i have extra time

	while (true)
	{
		int ps = totalScore(player);
		int ds = totalScore(dealer);

		if (checkInstantWin(ps, ds) == true)
		{
			break;
		}

		string input = getHitOrStand();
		//hit
		if (input == "h")
		{
			drawCard(player, cardPile, 1);
			displayCurrent();

			if (totalScore(player) > 21)
			{
				cout << "You lost!" << endl;
				break;
			}
		}
		//stand
		if (input == "s")
		{
			while (totalScore(dealer) < 17)
			{
				drawCard(dealer, cardPile, 1);
			}

			displayCurrent();

			int ps = totalScore(player);
			int ds = totalScore(dealer);

			checkWin(ps, ds);

			break;
		}
	}	
}

//displays current hands and scores
void GameManager::displayCurrent()
{
	printHand(player);
	cout << "Total Score: " << totalScore(player) << endl << endl;

	printHand(dealer);
	cout << "Total Score: " << totalScore(dealer) << endl << endl;
}

//finds score of selected player
int GameManager::totalScore(Player* player)
{
	Player* p = player;
	int total = 0;
	//used for making the ace 1 or 11
	bool aceOver21 = false;
	int numOfAces = 0;
	for (int i = 0; i < p->hand->size(); i++)
	{
		Card* c = (*p->hand)[i];
		if (c->cardValue == 11)
		{
			numOfAces += 1;
		}
		total += c->cardValue;
	}

	//implementation of the 11 or 1 ace rule
	//this was done very last minute. may or may not work
	if (total > 21 && numOfAces != 0)
	{
		while (total > 21 && numOfAces !=0)
		{
			total -= 10;
		}
	}

	return total;
}

//takes a card from a deck and puts it into a players hand
void GameManager::drawCard(Player* playerWhoDraws, vector<Card*>* deckToDrawFrom, int timesToDraw)
{
	int t = timesToDraw;
	vector<Card*>* d = deckToDrawFrom;
	Player* p = playerWhoDraws;
	for (int i = 0; i < t; i++)
	{
		Card* c = d->front();
		p->hand->push_back(c);
		d->erase(d->begin());
	}
}

//get player input to hit or stand
string GameManager::getHitOrStand()
{
	string input;
	while (true)
	{
		cout << "Do you want to hit or stand? type 'h' for hit or type 's' for stand." << endl;
		cin >> input;
		cout << endl;
		if (input == "h" || input == "H" || input == "s" || input == "S")
		{
			return input;
		}
		else
		{
			cout << "Invalid input please try again..." << endl;
		}
	}
	
}

//mainly for debug
void GameManager::printCard(vector<Card*>* cardPile, int i)
{
	Card* c = (*cardPile)[i];
	cout << c->Face << " of " << c->Suit << " : Value of " << c->cardValue << endl << endl;
}

//prints the hand of the specified player
void GameManager::printHand(Player* player)
{
	Player* p = player;
	cout << player->name << "'s hand:" << endl;
	for (size_t i = 0; i < p->hand->size(); i++)
	{
		Card* c = (*p->hand)[i];
		cout << c->Face << " of " << c->Suit << " : Value of " << c->cardValue << endl;
	}
}

//takes input to set player name
string GameManager::getPlayerName()
{
	string name;
	cout << "What is your name?" << endl << endl;
	cin >> name;
	cout << endl;

	return name;
}

void GameManager::checkWin(int playerS, int dealerS)
{
	int ps = playerS;
	int ds = dealerS;
	// I was trying to do only 3 ifs but it didn't work as intended til I split it up

	//if Tie
	if (ps == ds)
	{
		cout << "It's a tie!" << endl;
		return;
	}
	//if dealer wins
	if (ps > 21 || ds == 21)
	{
		cout << "You lost!" << endl;
		return;
	}
	//if Player wins
	if (ds > 21 || ps == 21)
	{
		cout << "You won!" << endl;
		return;
	}
	//if dealer wins
	if (ds < 21 && ds > ps)
	{
		cout << "You lost!" << endl;
		return;
	}
	//if you win
	if (ps < 21 && ps > ds)
	{
		cout << "You won!" << endl;
		return;
	}
}

bool GameManager::checkInstantWin(int playerS, int dealerS)
{
	int ps = playerS;
	int ds = dealerS;

	//instant tie
	if (ps == 21 && ps == ds)
	{
		cout << "It's a Tie!" << endl;
		return true;
	}
	//instant win
	if (ps == 21)
	{
		cout << "You Won!" << endl;
		return true;
	}
	//instant loss
	if (ds == 21)
	{
		cout << "You Lost!" << endl;
		return true;
	}

	return false;
}