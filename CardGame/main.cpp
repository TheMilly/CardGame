#include "deck.h"
#include <vector>
#include <map>

using namespace std;

int main()
{
	string input = "";
	cout << "Would you like to play a card game? [Y/N]: ";
	cin >> input;
	
	while ((input != "Y") && (input != "y") && (input != "N") && (input != "n"))
	{
		cout << "\n \nPlease enter 'Y' or 'y' to play the game, OR 'N' or 'n' to exit: ";
		cin >> input;
	}
	cout << endl;

	if (input == "n" || input == "N")
		exit(0);

	cout << "Input the number of players please (2 - 4): ";
	int numOfPlayers;
	cin >> numOfPlayers;

	cout << endl;

	while ((numOfPlayers > 4) || (numOfPlayers < 2))
	{
		if (cin.fail())
		{
			// Clear error state
			cin.clear();

			// Discard 'bad' characters
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		cout << "\n \nInvalid entry! Please input a value between 2 and 4: ";
		cin >> numOfPlayers;
		
	}

	// Second value will be the score which will be how the pairs are sorted by within the vector
	// The key/first value will be the player's ID
	map<int, int> scoreBoard;

	// Initialize scoreboard so all players start with score '0'
	for (int i = 0; i < numOfPlayers; i++)
		scoreBoard[i] = 0;

	// Boolean to identify when the game is over.
	bool winner = false;

	// Used to announce the winner of the whole game
	int winnerIndex = -1;

	// Used to announce the round number at the beginning of every round
	int round = 1;

	// Initialize the deck of 56 cards
	deck deckOfCards;
	
	// Original shuffle
	deckOfCards.shuffle();
	while (!winner)
	{	
		// Shuffle cards at beginning of every round
		//deckOfCards.shuffle();

		cout << "---------------------------------------------------------------------------------------------------" << endl;
		cout << "ROUND " + to_string(round) << endl << endl;
		
		// Vector will hold each player's card for the round
		vector<card> currentCards(numOfPlayers);

		// This loop will handle the drawing of the cards. It will also internally check if a "Special Card" is drawn
		// If "Special Card" is drawn, it will penalize the player who drew the card
		for (int i = 0; i < numOfPlayers; i++)
		{
			cout << "Player " + to_string(i + 1) + " please press any key to draw a card." << endl;
			system("PAUSE");
			cout << endl;
			currentCards[i] = deckOfCards.dealCard();
			cout << "********************************************" << endl;
			cout << "Player " + to_string(i+1) + "'s card is a [" << currentCards[i].print() + "]" << endl;
			cout << "********************************************" << endl << endl;

			// Checking for "Special Card", if it is a "Special Card" it will check to make sure
			// The player's score won't go below 0
			if (currentCards[i].getRank().first == -2)
			{
				if ((scoreBoard[i] != 0))
					scoreBoard[i] -= 1;
			}
		}

		// 'vari' is the index of the current largest element
		// In case of vari never being updated and staying at '0', 'roundWinner' will be updated when
		// A player has a higher score than another player, this is to prevent an edge case of all 
		// Players having a Special Card, and therefore vari would never be updated.
		// This was to avoid using a nested for loop. Therefore O(n) time complexity.
		int vari = 0;

		// Identify the winner for each round, if still '-1' at the end of round, 
		// Then no one won that round ex: (If all players draw Special Card)
		int roundWinner = -1;

		// This loop will determine the winner of each round
		for (int k = 1; k < numOfPlayers; k++)
		{
			pair<int, int> pairOne;
			pair<int, int> pairTwo;
			card Card1 = currentCards[k];
			card Card2 = currentCards[vari];

			pairOne = Card1.getRank();
			pairTwo = Card2.getRank();

			if (pairOne.first == pairTwo.first)
			{
				if (pairOne.second > pairTwo.second)
				{
					roundWinner = k;
					vari = k;
				}
				else if(pairOne.second < pairTwo.second)
				{
					roundWinner = vari;
				}
			} 
			else if (pairOne.first > pairTwo.first)
			{
				roundWinner = k;
				vari = k;
			}
			else if (pairOne.first < pairTwo.first)
			{
				roundWinner = vari;
			}
		}

		// If all players in game receive a Special Card, no one gains points that round
		// Otherwise, the winner of the round will be awarded their points
		// As well as announce the Player number that won that round.
		if (roundWinner != -1)
		{
			scoreBoard[roundWinner] += 2;
			cout << "*******************************" << endl;
			cout << "Player " + to_string(roundWinner + 1) + " Wins This Round!" << endl;
			cout << "*******************************" << endl << endl;
		}
		else
		{
			cout << "*******************************" << endl;
			cout << "No one Won This Round!" << endl;
			cout << "*******************************" << endl << endl;
		}

		// Displaying the scoreboard of the running sums of player's points for each round.
		cout << "The Current Scores Are:" << endl << "-------------------------" << endl;

		for (int x = 0; x < numOfPlayers; x++)
		{
			cout << "Player " + to_string(x + 1) + "  |  " + to_string(scoreBoard[x]) << endl;
		}

		cout << endl;

		// This nested loop will verify if someone has over 21 points,
		// If they have over 21 points, it will verify that they won by 2 points
		for (int y = 0; y < numOfPlayers; y++)
		{
			if (scoreBoard[y] >= 21)
			{
				winner = true;
				winnerIndex = y;
				for (int z = 0; z < numOfPlayers; z++)
				{
					if ((y != z) && (scoreBoard[y] - scoreBoard[z]) < 2)
					{
						winner = false;
					}
				}
			}
		}
		round++;
	}

	cout << endl << endl << "*******************************" << endl;
	cout << "The Champion Is: Player " + to_string(winnerIndex + 1) << endl;
	cout << "*******************************" << endl << endl;

	system("pause");

	return 0;
}