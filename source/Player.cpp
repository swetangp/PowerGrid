//Player.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "Player.h"
Player::Player()
{
	turnOrder = 0;
}
//Represents the turn in which player will move
Player::Player(int tO)
{
	turnOrder = tO;
}
Player::Player(Strategy * str)
{
	this->strategy = str;
}
void Player::setStrategy(Strategy * newStrat)
{
	this->strategy = newStrat;
}
int Player::passingStrategy()
{
	return this->strategy->pass();
}
int Player::auctionStrategy()
{
	return this->strategy->auction();
}
//Displays players number of remaining houses
void Player::displayMyHouses()
{
	cout <<"Houses: "<< myHouses.getNumber() << endl;
}
//Displays players resources
void Player::displayMyResources()
{
	cout << "Coal: " << myResources.getCoal() << endl;
	cout << "Garbage: " << myResources.getGarbage() << endl;
	cout << "Oil: " << myResources.getOil() << endl;
	cout << "Uranium: " << myResources.getUranium() << endl;
}
//Displays players elektro
void Player::displayMyMoney()
{
	cout << "Elektro: " << getMyMoney() << endl;
}
//Sets the player number
void Player::setPlayerTurn(int t)
{
	turnOrder = t;
}
//Sets the players colour region in which they start in
void Player::setStartRegion(string sSR)
{
	startRegion = sSR;
}
//Sets the players turn in game (1st, 2nd, ...)
void Player::setCurrentTurn(int t)
{
	currentTurn = t;
}
//Player can pass during the bidding phase and registers them with a value 0 thus making them in the same pool as those cannot bid anymore.
void Player::pass()
{
	passVal = 0;
}
//When buying or selling resources, elektro or money must be altered
void Player::setMyMoney(int m)
{
	elektro = m;
}
//Owning new cities requires a placement of the players house
void Player::setMyHouses(int mH)
{
	myHouses.setNum(mH);
}
void Player::getMyResources()
{
	int x = 0, y = 0, z = 0, w = 0;
	for (int i = 0; i < myCards.sizeOfSet(); i++)
	{
		if (myCards.getSet(i)->getResourceType() == "oil")
		{
			x = x + myCards.getSet(i)->getCurrentResource();
		}
		else if (myCards.getSet(i)->getResourceType() == "garbage")
		{
			y = y + myCards.getSet(i)->getCurrentResource();
		}
		else if (myCards.getSet(i)->getResourceType() == "coal")
		{
			z = z + myCards.getSet(i)->getCurrentResource();
		}
		else if (myCards.getSet(i)->getResourceType() == "uranium")
		{
			w = w + myCards.getSet(i)->getCurrentResource();
		}
		if (myCards.getSet(i)->getResourceType2() == "oil")
		{
			x = x + myCards.getSet(i)->getCurrentResource2();
		}
		else if (myCards.getSet(i)->getResourceType2() == "garbage")
		{
			y = y + myCards.getSet(i)->getCurrentResource2();
		}
		else if (myCards.getSet(i)->getResourceType2() == "coal")
		{
			z = z + myCards.getSet(i)->getCurrentResource2();
		}
		else if (myCards.getSet(i)->getResourceType2() == "uranium")
		{
			w = w + myCards.getSet(i)->getCurrentResource2();
		}
	}
	cout << "Oil: " << x << endl;
	cout << "Garbage: " << y << endl;
	cout << "Coal: " << z << endl;
	cout << "Uranium: " << w << endl;
}
void Player::setResourceZero()
{
	myResources.setCoal(0);
	myResources.setGarbage(0);
	myResources.setOil(0);
	myResources.setUranium(0);
}
//The pass value must be reset after the bidding phase is over
void Player::setPassVal(int pv)
{
	passVal = pv;
}
void Player::displayCardResources()
{

}
//Outputs the players powerplant cards that they own
void Player::displayMyCards()
{
	myCards.displayPowerPlantCards();
}
//Adding a card from the present deck to ones own deck
void Player::addCard(PowerPlantCard r)
{
	myCards.addElement(r);
}
//Destroys all cards that the player owns
void Player::clearCard()
{
	myCards.clearVector();
}
void Player::getMyTurn()
{
	//Notify();
}
//Removing resources from powerplant cards.
void Player::removeResources(int y)
{
	//Integer y represents the cities in which the player has chosen to power and is set to counter to keep track.
	//Once counter reaches 1 or below the player has satisfied the condition in which how many cities they want to power and can exit the loop
	int userChoice;
	int counter = y;

	//The players cards will be displayed
	cout << "Here are your cards." << endl;
	myCards.displayPowerPlantCards();

	int removalLoop = 0;
	while (removalLoop == 0)
	{
		//Until the user removes the right amount of resources the counter will not go down preventing them from escaping the loop
		cout << "You need to remove resources for " << counter << " cities." << endl;

		//Cycling through the players powerplant cards to remove resources.
		for (int i = 0; i < myCards.sizeOfSet(); i++)
		{
			//If the user has a resourceless card
			if (myCards.getSet(i)->getResourceType() == "none")
			{
				counter--;
			}

			//Compares the resource cost of the card to the players placed resources
			else if ((myCards.getSet(i)->getCurrentResource() >= myCards.getSet(i)->getResourceCost()) && counter >0)
			{
				//If the player has 2 times the amount of the max resource on the card, they can power up double the cities.
				//A decision tree in case they want to continue
				if (myCards.getSet(i)->getCurrentResource() == myCards.getSet(i)->getResourceCost() * 2)
				{
					cout << "Card: " << myCards.getSet(i)->getNumber() << " of resource type " << myCards.getSet(i)->getResourceType() << ", quantity of " << myCards.getSet(i)->getCurrentResource() << endl;
					cout << "Would you like to remove this resource to power up" << myCards.getSet(i)->getHouseCost()*2 << " cities?" << endl;
					cout << "1. Yes" << endl;
					cout << "2. No" << endl;
					cin >> userChoice;
					if (userChoice == 1)
					{
						myCards.getSet(i)->setCurrentResource(0);
						counter = counter - myCards.getSet(i)->getHouseCost() * 2;
					}
					else
					{

					}
				}
				//If the player only has the current resource value greater then the resource cost
				else
				{
					cout << "Card: " << myCards.getSet(i)->getNumber() << " of resource type " << myCards.getSet(i)->getResourceType() << ", quantity of " << myCards.getSet(i)->getCurrentResource() << endl;
					cout << "Would you like to remove this resource to power up" << myCards.getSet(i)->getHouseCost() << " cities?" << endl;
					cout << "1. Yes" << endl;
					cout << "2. No" << endl;
					cin >> userChoice;
					if (userChoice == 1)
					{
						myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() - myCards.getSet(i)->getResourceCost());
						counter = counter - myCards.getSet(i)->getHouseCost();
					}
					else
					{

					}
				}
			}
			//If the card has a secondary resource and the player wishes to expend that value instead.
			else if ((myCards.getSet(i)->getCurrentResource2() >= myCards.getSet(i)->getResourceCost2()) && counter > 0)
			{
				//If the secondary resource is 2 times of the resource cost, it can double the power to the cities
				//A decision tree if the user wishes to expend those resources
				if (myCards.getSet(i)->getCurrentResource2() == myCards.getSet(i)->getResourceCost2() * 2)
				{
					cout << "Card: " << myCards.getSet(i)->getNumber() << " of resource type " << myCards.getSet(i)->getResourceType2() << ", quantity of " << myCards.getSet(i)->getCurrentResource2() << endl;
					cout << "Would you like to remove this resource to power up" << myCards.getSet(i)->getHouseCost() * 2 << " cities?" << endl;
					cout << "1. Yes" << endl;
					cout << "2. No" << endl;
					cin >> userChoice;
					if (userChoice == 1)
					{
						myCards.getSet(i)->setCurrentResource2(0);
						counter = counter - myCards.getSet(i)->getHouseCost() * 2;
					}
					else
					{

					}
				}
				//If the player only has the current resource value greater then the resource cost
				else
				{
					cout << "Card: " << myCards.getSet(i)->getNumber() << " of resource type " << myCards.getSet(i)->getResourceType2() << ", quantity of " << myCards.getSet(i)->getCurrentResource2() << endl;
					cout << "Would you like to remove this resource to power up" << myCards.getSet(i)->getHouseCost() << " cities?" << endl;
					cout << "1. Yes" << endl;
					cout << "2. No" << endl;
					cin >> userChoice;
					if (userChoice == 1)
					{
						myCards.getSet(i)->setCurrentResource2(myCards.getSet(i)->getCurrentResource2() - myCards.getSet(i)->getResourceCost2());
						counter = counter - myCards.getSet(i)->getHouseCost();
					}
					else
					{

					}
				}
			}
		}
		//Once the counter is 0 or below, the player will have satisfied the condition and can exit the loop
		if (counter <= 0)
		{
			removalLoop = 1;
		}
		else
		{

		}
	}
}
//Returns the card number value, not its vector position!
int Player::getCardNum(int d)
{
	for (int i = 0; i < myCards.sizeOfSet(); i++)
	{
		if (myCards.getSet(i)->getNumber() == d)
		{
			return d;
		}
	}
	return -1;
}
int Player::getStep()
{
	if (step == 1)
	{
		return 1;
	}
	else if (step == 2)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}
//Putting resources on a powerplant card.
void Player::setResourcesOnCard(int x)
{
	for (int i = 0; i < myCards.sizeOfSet(); i++)
	{
		if (myCards.getSet(i)->getNumber() == x)
		{
			//ONLY FOR CARDS WITH DUAL RESOURCE TYPES
			if (myCards.getSet(i)->getResourceType2() != "null")
			{
				//A decision tree in which the powerplant card has two resources.
				cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost() << " " << myCards.getSet(i)->getResourceType() << "OR, " << myCards.getSet(i)->getResourceCost2()<<" "<<myCards.getSet(i)->getResourceType2()<< endl;
				cout << "Which resources would you like to use?" << endl;
				cout << "1. " << myCards.getSet(i)->getResourceType() << endl;
				cout << "2. " << myCards.getSet(i)->getResourceType2() << endl;
				cout << "3. Both" << endl;

				int resourceChoice;
				cin >> resourceChoice;

				//FOR RESOURCE TYPE 1
				if (resourceChoice == 1)
				{
					cout << "The cost of this power plant resource is " << myCards.getSet(i)->getResourceCost() << " and " << myCards.getSet(i)->getResourceType() << endl;
					cout << "How many resources would you like to put? A maximum of " << myCards.getSet(i)->getResourceCost() * 2 << " can be put." << endl;

					int costChoice;
					

					int costLoop=0;
					while (costLoop == 0)
					{
						cin >> costChoice;
						if (costChoice< 0 || costChoice >myCards.getSet(i)->getResourceCost() * 2)
						{
							cout << "Invalid range. Try again." << endl;
						}
						//Determines what type of resource the card is associated to.
						else
						{
							if (myCards.getSet(i)->getResourceType() == "coal")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost() << "and" << myCards.getSet(i)->getResourceType() << endl;
								if (myResources.getCoal() >= myCards.getSet(i)->getResourceCost())
								{
									myResources.setCoal(myResources.getCoal() - costChoice);
									myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() + costChoice);
								}
								else
								{
									cout << "You do not have enough coal" << endl;
								}
							}
							else if (myCards.getSet(i)->getResourceType() == "oil")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost() << "and" << myCards.getSet(i)->getResourceType() << endl;
								if (myResources.getOil() >= myCards.getSet(i)->getResourceCost())
								{
									myResources.setOil(myResources.getOil() - costChoice);
									myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource()+costChoice);
								}
								else
								{
									cout << "You do not have enough oil" << endl;
								}
							}
							else if (myCards.getSet(i)->getResourceType() == "garbage")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost() << "and" << myCards.getSet(i)->getResourceType() << endl;
								if (myResources.getGarbage() >= myCards.getSet(i)->getResourceCost())
								{
									myResources.setGarbage(myResources.getGarbage() - costChoice);
									myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() + costChoice);
								}
								else
								{
									cout << "You do not have enough garbage" << endl;
								}
							}
							else if (myCards.getSet(i)->getResourceType() == "uranium")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost() << "and" << myCards.getSet(i)->getResourceType() << endl;
								if (myResources.getUranium() >= myCards.getSet(i)->getResourceCost())
								{
									myResources.setUranium(myResources.getUranium() - costChoice);
									myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() + costChoice);
								}
								else
								{
									cout << "You do not have enough uranium" << endl;
								}
							}
							else
							{

							}
							costLoop = 1;
						}
					}
				}
				//FOR RESOURCE TYPE 2
				else if (resourceChoice == 2)
				{
					cout << "The cost of this power plant resource is " << myCards.getSet(i)->getResourceCost2() << " and "<<myCards.getSet(i)->getResourceType2() <<endl;
					cout << "How many resources would you like to put? A maximum of " << myCards.getSet(i)->getResourceCost2() * 2 << " can be put." << endl;

					int costChoice;
					cin >> costChoice;

					int costLoop = 0;
					while (costLoop == 0)
					{
						if (costChoice< 0 || costChoice >myCards.getSet(i)->getResourceCost2() * 2)
						{
							cout << "Invalid range. Try again." << endl;
						}
						//Determines what type of resource the card is associated to.
						else
						{
							if (myCards.getSet(i)->getResourceType2() == "coal")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost2() << "and" << myCards.getSet(i)->getResourceType2() << endl;
								if (myResources.getCoal() >= myCards.getSet(i)->getResourceCost2())
								{
									myResources.setCoal(myResources.getCoal() - costChoice);
									myCards.getSet(i)->setCurrentResource2(myCards.getSet(i)->getCurrentResource2() + costChoice);
								}
								else
								{
									cout << "You do not have enough coal" << endl;
								}
							}
							else if (myCards.getSet(i)->getResourceType2() == "oil")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost2() << "and" << myCards.getSet(i)->getResourceType2() << endl;
								if (myResources.getOil() >= myCards.getSet(i)->getResourceCost2())
								{
									myResources.setOil(myResources.getOil() - costChoice);
									myCards.getSet(i)->setCurrentResource2(myCards.getSet(i)->getCurrentResource2() + costChoice);
								}
								else
								{
									cout << "You do not have enough oil" << endl;
								}
							}
							else if (myCards.getSet(i)->getResourceType2() == "garbage")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost2() << "and" << myCards.getSet(i)->getResourceType2() << endl;
								if (myResources.getGarbage() >= myCards.getSet(i)->getResourceCost2())
								{
									myResources.setGarbage(myResources.getGarbage() - costChoice);
									myCards.getSet(i)->setCurrentResource2(myCards.getSet(i)->getCurrentResource2() + costChoice);
								}
								else
								{
									cout << "You do not have enough garbage" << endl;
								}
							}
							else if (myCards.getSet(i)->getResourceType2() == "uranium")
							{
								cout << "Card" << myCards.getSet(i)->getNumber() << "requires, " << myCards.getSet(i)->getResourceCost2() << "and" << myCards.getSet(i)->getResourceType2() << endl;
								if (myResources.getUranium() >= myCards.getSet(i)->getResourceCost2())
								{
									myResources.setUranium(myResources.getUranium() - costChoice);
									myCards.getSet(i)->setCurrentResource2(myCards.getSet(i)->getCurrentResource2() + costChoice);
								}
								else
								{
									cout << "You do not have enough uranium" << endl;
								}
							}
							else
							{

							}
							costLoop = 1;
						}
					}
				}
				else if (resourceChoice == 3)
				{
					
				}
				
			}
			
			//If the powerplant card only has one resource type
			//Conditional statements below determining what resource type it is for the player to set the right resource
			else if (myCards.getSet(i)->getResourceType() == "coal")
			{
				cout << "Card " << myCards.getSet(i)->getNumber() << " requires, " << myCards.getSet(i)->getResourceCost() << " and " << myCards.getSet(i)->getResourceType() << endl;
				cout << "How many resources would you like to put? A maximum of " << myCards.getSet(i)->getResourceCost() * 2 << " can be put." << endl;
				
				int costChoice;
				int costLoop = 0;
				while (costLoop == 0)
				{
					cin >> costChoice;
					if (costChoice< 0 || costChoice >myCards.getSet(i)->getResourceCost() * 2)
					{
						cout << "Invalid range. Try again." << endl;
					}
					else
					{
						if (myResources.getCoal() >= myCards.getSet(i)->getResourceCost())
						{
							myResources.setCoal(myResources.getCoal() - costChoice);
							myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() + costChoice);
						}
						else
						{
							cout << "You do not have enough coal" << endl;
						}
					}
					costLoop = 1;
				}
			}
			else if (myCards.getSet(i)->getResourceType() == "oil")
			{
				cout << "Card " << myCards.getSet(i)->getNumber() << " requires, " << myCards.getSet(i)->getResourceCost() << " and " << myCards.getSet(i)->getResourceType() << endl;
				cout << "How many resources would you like to put? A maximum of " << myCards.getSet(i)->getResourceCost() * 2 << " can be put." << endl;
				
				int costChoice;
				int costLoop = 0;
				while (costLoop == 0)
				{
					cin >> costChoice;
					if (costChoice< 0 || costChoice >myCards.getSet(i)->getResourceCost() * 2)
					{
						cout << "Invalid range. Try again." << endl;
					}
					else
					{
						if (myResources.getOil() >= myCards.getSet(i)->getResourceCost())
						{
							myResources.setOil(myResources.getOil() - costChoice);
							myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() + costChoice);
						}
						else
						{
							cout << "You do not have enough oil" << endl;
						}
					}
					costLoop = 1;
				}
			}
			else if (myCards.getSet(i)->getResourceType() == "garbage")
			{
				cout << "Card " << myCards.getSet(i)->getNumber() << " requires, " << myCards.getSet(i)->getResourceCost() << " and " << myCards.getSet(i)->getResourceType() << endl;
				cout << "How many resources would you like to put? A maximum of " << myCards.getSet(i)->getResourceCost() * 2 << " can be put." << endl;

				int costChoice;
				int costLoop = 0;
				while (costLoop == 0)
				{
					cin >> costChoice;
					if (costChoice< 0 || costChoice >myCards.getSet(i)->getResourceCost() * 2)
					{
						cout << "Invalid range. Try again." << endl;
					}
					else
					{
						if (myResources.getGarbage() >= myCards.getSet(i)->getResourceCost())
						{
							myResources.setGarbage(myResources.getGarbage() - costChoice);
							myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() + costChoice);
						}
						else
						{
							cout << "You do not have enough garbage" << endl;
						}
					}
					costLoop = 1;
				}
			}
			else if (myCards.getSet(i)->getResourceType() == "uranium")
			{
				cout << "Card " << myCards.getSet(i)->getNumber() << " requires, " << myCards.getSet(i)->getResourceCost() << " and " << myCards.getSet(i)->getResourceType() << endl;
				cout << "How many resources would you like to put? A maximum of " << myCards.getSet(i)->getResourceCost() * 2 << " can be put." << endl;

				int costChoice;
				int costLoop = 0;
				while (costLoop == 0)
				{
					cin >> costChoice;
					if (costChoice< 0 || costChoice >myCards.getSet(i)->getResourceCost() * 2)
					{
						cout << "Invalid range. Try again." << endl;
					}
					else
					{
						if (myResources.getUranium() >= myCards.getSet(i)->getResourceCost())
						{
							myResources.setUranium(myResources.getUranium() - costChoice);
							myCards.getSet(i)->setCurrentResource(myCards.getSet(i)->getCurrentResource() + costChoice);
						}
						else
						{
							cout << "You do not have enough uranium" << endl;
						}
					}
					costLoop = 1;
				}
			}
			else if (myCards.getSet(i)->getResourceType() == "none")
			{
				cout << "Card " << myCards.getSet(i)->getNumber() << " requires, " << myCards.getSet(i)->getResourceCost() << " and " << myCards.getSet(i)->getResourceType() << endl;
				cout << "This card does not require any resources." << endl;
			}
			else
			{ }
		}
		else
		{

		}
		
	}
}