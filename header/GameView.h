//GameView.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once
#include "Observer.h"
#include "Map.h"
#include "Player.h"

class GameView : public Observer
{
public:
	GameView();
	GameView(Map m, Player p);
	GameView(Player p);
	~GameView();
	void Update();
	void display();
	void turnInformationDisplay(int x, Map m, Player p, Card AMC);
	void usefulInformation();
private:
	Map viewMap;
	Player viewPlayer;
};