//AggressivePlayer.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once
#include "Strategy.h"
#include <iostream>
#include <string>
using namespace std;
class AggressivePlayer : public Strategy
{
public:
	int pass();
	int auction();
	int buy();
	int build();
};