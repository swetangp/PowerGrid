//ModeratePlayer.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "ModeratePlayer.h"
int ModeratePlayer:: pass()
{
	cout << "You are a moderate player who has chosen to pass." << endl;
	return 2;
}
int ModeratePlayer::auction()
{

	return 2; //By returning 2 the player will always consider their elektro and try not to spend over 50% during the auction phase
}
int ModeratePlayer::buy()
{
	return 2; //By returning 2 the player will always consider whether or not their resources are worth it and determine whether they need to switch power plants.
}
int ModeratePlayer::build()
{
	return 2; //By returning  2 the player will always try to protect their cities and expand when available.
}