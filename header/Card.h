//Card.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once

#ifndef _CARDS_H_INCLUDED_
#define _CARDS_H_INCLUDED_
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>    /
#include <ctime>        
#include <cstdlib>     


using namespace std;
class PowerPlantCard;
class Card
{
public:
	Card();
	void clearVector();
	void displayPowerPlantCards();
	
	PowerPlantCard* getSet(int i)
	{
		return &set[i];
	}
	void eraseElement(int x);
	void addElement(PowerPlantCard r);
	int sizeOfSet()
	{
		return set.size();
	}
	int cityPower()
	{

	}
	void Shuffle();
	int rngMethod(int i);
private:
	vector<PowerPlantCard> set;


};
class SummaryCard
{
public:
	SummaryCard();
	void displaySummary();
	void displayScoring();
};
class PowerPlantCard
{
public:
	PowerPlantCard();
	PowerPlantCard(int n, string rT, int rC, string rT2, int rC2, string c, int hC);

	void setToPlayer(int x);
	int belongsToPlayer()
	{
		return player;
	}
	
	int getNumber()
	{
		return number;
	}
	string getResourceType()
	{
		return resourceType;
	}
	int getResourceCost()
	{
		return resourceCost;
	}
	string getResourceType2()
	{
		return resourceType2;
	}
	int getResourceCost2()
	{
		return resourceCost2;
	}
	string getColour()
	{
		return colour;
	}
	int getHouseCost()
	{
		return houseCost;
	}
	int getCurrentResource()
	{
		return currentResource;
	}
	int getCurrentResource2()
	{
		return currentResource2;
	}
	void setCurrentResource(int sCr);
	void setCurrentResource2(int sCr2);
private:
	int player = 0;
	int number;
	string resourceType;
	int resourceCost;
	string resourceType2;
	int resourceCost2;
	string colour;
	int houseCost;
	int currentResource=0;
	int currentResource2=0;
	

};
#endif