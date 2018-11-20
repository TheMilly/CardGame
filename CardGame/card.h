#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <utility>

using namespace std;

class card 
{
	public:
		card(string cardFace, string cardSuit);
		string print() const;
		card();
		pair<int, int> getRank();
	private:
		string face;
		string suit;
};

// Constructor
card::card()
{

}

// Constructor
card::card(string cardFace, string cardSuit)
{
	face = cardFace;
	suit = cardSuit;
}

// Print Card Name Appropriately
string card::print() const
{
	if (face == "Special")
		return (face + " " + suit);
	else
		return (face + " of " + suit);
}

// Assign a rank for both the face value of the card and the suit of the card
pair<int, int> card::getRank() {
	pair<int, int> tempPair;
	tempPair = make_pair(0, 0);
	string faceValue = face;
	string suitValue = suit;

	if (faceValue == "Two")
		tempPair.first = 2;
	if (faceValue == "Three")
		tempPair.first = 3;
	if (faceValue == "Four")
		tempPair.first = 4;
	if (faceValue == "Five")
		tempPair.first = 5;
	if (faceValue == "Six")
		tempPair.first = 6;
	if (faceValue == "Seven")
		tempPair.first = 7;
	if (faceValue == "Eight")
		tempPair.first = 8;
	if (faceValue == "Nine")
		tempPair.first = 9;
	if (faceValue == "Ten")
		tempPair.first = 10;
	if (faceValue == "Jack")
		tempPair.first = 11;
	if (faceValue == "Queen")
		tempPair.first = 12;
	if (faceValue == "King")
		tempPair.first = 13;
	if (faceValue == "Ace")
		tempPair.first = 14;
	if (faceValue == "Special")
		tempPair.first = -2;

	if (suitValue == "Card")
		tempPair.second = -2;
	if (suitValue == "Spades")
		tempPair.second = 4;
	if (suitValue == "Hearts")
		tempPair.second = 3;
	if (suitValue == "Diamonds")
		tempPair.second = 2;
	if (suitValue == "Clubs")
		tempPair.second = 1;

	return tempPair;

}

#endif