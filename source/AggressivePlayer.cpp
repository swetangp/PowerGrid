//AggressivePlayer.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "AggressivePlayer.h"
int AggressivePlayer:: pass()
{
	cout << "You are an aggressive player who has chosen to pass." << endl;
	return 1;
}
int AggressivePlayer::auction()
{
	return 1; //By returning 1 the player will constantly bid on a power plant as long as player has sufficient elektro
}
int AggressivePlayer::buy()
{
	return 1; //By returning 1 the player will try to buy resources if the player has sufficient elektro
}
int AggressivePlayer::build()
{
	return 1; //By returning 1 the player will try to build cities if the player has sufficient elektro
}