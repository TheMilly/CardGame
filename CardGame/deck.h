#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int DECK_SIZE = 56;

class deck
{
	public:
		deck();
		card dealCard();
		void shuffle();
		void printDeck() const;

	private:
		card *deckOfCards;
		int currentCard;
};

// This function is for debugging purposes
void deck::printDeck() const
{
	for (int i = 0; i < DECK_SIZE; i++)
	{
		cout << setw(25) << deckOfCards[i].print();

		if (i % 4 == 3)
			cout << endl;
	}
}

// Constructor for deck. It will create the deck in order.
// But will eventually be shuffled for each round of the game.
deck::deck()
{
	string faces[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	
	deckOfCards = new card[DECK_SIZE];
	currentCard = 0;

	for (int counter = 0; counter < 52; counter++)
	{
		deckOfCards[counter] = card(faces[counter % 13], suits[counter / 13]);
	}

	for (int specialCounter = 52; specialCounter < DECK_SIZE; specialCounter++)
	{
		deckOfCards[specialCounter] = card("Special", "Card");
	}
}

// Using a seed for "rand()" based off of the system time on the machine.
// This will determine how the deck is shuffled every time it is called.
void deck::shuffle()
{
	cout << endl << endl;
	srand(time(NULL));
	currentCard = 0;
	for (int first = 0; first < 56; first++)
	{
		int second = (rand() % 56);
		card temp = deckOfCards[first];
		deckOfCards[first] = deckOfCards[second];
		deckOfCards[second] = temp;
	}
	// Uncomment the below line to verify the deck is shuffled 
	// And that each player is drawing the correct card
	printDeck();
}

// Shuffle once all 56 cards are used
card deck::dealCard()
{
	if (currentCard >= 56)
	{
		shuffle();
	}
	if (currentCard < 56)
	{
		return (deckOfCards[currentCard++]);
	}

	return (deckOfCards[0]);
}


#endif