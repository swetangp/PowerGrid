//EnvironmentalistPlayer.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "EnvironmentalistPlayer.h"
int EnvironmentalistPlayer::pass()
{
	cout << "You are a environmentailist player who has chosen to pass." << endl;
	return 3;
}
int EnvironmentalistPlayer::auction()
{

	return 3; //By returning 3 the player will always consider a good Powerplant cards that have low resource costs.
}
int EnvironmentalistPlayer::buy()
{
	return 3; //By returning 3 the player will always consider whether or not their resources are worth it and determine whether they need to switch power plants.
}
int EnvironmentalistPlayer::build()
{
	return 3; //By returning  3 the player is more inclined on expanding slowly with the use of low resource powerplant cards
}