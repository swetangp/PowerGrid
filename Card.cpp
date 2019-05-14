//Card.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once
#include "Card.h"
//Default constructor where all Power Plant Cards are created.
Card::Card()
{
	set.push_back(PowerPlantCard(3, "oil", 2, "null", 0, "black", 1));
	set.push_back(PowerPlantCard(4, "coal", 2, "null", 0, "brown", 1));
	set.push_back(PowerPlantCard(5, "oil", 2, "coal", 2, "black/brown", 1));
	set.push_back(PowerPlantCard(6, "garbage", 1, "null", 0, "yellow", 1));
	set.push_back(PowerPlantCard(7, "oil", 3, "null", 0, "black", 2));
	set.push_back(PowerPlantCard(8, "coal", 3, "null", 0, "brown", 21));
	set.push_back(PowerPlantCard(9, "oil", 1, "null", 0, "black", 1));
	set.push_back(PowerPlantCard(10, "coal", 2, "null", 0, "brown", 2));
	set.push_back(PowerPlantCard(11, "uranium", 2, "null", 0, "red", 2));
	set.push_back(PowerPlantCard(12, "coal", 2, "oil", 2, "black/brown", 2));
	set.push_back(PowerPlantCard(13, "none", 0, "null", 0, "green", 1));
	set.push_back(PowerPlantCard(14, "garbage", 2, "null", 0, "yellow", 2));
	set.push_back(PowerPlantCard(15, "coal", 2, "null", 0, "brown", 3));
	set.push_back(PowerPlantCard(16, "oil", 2, "null", 0, "black", 3));
	set.push_back(PowerPlantCard(17, "uranium", 1, "null", 0, "red", 2));
	set.push_back(PowerPlantCard(18, "none", 0, "null", 0, "green", 2));
	set.push_back(PowerPlantCard(19, "garbage", 2, "null", 0, "yellow", 3));
	set.push_back(PowerPlantCard(20, "coal", 3, "null", 0, "black", 5));
	set.push_back(PowerPlantCard(21, "oil", 2, "coal", 2, "black/brown", 4));
	set.push_back(PowerPlantCard(22, "none", 0, "null", 0, "green", 2));
	set.push_back(PowerPlantCard(23, "uranium", 1, "null", 0, "red", 3));
	set.push_back(PowerPlantCard(24, "garbage", 2, "null", 0, "yellow", 4));
	set.push_back(PowerPlantCard(25, "coal", 2, "null", 0, "brown", 5));
	set.push_back(PowerPlantCard(26, "oil", 2, "null", 0, "black", 5));
	set.push_back(PowerPlantCard(27, "none", 0, "null", 0, "green", 3));
	set.push_back(PowerPlantCard(28, "uranium", 1, "null", 0, "red", 4));
	set.push_back(PowerPlantCard(29, "coal", 1, "oil", 1, "black/brown", 4));
	set.push_back(PowerPlantCard(30, "garbage", 3, "null", 0, "yellow", 6));
	set.push_back(PowerPlantCard(31, "coal", 3, "null", 0, "brown", 6));
	set.push_back(PowerPlantCard(32, "oil", 3, "null", 0, "black", 6));
	set.push_back(PowerPlantCard(33, "none", 0, "null", 0, "green", 4));
	set.push_back(PowerPlantCard(34, "uranium", 1, "null", 0, "red", 5));
	set.push_back(PowerPlantCard(35, "oil", 1, "null", 0, "black", 5));
	set.push_back(PowerPlantCard(36, "coal", 3, "null", 0, "brown", 7));
	set.push_back(PowerPlantCard(37, "none", 0, "null", 0, "green", 4));
	set.push_back(PowerPlantCard(38, "garbage", 3, "null", 0, "yellow", 7));
	set.push_back(PowerPlantCard(39, "uranium", 1, "null", 0, "red", 6));
	set.push_back(PowerPlantCard(40, "oil", 2, "null", 0, "black", 6));
	set.push_back(PowerPlantCard(42, "coal", 2, "null", 0, "brown", 6));
	set.push_back(PowerPlantCard(44, "none", 0, "null", 0, "green", 5));
	set.push_back(PowerPlantCard(46, "coal", 3, "oil", 3, "brown", 7));
	set.push_back(PowerPlantCard(50, "stage3", 0, "null", 0, "blue", 6));
}
void Card::clearVector()
{
	set.clear();
}
//Displays information regarding to the power plant
void Card::displayPowerPlantCards()
{
	for (int i = 0; i < set.size(); i++)
	{
		cout << "Card: " << set[i].getNumber() << endl;
		cout << "Resource type and cost: " << set[i].getResourceType() << ", " << set[i].getResourceCost() << endl;
		/*if (set[i].getResourceType2 != "null")
		{
			cout << "Resource type 2 and cost: " << set[i].getResourceType2() << ", " << set[i].getResourceCost2() << endl;
		}*/
		cout << "Houses: " << set[i].getHouseCost() << endl;
	}
}
//Random number generator
int Card::rngMethod(int i)
{
	return std::rand() % i;
}
//Shuffle method to shuffle vectors
void Card::Shuffle()
{
	srand(unsigned(std::time(0)));
	std::random_shuffle(set.begin(), set.end());
}
//Removing cards from the vector
void Card::eraseElement(int x)
{
	for (int i = 0; i < set.size(); i++)
	{
		if (set[i].getNumber() == x)
		{
			set.erase(set.begin() + i);
		}
	}
}
//Adding cards to the vector
void Card::addElement(PowerPlantCard r)
{
	set.push_back(r);
}
//Setting a card to a player
void PowerPlantCard::setToPlayer(int x)
{
	player = x;
}
SummaryCard::SummaryCard()
{

}
//Displays the summary card steps
void SummaryCard::displaySummary()
{
	cout << "1. Determine Turn Order\n" << endl;
	cout << "2. Buy Power Plant\nThe first player begins.\nPer round, each may buy only one power plant\n" << endl;
	cout << "3. Buy Raw Materials\nThe last player begins.\nMaximum double input per power plant.\n" << endl;
	cout << "4. Building\nThe last player begins.\n" << endl;
	cout << "5. Bureaucracy\n-Get money.\n-In phase 1 and 2: Place highest power plant under the stack.\nIn phase 3: Remove lowest power plant from the game.\nRestock raw materials\n" << endl;
}
//Displays the scoring system
void SummaryCard::displayScoring()
{
	int houseScore[20];
	for (int i = 0; i <= 21; i++)
	{
		houseScore[i] = i;
	}
	int electroScore[21] = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150 };
}

//Default constructor
PowerPlantCard::PowerPlantCard()
{

}
//Constructor
PowerPlantCard::PowerPlantCard(int n, string rT, int rC, string rT2, int rC2, string c, int hC)
{
	number = n;
	resourceType = rT;
	resourceCost = rC;
	resourceType2 = rT2;
	resourceCost2 = rC2;
	colour = c;
	houseCost = hC;
}
//Sets the players current resource on that card
void PowerPlantCard::setCurrentResource(int sCr)
{
	currentResource = sCr;
}
//If the cards has dual properties it will set the players second resource on that card
void PowerPlantCard::setCurrentResource2(int sCr2)
{
	currentResource2 = sCr2;
}

