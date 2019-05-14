//Map.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once

#ifndef _MAP_H_INCLUDED_
#define _MAP_H_INCLUDED_
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Attributes.h"
#include "Player.h"
using namespace std;
class City;
class Connection
{
public:
	Connection(City* st, City* en, int id);
	City* getStart()
	{
		return start;
	}
	City* getEnd()
	{
		return end;
	}
	int getIdentity()
	{
		return identity;
	}
private:
	City* start;
	City* end;
	int identity;
};
class City
{
public:
	City();
	City(string col);
	City(string n, string col, int c1, int c2, int c3, Houses h);
	string getName()
	{
		return name;
	}
	string getColor()
	{
		return color;
	}
	int getCost1()
	{
		return cost1;
	}
	int getCost2()
	{
		return cost2;
	}
	int getCost3()
	{
		return cost3;
	}
	void setHouse1(Player p)
	{
		p1 = p;
	}
	void setHouse2(Player p)
	{
		p2 = p;
	}
	void setHouse3(Player p)
	{
		p3 = p;
	}
	int getHouse1()
	{
		if (p1.getTurnOrder() > 0)
		{
			return p1.getTurnOrder();
		}
		else
		{
			return 0;
		}
	}
	int getHouse2()
	{
		if (p2.getTurnOrder() > 0)
		{
			return p2.getTurnOrder();
		}
		else
		{
			return 0;
		}
	}
	int getHouse3()
	{
		if (p3.getTurnOrder() > 0)
		{
			return p3.getTurnOrder();
		}
		else
		{
			return 0;
		}
	}
	int getPlayerNum()
	{
		return p1.getTurnOrder();
	}
	int connectionCost(string nc);
	void createConnection(City* cT, int id);
	void displayRegion();
	void display();
	string name;
	string color;
	int cost1;
	int cost2;
	int cost3;
	Player p1;
	Player p2;
	Player p3;

	vector<Connection> connection;
};
class Map
{
public:
	Map();
	Map(string au, string wrn, string img, string wrp, string scr);
	//Start here today
	void resupply(int x);
	int ownNewCity(Player p, string nc, string oc);
	void displayColorCity(string sn);
	int setCityForPlayer(Player p, string col);
	void checkMyCity(Player p);
	int countTotalCityForPlayer(Player p);
	void errorLoad();
	void printRegion();
	void create(City* t);
	void printMap();
	void getPoint(int x);
	void loadMap(string inputFile);
	string author, warn, image, wrap, scroll;
private:
	vector<City*> point;
	vector<Resources> mapResource;
};
#endif