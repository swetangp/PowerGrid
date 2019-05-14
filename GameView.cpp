//GameView.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "GameView.h"
//This file is the Observer design pattern also known as a view port for parts 1 and 2
GameView::GameView()
{
}

GameView::GameView(Map m, Player p)
{
	viewMap = m;
	viewPlayer = p;
}

GameView::GameView(Player  p)
{
	viewPlayer = p;
	viewPlayer.Attach(this);
}

GameView::~GameView()
{
	viewPlayer.Detach(this);
}

void GameView::Update()
{
	display();
}
//Displays a header of the current player as well the step they are on
void GameView::display()
{
	int playerNumber = viewPlayer.getTurnOrder();
	int playerStep = viewPlayer.getStep();
	

	//Header, displays current Player and current step.

	if (playerStep == 1)
	{
		cout << "===================================================================" << endl;
		cout << "===================" << "Player " << playerNumber << " turn" << "=====================================" << endl;
		cout << "===================================================================" << endl;
		cout << " You are currently on step " << playerStep << endl;
	}
	else if (playerStep == 2)
	{
		cout << "===================================================================" << endl;
		cout << "===================" << "Player " << playerNumber << " turn" << "=====================================" << endl;
		cout << "===================================================================" << endl;
		cout << " You are currently on step " << playerStep << endl;
	}
	else
	{
		cout << "===================================================================" << endl;
		cout << "===================" << "Player " << playerNumber << " turn" << "=====================================" << endl;
		cout << "===================================================================" << endl;
		cout << " You are currently on step " << playerStep << endl;
	}
}
//Displays a header concerning to which phase they are currently playing on
void GameView::turnInformationDisplay(int x, Map m, Player p, Card AMC)
{
	if (x == 1)
	{

	}
	else if (x == 2)
	{
		cout << "=======================================================================" << endl;
		cout << "============ The current phase being played: Auction Phase ============" << endl;
		cout << "=======================================================================" << endl;
	}
	else if (x == 3)
	{
		cout << "=======================================================================" << endl;
		cout << "=== The current phase being played: Buying Resource, Housing Phase ====" << endl;
		cout << "=======================================================================" << endl;
	}
}

//Displays the players statistics and other information in the viewport
void GameView::usefulInformation()
{
	cout << "=======================================================================" << endl;
	cout << "============== Player " << viewPlayer.getTurnOrder()<< " locations =================" << endl;
	cout << "=======================================================================" << endl;
	viewMap.checkMyCity(viewPlayer);
	cout << "Procession view" << endl;
	cout << "=======================================================================" << endl;
	int c = viewMap.countTotalCityForPlayer(viewPlayer);
	int x = 0;
	while (x != c)
	{
		cout << "|||| ";
		x++;
	}
	cout << endl;
	x = 0;
	while (x != c)
	{
		cout << "    "<<x+1;
		x++;
	}
	cout << endl;
	cout << "===============" << endl;
	cout << "===Resources===" << endl;
	cout << "===============" << endl;
	viewPlayer.getMyResources();
	cout << "===============" << endl;
	cout << "===Elektro===" << endl;
	cout << "===============" << endl;
	viewPlayer.displayMyMoney();
	cout << "===============" << endl;
	cout << "===Houses===" << endl;
	cout << "===============" << endl;
	viewPlayer.displayMyHouses();
}
