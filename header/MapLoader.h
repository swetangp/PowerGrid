#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class Territory;
class Continent
{
public:
	Continent();
	Continent(string n, int num);
	string name;
	int number;
};
class Connection
{
public:
	Connection(Territory* st, Territory* en, int id);
	Territory* getStart()
	{
		return start;
	}
	Territory* getEnd()
	{
		return end;
	}
	int getIdentity()
	{
		return identity;
	}
private:
	Territory* start;
	Territory* end;
	int identity;
};

class Territory
{
public:
	Territory();
	Territory(string n, int pl, int ar, string cont);
	string getName()
	{
		return name;
	}
	string getContinent()
	{
		return continent;
	}
	int getPlayer()
	{
		return player;
	}
	int getArmy()
	{
		return army;
	}
	void createConnection(Territory* cT, int id);
	void display();
	string name;
	string continent;
	int player;
	int army;
	vector<Connection> connection;
};

class Map
{
public:
	Map();
	Map(string au, string wrn, string img, string wrp, string scr);
	void errorLoad();
	void create(Territory* t);
	void printMap();
	void loadMap(string inputFile);
	string author, warn, image, wrap, scroll;
private:
	vector<Territory*> point;
};