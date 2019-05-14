//Map.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "Map.h"

Connection::Connection(City* st, City* en, int id)
{
	start = st;
	end = en;
	identity = id;
}

//Default constructor
City::City()
{
	p1.setPlayerTurn(0);
	p2.setPlayerTurn(0);
	p3.setPlayerTurn(0);
}
City::City(string col)
{
	color = col;
}
City::City(string n, string col, int c1, int c2, int c3, Houses h)
{
	name = n;
	color = col;
	cost1 = c1;
	cost2 = c2;
	cost3 = c3;
	p1.setPlayerTurn(0);
	p2.setPlayerTurn(0);
	p3.setPlayerTurn(0);
}

//Creates the edges between nodes
void City::createConnection(City* cT, int id)
{
	Connection createNewConnection(this, cT, id);
	connection.push_back(createNewConnection);
}
//Current map view
void City::display()
{
	cout << " " << name << " " << endl;
	for (int i = 0; i < connection.size(); i++)
	{
		Connection c = connection[i];
		cout << c.getEnd()->getName() << " - " << c.getIdentity()/*c.getEnd()->getPlayer()*/ << ", belongs to, Player " << c.getEnd()->getPlayerNum() << endl;
	}
	cout << endl;
}
//The traversal cost from one city to another.
int City::connectionCost(string nc)
{
	for (int i = 0; i < connection.size(); i++)
	{
		Connection c = connection[i];
		if(c.getEnd()->getName() == nc)
		{ 
			return c.getIdentity();
		}
	}
	return -1;
}
//Displays the cities corresponding to a certain colour
void City::displayRegion()
{
	cout << " " << name << " " << endl;
	for (int i = 0; i < connection.size(); i++)
	{
		Connection c = connection[i];
		cout << c.getEnd()->getName() << " - " << c.getIdentity()/*c.getEnd()->getPlayer()*/ << ", COLOR: " << c.getEnd()->getColor() << endl;
	}
	cout << endl;
}

//Default construcor in which creates the initial resource board
Map::Map()
{
	mapResource.push_back(Resources(3, 0, 0, 0));
	mapResource.push_back(Resources(3, 0, 0, 0));
	mapResource.push_back(Resources(3, 3, 0, 0));
	mapResource.push_back(Resources(3, 3, 0, 0));
	mapResource.push_back(Resources(3, 3, 0, 0));
	mapResource.push_back(Resources(3, 3, 0, 0));
	mapResource.push_back(Resources(3, 3, 3, 0));
	mapResource.push_back(Resources(3, 3, 3, 0));
	mapResource.push_back(Resources(0, 0, 0, 0));
	mapResource.push_back(Resources(0, 0, 0, 0));
	mapResource.push_back(Resources(0, 0, 0, 0));
	mapResource.push_back(Resources(0, 0, 0, 0));
	mapResource.push_back(Resources(0, 0, 0, 0));
	mapResource.push_back(Resources(0, 0, 0, 1));
	mapResource.push_back(Resources(0, 0, 0, 0));
	mapResource.push_back(Resources(0, 0, 0, 1));
}
Map::Map(string au, string wrn, string img, string wrp, string scr)
{
	author = au;
	warn = wrn;
	image = img;
	wrap = wrp;
	scroll = scr;
}
//Stores city node pointer into a vector
void Map::create(City* t)
{
	point.push_back(t);
}
//Displays all cities on the map regarding who owns what or what isn't occupied
void Map::printMap()
{
	for (int i = 0; i < point.size(); i++)
	{
		if (point[i]->getName() == "")
		{
			i = point.size() - 1;
		}
		point[i]->display();
	}
}
void Map::printRegion()
{
	for (int i = 0; i < point.size(); i++)
	{
		if (point[i]->getName() == "")
		{
			i = point.size() - 1;
		}
		point[i]->displayRegion();
	}
}
//View information of a single city regarding to who owns it
void Map::getPoint(int x)
{
	point[x]->getPlayerNum();
}
//Error message when loading a map fails
void Map::errorLoad()
{
	std::cerr << "This is an invalid map. Please try another map" << endl;
	system("pause");
	exit(1);
}
//The map loader in which a .map is read and uses its stored data to create a map.
void Map::loadMap(string inputFile)
{
	const int size = 1000;
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
				t[i] = City(estTerr,"null", 0, 0, 0, h);
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
			string city,color, c1, c2, c3;

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
			
			if (tp[i]->getName() == tp[j]->getName() &&tp[i]->getName()!="")
			{
				errorLoad();
			}
		}
	}
	//Displays loaded map
	PowerGrid.printMap();
}
int Map::setCityForPlayer(Player p, string cityName)
{
	//A city can have up to 3 houses, this will check if any are free and display the appropriate elektro value (10,15,20) depending on which is free.
	for (int i = 0; i < point.size(); i++)
	{
		if (point[i]->getName() == cityName && point[i]->getHouse1()==0)
		{
			point[i]->setHouse1(p);
			i = point.size();
			return 1;
		}
		else if (point[i]->getName() == cityName && point[i]->getHouse2() == 0)
		{
			point[i]->setHouse2(p);
			i = point.size();
			return 2;
		}
		else if (point[i]->getName() == cityName && point[i]->getHouse3() == 0)
		{
			point[i]->setHouse3(p);
			i = point.size();
			return 3;
		}
		else
		{
			
		}
	}
	return 0;
}
//Getting a city by its colour property
void Map::displayColorCity(string sn)
{
	for (int i = 0; i < point.size(); i++)
	{
		if (point[i]->getColor() == sn)
		{
			point[i]->displayRegion();
		}
	}
}
//The resupply phase in which the board resources are replenished depending on the events that taken place that round.
void Map::resupply(int x)
{
	for (int i = 0; i < mapResource.size(); i++)
	{
		if (x == 2)
		{
			if (mapResource[i].getCoal() < 3)
			{
				mapResource[i].setCoal(mapResource[i].getCoal() + 3);
			}
			if (mapResource[i].getOil() < 3)
			{
				mapResource[i].setOil(mapResource[i].getOil() + 2);
			}
			if (mapResource[i].getGarbage() < 3)
			{
				mapResource[i].setGarbage(mapResource[i].getGarbage() + 1);
			}
			if (mapResource[i].getUranium() == 0)
			{
				mapResource[i].setUranium(mapResource[i].getUranium() + 1);
			}	
		}
		else if (x == 3)
		{
			if (mapResource[i].getCoal() < 3)
			{
				mapResource[i].setCoal(mapResource[i].getCoal() + 3);
			}
			if (mapResource[i].getOil() < 3)
			{
				mapResource[i].setOil(mapResource[i].getOil() + 2);
			}
			if (mapResource[i].getGarbage() < 3)
			{
				mapResource[i].setGarbage(mapResource[i].getGarbage() + 1);
			}
			if (mapResource[i].getUranium() == 0)
			{
				mapResource[i].setUranium(mapResource[i].getUranium() + 1);
			}

		}
		else if (x == 4)
		{
			if (mapResource[i].getCoal() < 3)
			{
				mapResource[i].setCoal(mapResource[i].getCoal() + 3);
			}
			if (mapResource[i].getOil() < 3)
			{
				mapResource[i].setOil(mapResource[i].getOil() + 2);
			}
			if (mapResource[i].getGarbage() < 3)
			{
				mapResource[i].setGarbage(mapResource[i].getGarbage() + 1);
			}
			if (mapResource[i].getUranium() == 0)
			{
				mapResource[i].setUranium(mapResource[i].getUranium() + 1);
			}
		}
		else if (x == 5)
		{
			if (mapResource[i].getCoal() < 3)
			{
				mapResource[i].setCoal(mapResource[i].getCoal() + 3);
			}
			if (mapResource[i].getOil() < 3)
			{
				mapResource[i].setOil(mapResource[i].getOil() + 2);
			}
			if (mapResource[i].getGarbage() < 3)
			{
				mapResource[i].setGarbage(mapResource[i].getGarbage() + 1);
			}
			if (mapResource[i].getUranium() == 0)
			{
				mapResource[i].setUranium(mapResource[i].getUranium() + 1);
			}
		}
		else
		{
			if (mapResource[i].getCoal() < 3)
			{
				mapResource[i].setCoal(mapResource[i].getCoal() + 3);
			}
			if (mapResource[i].getOil() < 3)
			{
				mapResource[i].setOil(mapResource[i].getOil() + 2);
			}
			if (mapResource[i].getGarbage() < 3)
			{
				mapResource[i].setGarbage(mapResource[i].getGarbage() + 1);
			}
			if (mapResource[i].getUranium() == 0)
			{
				mapResource[i].setUranium(mapResource[i].getUranium() + 1);
			}
		}
	}
}
//Counts the total number of houses across the multiple cities on the map for a player
int Map::countTotalCityForPlayer(Player p)
{
	int count = 0;
	for (int i = 0; i < point.size(); i++)
	{
		if (point[i]->getHouse1() == p.getTurnOrder())
		{
			count++;
		}
		else if (point[i]->getHouse2() == p.getTurnOrder())
		{
			count++;
		}
		else if (point[i]->getHouse3() == p.getTurnOrder())
		{
			count++;
		}
		else
		{

		}
	}
	return count;
}
//Checks to see if the player has any city on the map
void Map::checkMyCity(Player p)
{
	for (int i = 0; i < point.size(); i++)
	{
		if (point[i]->getHouse1() == p.getTurnOrder())
		{
			point[i]->displayRegion();
		}
		else if (point[i]->getHouse2() == p.getTurnOrder())
		{
			point[i]->displayRegion();
		}
		else if (point[i]->getHouse3() == p.getTurnOrder())
		{
			point[i]->displayRegion();
		}
	}
}
//If a player wants to own a new city
int Map::ownNewCity(Player p, string nc, string oc)
{
	//This is the traversal cost.
	int costForCity = 0;
	for (int i = 0; i < point.size(); i++)
	{
		if (point[i]->getName() == oc)
		{
			costForCity = point[i]->connectionCost(nc);
		}
	}
	if (costForCity == -1)
	{
		return -1;
	}
	//Checks whether any houses are available from cheapest to highest
	for (int j = 0; j < point.size(); j++)
	{
		if (point[j]->getName() == nc)
		{
			if (point[j]->getHouse1() != 0)
			{
				cout << "Housing for 10 elektro is taken" << endl;
			}
			else if (point[j]->getHouse2() != 0)
			{
				cout << "Housing for 15 elektro is taken" << endl;
			}
			else if (point[j]->getHouse3() != 0)
			{
				cout << "Housing for 20 elektro is taken" << endl;
			}
			else if (point[j]->getHouse1() == 0)
			{
				cout << "Housing for 10 elektro free. A house will be placed on this city" << endl;
				return (10 + costForCity);
			}
			else if (point[j]->getHouse2() == 0)
			{
				cout << "Housing for 15 elektro free. A house will be placed on this city" << endl;
				return (15 + costForCity);
			}
			else if (point[j]->getHouse3() == 0)
			{
				cout << "Housing for 20 elektro free. A house will be placed on this city" << endl;
				return (20 + costForCity);
			}
			else
			{

			}
		}
	}
	return -1;
}