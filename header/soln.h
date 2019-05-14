#pragma once

#ifndef _SOLNS_H_INCLUDED_
#define _SOLNS_H_INCLUDED_
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

class soln
{
public:
	soln();
	soln(int ng)
	{
		newg = ng;
	}
private:
	int newg;
};
class SummaryCard2
{
public:
	SummaryCard2();
	void displaySummary();
	void displayScoring();
};
class PowerPlantCard2
{
public:
	PowerPlantCard2();
	PowerPlantCard2(int n, string rT, int rC, string rT2, int rC2, string c, int hC);
	int number;
	string resourceType;
	int resourceCost;
	string resourceType2;
	int resourceCost2;
	string colour;
	int houseCost;

	void Shuffle();
	vector<PowerPlantCard2> set;
};
#endif;