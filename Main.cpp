#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "Card.h"

using namespace std;

// prototypes
string showCards(vector<Card> cards);
short sumCardValues(vector<Card> cards);
void playHand(short& cash);  // & means "address of"

int main()
{
	cout << (char)3 << endl;
	cout << (char)4 << endl;
	cout << (char)5 << endl;
	cout << (char)6 << endl;


	short cash = 100;
	cout << "Welcome to BlackJack Extreme!" << endl;
	cout << "\nYour starting cash position: $" << cash << endl;

	//pause 
	cout << endl;
	system("pause");

	// initialize application loop variable and then start the loop
	short choice = 0;

	do
	{
		// display menu
		system("cls");  // clears the screen
		cout << "Menu\n" << endl;
		cout << "1) Play a hand" << endl;
		cout << "2) Show current cash balance" << endl;
		cout << "3) Exit" << endl;

		// get user's choice
		cout << "\nEnter your choice: ";
		cin >> choice;

		// run code based on user's choice
		switch (choice)
		{
		case 1:
			playHand(cash);
			if (cash == 0)
			{
				cout << "\nYou are broke!" << endl;
				cout << "Come back when you have more cash!" << endl;
				break;
			}
			break;
		case 2:
			cout << "\nHere is your current cash position: $" << cash << endl;
			break;
		case 3:
			cout << "\nGoodbye!" << endl;
			break;
		default:
			cout << "\nError. Please select from the menu." << endl;
		}

		//pause
		cout << endl;
		system("pause");
	} 	while (choice != 3);

	// show the final cash position
	cout << "\nHere is your final cash position: $" << cash << endl;
	cout << "Come back when you are ready to play again!" << endl;

	return 0;
}

string showCards(vector<Card> cards)
{
	string output = "";
	for (Card c : cards)
	{
		output += c.toString() + " ";
	}
	return output;
}

short sumCardValues(vector<Card> cards)
{
	short total = 0;
	for (Card c : cards)
	{
		total += c.getValue();
	}
	return total;
}

void playHand(short& cash)
{
	vector<Card> dealerCards;
	vector<Card> playerCards;
	short playerTotal;
	short dealerTotal;
	short bet;

	// get the user's bet amount
	do
	{
		cout << "\nHow much do you want to bet on this hand? ";
		cin >> bet;

		if (bet > cash)
		{
			cout << "\nError. You do not have that much cash. " << endl;
			cout << "Here is your cash position: $" << cash << endl;
		}
	} 	while (bet > cash);

	Card c1;
	Card c2;
	dealerCards.push_back(c1);
	dealerCards.push_back(c2);

	dealerTotal = sumCardValues(dealerCards);
	cout << "\nDealer's first card: " << dealerCards[0].toString() << endl;

	playerCards.push_back(Card());
	playerCards.push_back(Card());
	playerTotal = sumCardValues(playerCards);

	cout << "\nPlayer Cards: " << showCards(playerCards) << endl;

	// deal more cards to the player, if desired
	char answer = '?';

	do
	{
		cout << "\nHit or Stand (H of S): ";
		cin >> answer;  // Hit ENTER
		cin.ignore(100, '\n');

		if (answer == 'h' || answer == 'H')
		{
			Card c;
			cout << "\nHere is your card: " << c.toString() << endl;
			playerCards.push_back(c);
			playerTotal = sumCardValues(playerCards);
			if (playerTotal > 21)
			{
				for (Card card : playerCards)
				{
					if (card.getValue() == 11)
					{
						card.flipAceToOne();
						cout << "\nYour total was greater than 21" << endl;
						cout << "Ace value was flipped to one." << endl;
						break;
					}
				}

			}
			cout << "\nHere are your cards: " << showCards(playerCards) << endl;
			playerTotal = sumCardValues(playerCards);
			cout << "Your total is " << playerTotal << endl;

			if (playerTotal > 21)
			{
				answer = 'S';
			}
		}
	} 	while (answer != 's' && answer != 'S');

	// deal cards to the dealer, if appropriate
	if (playerTotal > 21)
	{
		cout << "\nPlayer, you busted with a " << playerTotal << endl;
	}
	else
	{
		while (dealerTotal < 17)
		{
			Card c;
			cout << "\nDealer pulled: " << c.toString() << endl;
			dealerCards.push_back(c);
			dealerTotal = sumCardValues(dealerCards);
			cout << "Dealer cards: " << showCards(dealerCards) << endl;
		}

		if (dealerTotal > 21)
		{
			cout << "\nDealer busted with: " << dealerTotal << endl;
			cash += bet;
		}
		else if (dealerTotal > playerTotal)
		{
			cout << "\nDealer wins. " << endl;
			cout << "\tDealer: " << dealerTotal << endl;
			cout << "\tPlayer: " << playerTotal << endl;
			cash -= bet;
		}
		else if (playerTotal > dealerTotal)
		{
			cout << "\nPlayer wins!" << endl;
			cout << "\tDealer: " << dealerTotal << endl;
			cout << "\tPlayer: " << playerTotal << endl;
			cash += bet;
		}
		else
		{
			cout << "\nPlayer pushes the dealer. " << endl;
			cout << "\tDealer: " << dealerTotal << endl;
			cout << "\tPlayer: " << playerTotal << endl;
		}
	}
}
