//MapDriver.cpp
//COMP345 Assignment #2 
//Swetang Patel 28/03/2019
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Map.h"
#include "Player.h"
#include "Attributes.h"
#include "Card.h"
#include "GameView.h"
#include "AggressivePlayer.h"
#include "ModeratePlayer.h"
#include "Singleton.h"
#include <algorithm> 
#include <ctime>        
#include <cstdlib>
#include <experimental/filesystem>

//To access the files in directory
namespace directoryFiles = experimental::filesystem;
struct displayFilesOfDirectory
{
	string typeOfExt;
	displayFilesOfDirectory(string const& typeOfExt) : typeOfExt(typeOfExt) {}
	bool operator()(directoryFiles::directory_entry const& dF) const
	{
		return dF.path().extension() == typeOfExt;
	}
};
int rngMethod(int i)
{
	return std::rand() % i;
};
void Shuffle(vector<Player>set)
{
	srand(unsigned(std::time(0)));
	std::random_shuffle(set.begin(), set.end());
}
void errorLoad()
{
	cout << "An error has occured loading this file" << endl;
}
void incrementLoop(void)
{
	Singleton::instance()->increaseValue();
}
int returnLcount()
{
	return Singleton::instance()->getLvalue();
}
void staticZero(void)
{
	Singleton::instance()->setToZero();
}

using namespace std;

int main()
{
	try
	{
		directoryFiles::path line = ".";

		//Use of vector to keep track of all files in the directory
		vector<directoryFiles::directory_entry> directoryFiles;

		//Takes files that only have the .txt extension
		directoryFiles::directory_iterator st(line);
		directoryFiles::directory_iterator last;

		copy_if(st, last, back_inserter(directoryFiles),
			displayFilesOfDirectory(".txt"));

		//All the files labelled with ".txt" extensions will be displayed here
		cout << "Here are the files listed in your directory" << endl;
		for (auto const& myFiles : directoryFiles)
		{
			if (myFiles.path().string() == "")
			{
				cout << "No files can be found." << endl;
			}
			else
			{
				cout << myFiles.path().string() << '\n';
			}
		}
	}
	//A catch statement is provided in case an exception occurs. Perhaps broadening the exception pool to pinpoint problems can useful in the future
	catch (exception unexpectedError)
	{
		cout << "An error has occured please try again." << endl;
	}
	cout << "Type in the file name you wish to pick" << endl;
	string pick;
	cin >> pick;

	/*
		Map Loader was moved to the main driver due to difficulties with returning the whole map as a value.
	*/
	string inputFile = pick;
	const int size = 100;
	Houses h;
	int count = 0;
	int loadTime = 0;
	int esc = 0;
	ifstream sizeOfArray(inputFile);
	vector<string> arraySize;

	//Measure current number of cities in which the array size is determined
	if (sizeOfArray.is_open())
	{

		string line;
		while (esc == 0)
		{

			getline(sizeOfArray, line);
			stringstream notData(line);
			string blank;
			getline(notData, blank, ',');

			if (blank == "[Cities]")
			{
				esc = 1;
			}
			if (loadTime == 200)
			{
				errorLoad();
			}
			loadTime++;
		}
		while (getline(sizeOfArray, line))
		{

			stringstream det(line);
			string estTerr;
			getline(det, estTerr, ',');
			if (estTerr != "")
			{
				count++;
				arraySize.push_back(estTerr);
			}

		}
	}
	sizeOfArray.close();
	City t[size] = {};


	//Stores City names in array
	ifstream terNames(inputFile);
	if (terNames.is_open())
	{
		int i = 0;
		string line;
		esc = 0;


		while (esc == 0)
		{
			getline(terNames, line);
			stringstream notData(line);
			string blank;
			getline(notData, blank, ',');

			if (blank == "[Cities]")
			{

				esc = 1;
			}

		}

		while (getline(terNames, line))
		{
			stringstream ss1(line);
			string estTerr;
			getline(ss1, estTerr, ',');
			if (estTerr != "")
			{
				t[i] = City(estTerr, "null", 0, 0, 0, h);
				i++;
			}
		}
	}
	terNames.close();

	//This will allow the program to establish the edges of each City.
	Map PowerGrid;

	City* tp[size];

	for (int i = 0; i < size; i++)
	{
		tp[i] = &t[i];
	}
	ifstream last(inputFile);

	//Having each name of the city stored, we can now find out what data the city has regarding to its cost and its edges to other cities by opening the file one last time.
	if (last.is_open())
	{
		int i = 0;
		string line;
		esc = 0;

		while (esc == 0)
		{
			getline(last, line);
			stringstream notData(line);
			string blank;
			getline(notData, blank, ',');

			if (blank == "[Cities]")
			{
				esc = 1;
			}

		}

		while (getline(last, line))
		{
			stringstream ss(line);
			string city, color, c1, c2, c3;

			getline(ss, city, ',');
			getline(ss, color, ',');
			getline(ss, c2, ',');
			getline(ss, c3, ',');


			stringstream convert(c1);
			int iNum1 = 0;
			convert >> iNum1;
			stringstream convert1(c2);
			int iNum2 = 0;
			convert1 >> iNum2;
			stringstream convert2(c3);
			int iNum3 = 0;
			convert2 >> iNum3;
			if (city != "")
			{
				t[i] = City(city, color, iNum1, iNum2, iNum3, h);

				vector<string> connection;
				string cityConnect;
				while (getline(ss, cityConnect, ','))
				{
					connection.push_back(cityConnect);
					for (int z = 0; z < size; z++)
					{
						if (cityConnect == t[z].getName())
						{

							string cost;
							getline(ss, cost, ',');
							stringstream convert3(cost);
							int iNum4 = 0;
							convert3 >> iNum4;
							t[i].createConnection(tp[z], iNum4);
							z = size + 1;
						}

					}
				}
				if (city == "")
				{
					i--;
				}
				i++;
			}
		}
	}
	last.close();

	//Establishes connection points
	for (int i = 0; i < size; i++)
	{
		tp[i] = &t[i];
	}
	//Each City is placed on the map and are connected
	for (int j = 0; j < size; j++)
	{
		PowerGrid.create(tp[j]);
	}
	//Error check for duplicates
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; i++)
		{
			if (i == j)
			{
				j++;
			}

			if (tp[i]->getName() == tp[j]->getName() && tp[i]->getName() != "")
			{
				PowerGrid.errorLoad();
			}
		}
	}
	//Displays loaded map
	//PowerGrid.printMap();


	//User Interaction
	//This will demonstrate Assignment 2, as it can be seen below I ran into a little trouble with parts 1 and 2, and thus could not make it continuous with parts 3 and 4.
	//Hopefully this will be fixed by end.
	cout << "1. Parts 1 " << endl;
	cout << "2. Parts 2" << endl;
	cout << "3. Part 3 and 4" << endl;
	cout << "4. Gameview" << endl;
	int choice;
	cin >> choice;


	//Part 1 will be explained below.
	if (choice == 1)
	{
		vector<Player> p;
		Player p1;
		p1.setPlayerTurn(1);
		Player p2;
		p2.setPlayerTurn(2);
		p.push_back(p1);
		p.push_back(p2);
		Card ppc;
		Card actualMarketCard;
		Card futureMarketCard;
		actualMarketCard.clearVector();
		futureMarketCard.clearVector();
		actualMarketCard.addElement(*ppc.getSet(0));
		actualMarketCard.addElement(*ppc.getSet(1));
		actualMarketCard.addElement(*ppc.getSet(2));
		actualMarketCard.addElement(*ppc.getSet(3));
		futureMarketCard.addElement(*ppc.getSet(4));
		futureMarketCard.addElement(*ppc.getSet(5));
		futureMarketCard.addElement(*ppc.getSet(6));
		futureMarketCard.addElement(*ppc.getSet(7));
		ppc.eraseElement(3);ppc.eraseElement(4);ppc.eraseElement(5);ppc.eraseElement(6);ppc.eraseElement(7);ppc.eraseElement(8);


		int mainGameLoop = 0;

		while (mainGameLoop == 0)
		{
			//Phase 1: Determine player order
			if (p[0].getCurrentTurn() == p[1].getCurrentTurn())
			{

				int randomNum;
				srand(time(NULL));
				randomNum = rand() % 10 + 1;
				if (randomNum % 2 == 0)
				{
					p[0].setCurrentTurn(1);
					p[1].setCurrentTurn(2);
					cout << "Player order is determined." << endl;
				}
				else
				{
					p[0].setCurrentTurn(2);
					p[1].setCurrentTurn(1);
					cout << "Player order is determined." << endl;
				}
				Shuffle(p);

			}
			//Phase 2: Auction
			int myCost = 0;
			int z;
			int i = 0;
			int j = 0;

			int exit = 9;
			while (exit == 9)
			{
				//The player will now be presented a list of cards in which they can select and auction for.
				if (p[i].getCurrentTurn() < p[j].getCurrentTurn())
				{
					GameView g(PowerGrid, p[i]);
					p[i] =g.usefulDisplay(choice, PowerGrid, p[i], actualMarketCard);
				}
				else
				{
					GameView g(PowerGrid, p[j]);
					p[j]=g.usefulDisplay(choice, PowerGrid, p[j], actualMarketCard);
				}
				if(p[0].getPassVal()== 0 || p[1].getPassVal()==0)
				{
					exit = 10;
					mainGameLoop = 1; 
				}
			}
		}
	}
	else if (choice == 2)
	{
		vector<Player> p;
		Player p1;
		p1.setPlayerTurn(1);
		Player p2;
		p2.setPlayerTurn(2);
		p.push_back(p1);
		p.push_back(p2);
		Card ppc;
		Card actualMarketCard;
		Card futureMarketCard;
		actualMarketCard.clearVector();
		futureMarketCard.clearVector();
		actualMarketCard.addElement(*ppc.getSet(0));
		actualMarketCard.addElement(*ppc.getSet(1));
		actualMarketCard.addElement(*ppc.getSet(2));
		actualMarketCard.addElement(*ppc.getSet(3));
		futureMarketCard.addElement(*ppc.getSet(4));
		futureMarketCard.addElement(*ppc.getSet(5));
		futureMarketCard.addElement(*ppc.getSet(6));
		futureMarketCard.addElement(*ppc.getSet(7));
		ppc.eraseElement(3);ppc.eraseElement(4);ppc.eraseElement(5);ppc.eraseElement(6);ppc.eraseElement(7);ppc.eraseElement(8);


		int mainGameLoop = 0;

		while (mainGameLoop == 0)
		{
			//Phase 1: Determine player order
			if (p[0].getCurrentTurn() == p[1].getCurrentTurn())
			{

				int randomNum;
				srand(time(NULL));
				randomNum = rand() % 10 + 1;
				if (randomNum % 2 == 0)
				{
					p[0].setCurrentTurn(1);
					p[1].setCurrentTurn(2);
					cout << "Player order is determined." << endl;
				}
				else
				{
					p[0].setCurrentTurn(2);
					p[1].setCurrentTurn(1);
					cout << "Player order is determined." << endl;
				}
				Shuffle(p);

			}
			//Phase 2: Auction
			int myCost = 0;
			int z;
			int i = 0;
			int j = 0;

			int exit = 9;
			while (exit == 9)
			{
				//The player will now be presented a list of cards in which they can select and auction for.
				if (p[i].getCurrentTurn() < p[j].getCurrentTurn())
				{
					cout << "Player " << p[i].getTurnOrder() << " will begin the auction phase." << endl;
					actualMarketCard.displayPowerPlantCards();
					cout << "Choose a card which you wish to bid for. Or you can pass by typing '99'" << endl;
					int choose;
					cin >> choose;
					int bid = 1;

					//If the don't wish to bid for a card the can use the pass function. The pass function will store a value and prevent them from bidding on anything else this turn.
					if (choose == 99)
					{
						p[i].pass();
					}
					else
					{
						int x = 0;
						for (z = 0; z < actualMarketCard.sizeOfSet() && x != -1; z++)
						{
							if (choose == actualMarketCard.getSet(z)->getNumber())
							{
								cout << "You have made a bid on Card " << actualMarketCard.getSet(z)->getNumber() << ", of elektro cost of " << actualMarketCard.getSet(z)->getNumber() << endl;
								actualMarketCard.getSet(z)->setToPlayer(i);
								bid = 0;
								x = -1;

							}
						}

					}
					//The initial bidding phase will now begin players can compete with each other here by raising the elektro cost
					while (bid == 0)
					{
						cout << "Would player " << p[j].getTurnOrder() << " like to make a bid?" << endl;
						cin >> choose;
						if (choose != 99 && p[j].getPassVal() != 0)
						{
							cout << "The bid you place must be higher then the last price" << endl;

							cin >> myCost;

							if (myCost > actualMarketCard.getSet(z)->getNumber());
							{
								actualMarketCard.getSet(z)->setToPlayer(j);
							}

						}
						else
						{
							p[j].pass();
							bid = -1;

							if (j == 0)
							{
								p[1].setMyMoney(p[1].getMyMoney() - myCost);
							}
							else
							{
								p[0].setMyMoney(p[0].getMyMoney() - myCost);
							}
						}
						if (j >= p.size())
						{
							j = 0;
						}
						else
						{
							j++;
						}
					}
				}
				//The player will now be presented a list of cards in which they can select and auction for.
				else
				{
					cout << "Player " << p[i].getTurnOrder() << " will begin the auction phase." << endl;
					actualMarketCard.displayPowerPlantCards();
					cout << "Choose a card which you wish to bid for. Or you can pass by typing '99'" << endl;
					int cardNum;
					cin >> cardNum;
					int bid = 1;

					//If the don't wish to bid for a card the can use the pass function. The pass function will store a value and prevent them from bidding on anything else this turn.
					if (cardNum == 99)
					{
						p[i].pass();
					}
					//Selection of the card to begin bidding.
					else
					{
						int x = 0;
						for (z = 0; z < actualMarketCard.sizeOfSet() && x != -1; z++)
						{
							if (cardNum == actualMarketCard.getSet(z)->getNumber())
							{
								cout << "You have made a bid on Card " << actualMarketCard.getSet(z)->getNumber() << ", of elektro cost of " << actualMarketCard.getSet(z)->getNumber() << endl;
								actualMarketCard.getSet(z)->setToPlayer(i);
								cout << z << endl;
								bid = 0;
								x = -1;

							}
						}

					}
					//The bidding phase in which players must compete with each other
					while (bid == 0)
					{
						int choice;
						cout << "Would player " << p[j].getTurnOrder() << " like to make a bid? Or pass (99)" << endl;
						cin >> choice;
						if (choice != 99 && p[j].getPassVal() != 0)
						{
							cout << "The bidz you place must be higher then the last price" << endl;

							cin >> myCost;

							if (myCost >= actualMarketCard.getSet(z)->getNumber())
							{
								actualMarketCard.getSet(z)->setToPlayer(j);

							}
							else
							{
								cout << "You have bid less then the previous player. You lost the auction." << endl;
								p[j].pass();
								bid = -1;

								if (j == 0)
								{
									p[1].setMyMoney(p[1].getMyMoney() - myCost);
									p[1].addCard(*actualMarketCard.getSet(z));
								}
								else
								{
									p[0].setMyMoney(p[0].getMyMoney() - myCost);
									p[0].addCard(*actualMarketCard.getSet(z));
								}
								actualMarketCard.eraseElement(cardNum);

							}


						}
						else
						{
							p[j].pass();
							bid = -1;

							if (j == 0)
							{
								p[1].setMyMoney(p[1].getMyMoney() - myCost);
								p[1].addCard(*actualMarketCard.getSet(z));
							}
							else
							{
								p[0].setMyMoney(p[0].getMyMoney() - myCost);
								p[0].addCard(*actualMarketCard.getSet(z));
							}
							actualMarketCard.eraseElement(cardNum);

						}
						if (j >= p.size() - 1)
						{
							j = 0;
						}
						else
						{
							j++;
						}
					}
				}

				exit = 10;
				mainGameLoop = 1;
			}
		}
	}

	//PART 3, phase 3 and 4
	else if (choice == 3)
	{
		//Example player pool used  for demo.
		Player p1, p2, p3;
		vector<Player> p;
		p.push_back(p1);p.push_back(p2);p.push_back(p3);
		p[0].setCurrentTurn(0);p[1].setCurrentTurn(2);p[2].setCurrentTurn(1);
		p[0].setPlayerTurn(1);p[1].setPlayerTurn(2);p[2].setPlayerTurn(3);
		p[0].setStartRegion("purple");p[1].setStartRegion("yellow");p[2].setStartRegion("teal");
		PowerGrid.setCityForPlayer(p[0], "purple");PowerGrid.setCityForPlayer(p[1], "yellow");PowerGrid.setCityForPlayer(p[2], "teal");

		//The players will also be assigned power plant cards for demonstration purposes.
		Card ppc;
		Card actualMarketCard;
		Card futureMarketCard;
		actualMarketCard.clearVector();
		futureMarketCard.clearVector();

		//Adding cards the present and future market and removing them from power plant card deck (main deck).
		actualMarketCard.addElement(*ppc.getSet(0));
		actualMarketCard.addElement(*ppc.getSet(1));
		actualMarketCard.addElement(*ppc.getSet(2));
		actualMarketCard.addElement(*ppc.getSet(3));
		futureMarketCard.addElement(*ppc.getSet(4));
		futureMarketCard.addElement(*ppc.getSet(5));
		futureMarketCard.addElement(*ppc.getSet(6));
		futureMarketCard.addElement(*ppc.getSet(7));
		ppc.eraseElement(3);ppc.eraseElement(4);ppc.eraseElement(5);ppc.eraseElement(6);ppc.eraseElement(7);ppc.eraseElement(8);

		p[0].clearCard();p[1].clearCard();p[2].clearCard();

		p[0].addCard(*actualMarketCard.getSet(0));

		p[1].addCard(*actualMarketCard.getSet(1));

		p[2].addCard(*actualMarketCard.getSet(2));

		actualMarketCard.eraseElement(0/*actualMarketCard.getSet(0)->getNumber()*/);
		actualMarketCard.eraseElement(1/*actualMarketCard.getSet(1)->getNumber()*/);
		actualMarketCard.eraseElement(2/*actualMarketCard.getSet(2)->getNumber()*/);

		//Attributes for checking player number and to ensure this phase is played in reverse order.
		int loop = 0;
		//int checkTurnOrder = 0;
		int reverseOrder = p.size() - 1;


		//THIS IS THE BUYING RESOURCE PHASE.
		while (loop == 0)
		{
			if (p[returnLcount()].getCurrentTurn() == reverseOrder)
			{

				//Decision tree in which if the player buys resources for their cards.
				cout << "Would Player " << p[returnLcount()].getTurnOrder() << ", like to buy any resources for their select properties?" << endl;
				cout << p[returnLcount()].getCardTotal() << endl;
				p[returnLcount()].displayMyCards();
				cout << "Type the card number in which you want to buy resources for." << endl;

				int cardChoice;
				cin >> cardChoice;

				p[returnLcount()].setResourcesOnCard(cardChoice);
				reverseOrder--;
			}
			//checkTurnOrder++;
			incrementLoop();
			if (returnLcount() >= p.size())
			{
				//checkTurnOrder = 0;
				staticZero();
			}
			if (reverseOrder == -1)
			{
				loop = 1;
			}
		}

		//Attributes for checking player number and to ensure this phase is played in reverse order.
		loop = 0;
		//int checkTurnOrder = 0;
		staticZero();
		reverseOrder = p.size() - 1;
		//THIS IS THE HOUSING PHASE
		while (loop == 0)
		{
			if (p[returnLcount()].getCurrentTurn() == reverseOrder)
			{

				//This if statement is for starting games when choosing the first city or if a player still does not have any houses on the map.
				if (p[returnLcount()].getMyHouses() == 22)
				{
					//A decision tree in which the player must decide to build a house in the city of the colour they chose.
					cout << "Would Player " << p[returnLcount()].getTurnOrder() << ", like to build any houses in the city of their color" << endl;
					cout << "These are the cities in which you can start in." << endl;
					PowerGrid.displayColorCity(p[returnLcount()].getStartRegion());
					cout << "Pick a city in which you will start in by typing its name. (Example: Seattle)" << endl;
					string cityChoice;
					cin >> cityChoice;

					int cost = PowerGrid.setCityForPlayer(p[returnLcount()], cityChoice);
					if (cost == 0)
					{
						cout << "City has no houses to place." << endl;
					}
					else if (cost == 1)
					{
						cout << "House has been placed at a spot open for 10 elektro" << endl;
						p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() - 10);
						p[returnLcount()].setMyHouses(p[returnLcount()].getMyHouses() - 1);
					}
					else if (cost == 2)
					{
						cout << "House has been placed at a spot open for 15 elektro" << endl;
						p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() - 15);
						p[returnLcount()].setMyHouses(p[returnLcount()].getMyHouses() - 1);
					}
					else
					{
						cout << "House has been placed at a spot open for 20 elektro" << endl;
						p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() - 20);
						p[returnLcount()].setMyHouses(p[returnLcount()].getMyHouses() - 1);
					}
					reverseOrder--;
				}
				//This else statement will be executed if the player already has a house on the map.
				else
				{
					//A decision tree in which the player must decide to build a house on the map by traversal to other city and collecting the net elektro to that city.
					cout << "Would Player " << p[returnLcount()].getTurnOrder() << ", like to build any new houses" << endl;
					PowerGrid.printMap();
					cout << "\nHere is a map of neighbouring cities around your currently owned cities." << endl;
					PowerGrid.checkMyCity(p[returnLcount()]);
					cout << "Choose a city in which you would like to establish a new house" << endl;
					string newCity;
					cin >> newCity;
					cout << "Choose a city in which you already own" << endl;
					string myCity;
					cin >> myCity;

					int costForNewCity = PowerGrid.ownNewCity(p[returnLcount()], newCity, myCity);

					if (costForNewCity == -1)
					{
						cout << "No available housing is left on that city" << endl;
					}
					else
					{
						PowerGrid.setCityForPlayer(p[returnLcount()], newCity);
						p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() - costForNewCity);
					}
					reverseOrder--;
				}

			}
			//This will check whether or not every player has had one turn. If every player has had at most one turn the building phase will be over.
			//checkTurnOrder++;
			incrementLoop();
			if (returnLcount() >= p.size())
			{
				//checkTurnOrder = 0;
				staticZero();
			}
			if (reverseOrder == -1)
			{
				loop = 1;
			}
		}

		//This is the Bureacracy phase, which consists of players earning cash by providing electricity, resupplying the resource market, and removing powerplant cards and putting them into future market and into present market
		//This will be played in normal order
		int normalOrder = 0;
		loop = 0;
		//checkTurnOrder = 0;
		staticZero();

		//Players in this phase will be allowed to generate elektro depending on how their resources look with their power plant cards they own.
		while (loop == 0)
		{
			if (p[returnLcount()].getCurrentTurn() == normalOrder)
			{
				//A decision tree in which the player can sell their resources to power their cities and fetch a potential higher elektro or not sell and generate 10 elektro
				cout << "Does player " << p[returnLcount()].getCurrentTurn() << " wish to supply electricity to their city?" << endl;
				int decision;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl;
				cin >> decision;

				//The player will now be displayed how many cities they own on the map and up to how many cities they can provide electricity to.
				//The player can also decide how many cities they wish they can provide electricity to.
				if (decision == 1)
				{
					int myCityTotal = PowerGrid.countTotalCityForPlayer(p[returnLcount()]);
					cout << "You own " << myCityTotal << " on the map." << endl;

					cout << "You can provide electricity for up to, " << p[returnLcount()].determineHousePower() << " cities." << endl;
					cout << "How many cities do you wish to provide electricity to?" << endl;

					//A loop to make sure the player enters a valid range.
					int invalidDecision = 0;
					while (invalidDecision == 0)
					{
						cin >> decision;
						if (decision<0 || decision > myCityTotal)
						{
							cout << "Enter valid range." << endl;
						}
						else
						{
							invalidDecision = -1;
						}
					}
					//The player will now have to give up their resources on their powerplant cards and provide electricity for those cities.
					cout << "You are providing electricity to " << decision << " cities. You must remove resources to provide sufficient electricity" << endl;
					p[returnLcount()].removeResources(decision);

					//In return to removing the resources from their powerplant cards, they will now generate elektro depending on how many cities they powered.
					if (decision == 0) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 10); }
					if (decision == 1) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 22); }
					if (decision == 2) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 33); }
					if (decision == 3) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 44); }
					if (decision == 4) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 54); }
					if (decision == 5) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 64); }
					if (decision == 6) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 73); }
					if (decision == 7) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 82); }
					if (decision == 8) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 90); }
					if (decision == 9) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 98); }
					if (decision == 10) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 105); }
					if (decision == 11) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 112); }
					if (decision == 12) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 118); }
					if (decision == 13) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 124); }
					if (decision == 14) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 129); }
					if (decision == 15) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 134); }
					if (decision == 16) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 138); }
					if (decision == 17) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 142); }
					if (decision == 18) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 145); }
					if (decision == 19) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 148); }
					if (decision == 20) { p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 150); }

				}
				//If the player did not power any city this turn they will be provided 10 elektro
				else
				{
					cout << "You have not supplied any electricity to any of your cities. 10 Elektro will be provided to you." << endl;
					p[returnLcount()].setMyMoney(p[returnLcount()].getMyMoney() + 10);
				}

				normalOrder++;
			}
			//Loop checker to make sure each player has had one turn.
			else
			{
				//checkTurnOrder++;
				incrementLoop();
				if (returnLcount() >= p.size())
				{
					//checkTurnOrder = 0;
					staticZero();
				}
				if (normalOrder >= p.size())
				{
					loop = 1;
				}
			}

		}
		//Resupplying the Resource Market
		cout << "Resupplying market. . . Done!" << endl;
		PowerGrid.resupply(p.size());

		//Updating PowerPlant Market
		int compare = 0;
		for (int j = 0; j < futureMarketCard.sizeOfSet(); j++)
		{
			if (futureMarketCard.getSet(compare)->getNumber() < futureMarketCard.getSet(j)->getNumber())
			{
				compare = j;
			}
		}
		//Adding new card to present market from future market
		//Adding new card from powerplant deck to future market
		actualMarketCard.addElement(*futureMarketCard.getSet(compare));
		futureMarketCard.eraseElement(futureMarketCard.getSet(compare)->getNumber());
		ppc.Shuffle();
		futureMarketCard.addElement(*ppc.getSet(0));

		system("pause");
		return 1;
	}
	else if (choice == 4)
	{
		//Example player pool used  for demo.
		Player p1, p2, p3;
		vector<Player> p;
		p.push_back(p1);p.push_back(p2);p.push_back(p3);
		p[0].setCurrentTurn(0);p[1].setCurrentTurn(2);p[2].setCurrentTurn(1);
		p[0].setPlayerTurn(1);p[1].setPlayerTurn(2);p[2].setPlayerTurn(3);
		p[0].setStartRegion("purple");p[1].setStartRegion("yellow");p[2].setStartRegion("teal");
		PowerGrid.setCityForPlayer(p[0], "purple");PowerGrid.setCityForPlayer(p[1], "yellow");PowerGrid.setCityForPlayer(p[2], "teal");

		//The players will also be assigned power plant cards for demonstration purposes.
		Card ppc;
		Card actualMarketCard;
		Card futureMarketCard;
		actualMarketCard.clearVector();
		futureMarketCard.clearVector();

		//Adding cards the present and future market and removing them from power plant card deck (main deck).
		actualMarketCard.addElement(*ppc.getSet(0));
		actualMarketCard.addElement(*ppc.getSet(1));
		actualMarketCard.addElement(*ppc.getSet(2));
		actualMarketCard.addElement(*ppc.getSet(3));
		futureMarketCard.addElement(*ppc.getSet(4));
		futureMarketCard.addElement(*ppc.getSet(5));
		futureMarketCard.addElement(*ppc.getSet(6));
		futureMarketCard.addElement(*ppc.getSet(7));
		ppc.eraseElement(3);ppc.eraseElement(4);ppc.eraseElement(5);ppc.eraseElement(6);ppc.eraseElement(7);ppc.eraseElement(8);

		p[0].clearCard();p[1].clearCard();p[2].clearCard();

		p[0].addCard(*actualMarketCard.getSet(0));

		p[1].addCard(*actualMarketCard.getSet(1));

		p[2].addCard(*actualMarketCard.getSet(2));

		actualMarketCard.eraseElement(0/*actualMarketCard.getSet(0)->getNumber()*/);
		actualMarketCard.eraseElement(1/*actualMarketCard.getSet(1)->getNumber()*/);
		actualMarketCard.eraseElement(2/*actualMarketCard.getSet(2)->getNumber()*/);
		//Attributes for checking player number and to ensure this phase is played in reverse order.
		int loop = 0;
		int checkTurnOrder = 0;
		int reverseOrder = p.size() - 1;


		int x = 0;
		int i = 0;

		while (x == 0)
		{

			if (p[checkTurnOrder].getCurrentTurn() == reverseOrder)
			{
				GameView myView(PowerGrid, p[checkTurnOrder]);
				myView.display();
				//p[checkTurnOrder]=myView.usefulDisplay();

				//Decision tree in which if the player buys resources for their cards.
				/*cout << "Would Player " << p[checkTurnOrder].getTurnOrder() << ", like to buy any resources for their select properties?" << endl;
				cout << p[checkTurnOrder].getCardTotal() << endl;
				p[checkTurnOrder].displayMyCards();
				cout << "Type the card number in which you want to buy resources for." << endl;

				int cardChoice;
				cin >> cardChoice;

				p[checkTurnOrder].setResourcesOnCard(cardChoice);*/
				reverseOrder--;
			}
			checkTurnOrder++;
			if (checkTurnOrder >= p.size())
			{
				checkTurnOrder = 0;
			}
			if (reverseOrder == -1)
			{
				loop = 1;
			}
		}

	}
	else if (choice == 5)
	{
		/*vector<Player> p;
		Player p1(new AggressivePlayer);
		Player p2(new ModeratePlayer);
		p1.setPlayerTurn(1);
		Player p2;
		p2.setPlayerTurn(2);
		p.push_back(p1);
		p.push_back(p2);
		Card ppc;
		Card actualMarketCard;
		Card futureMarketCard;
		actualMarketCard.clearVector();
		futureMarketCard.clearVector();
		actualMarketCard.addElement(*ppc.getSet(0));
		actualMarketCard.addElement(*ppc.getSet(1));
		actualMarketCard.addElement(*ppc.getSet(2));
		actualMarketCard.addElement(*ppc.getSet(3));
		futureMarketCard.addElement(*ppc.getSet(4));
		futureMarketCard.addElement(*ppc.getSet(5));
		futureMarketCard.addElement(*ppc.getSet(6));
		futureMarketCard.addElement(*ppc.getSet(7));
		ppc.eraseElement(3);ppc.eraseElement(4);ppc.eraseElement(5);ppc.eraseElement(6);ppc.eraseElement(7);ppc.eraseElement(8);


		int mainGameLoop = 0;

		while (mainGameLoop == 0)
		{
			//Phase 1: Determine player order
			if (p[0].getCurrentTurn() == p[1].getCurrentTurn())
			{

				int randomNum;
				srand(time(NULL));
				randomNum = rand() % 10 + 1;
				if (randomNum % 2 == 0)
				{
					p[0].setCurrentTurn(1);
					p[1].setCurrentTurn(2);
					cout << "Player order is determined." << endl;
				}
				else
				{
					p[0].setCurrentTurn(2);
					p[1].setCurrentTurn(1);
					cout << "Player order is determined." << endl;
				}
				Shuffle(p);

			}
			//Phase 2: Auction
			int myCost = 0;
			int z;
			int i = 0;
			int j = 0;

			int exit = 9;
			while (exit == 9)
			{
				//The player will now be presented a list of cards in which they can select and auction for.
				cout << "Player " << p[i].getTurnOrder() << " will auction" << endl;
				actualMarketCard.displayPowerPlantCards();
				int choose = 33;

				if (p[i].auctionStrategy() == 1)
				{
					if (p[i].getMyMoney() > actualMarketCard.getSet(0)->getNumber())
					{
						actualMarketCard.getSet(0)->setToPlayer(i);
					}
				}
				else if (p[i].auctionStrategy() == 2)
				{
					if ((p[i].getMyMoney() / 2) > actualMarketCard.getSet(0)->getNumber())
					{
						actualMarketCard.getSet(0)->setToPlayer(i);
					}
				}
				else if (p[i].getMyMoney() < 0)
				{
					p[i].setPassVal = p[i].passingStrategy();
				}
				else
				{
					p[i].pass();
				}
				i++;
				if (i > p.size())
				{
					i = 0;
				}
		}*/

	}
}



