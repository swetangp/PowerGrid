//Attributes.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once
#ifndef _ATTRIBUTES_H_INCLUDED_
#define _ATTRIBUTES_H_INCLUDED_

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Houses
{
public:
	Houses();
	Houses(string col, int num);
	string getColour()
	{
		return colour;
	}
	int getNumber()
	{
		return number;
	}
	void setColour(string col);
	void setNum(int num);
private:
	string colour;
	int number=25;
};

class Resources
{
public:
	Resources();
	Resources(int cl, int ol, int gb, int ur);
	int getCoal()
	{
		return coal;
	}
	int getOil()
	{
		return oil;
	}
	int getGarbage()
	{
		return garbage;
	}
	int getUranium()
	{
		return uranium;
	}
	void setCoal(int cl);
	void setOil(int ol);
	void setGarbage(int gb);
	void setUranium(int ur);
private:
	int coal;
	int oil;
	int garbage;
	int uranium;
};
#endif