#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class Card
{
private:
	// attributes
	char suit;
	char face;
	short value;
	static bool randomizerSeeded;   // class-wide variable

public:
	// constructors
	Card();

	// behaviors
	string toString();
	bool flipAceToOne();

	// accessors 
	char getSuit() { return suit; }
	char getFace() { return face; }
	short getValue() { return value; }
};

