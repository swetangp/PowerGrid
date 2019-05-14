//Player.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once

#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Attributes.h"
#include "Card.h"
#include "Subject.h"
#include "Strategy.h"
using namespace std;

class Player : public Subject
{
public:
	Player();
	Player(int tO);
	Player(Strategy* str);
	void setStrategy(Strategy* newStrat);
	int passingStrategy();
	int auctionStrategy();
	void displayMyHouses();
	void displayMyResources();
	void displayMyMoney();
	void setPlayerTurn(int t);
	void setCurrentTurn(int t);
	void pass();
	int getMyHouses()
	{
		return myHouses.getNumber();
	}
	Houses toSetHouse()
	{
		return myHouses;
	}
	int getTurnOrder()
	{
		return turnOrder;
	}
	int getCurrentTurn()
	{
		return currentTurn;
	}
	string getStartRegion()
	{
		return startRegion;
	}
	int getMyMoney()
	{
		return elektro;
	}
	int getPassVal()
	{
		return passVal;
	}
	int getCardTotal()
	{
		return myCards.sizeOfSet();
	}
	void getMyTurn();
	void removeResources(int y);
	void setResourcesOnCard(int x);
	void displayMyCards();
	void addCard(PowerPlantCard r);
	void clearCard();
	void setMyHouses(int mH);
	void getMyResources();
	void setResourceZero();
	void setMyMoney(int m);
	void setStartRegion(string sSR);
	void setPassVal(int pv);
	void displayCardResources();
	int getCardNum(int d);
	int getStep();

	//Finds out how much electricity a player can generate with their powerplant cards and resources
	int determineHousePower()
	{
		int cost = 0;
		for (int i = 0; i < myCards.sizeOfSet(); i++)
		{
			if (myCards.getSet(i)->getCurrentResource() >= myCards.getSet(i)->getResourceCost())
			{
				if (myCards.getSet(i)->getCurrentResource() == myCards.getSet(i)->getResourceCost() * 2)
				{
					cost= cost + myCards.getSet(i)->getHouseCost() * 2;
				}
				else
				{
					cost = cost + myCards.getSet(i)->getHouseCost();
				}
			}
		}
		return cost;
	}
private:
	int step = 1;
	int passVal = 1;
	int elektro = 50;
	int currentTurn = 0;
	string startRegion;
	int turnOrder=0;
	Houses myHouses;
	Resources myResources;
	Card myCards;
	Strategy* strategy;
};
#endif