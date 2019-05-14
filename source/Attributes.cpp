//Attributes.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "Attributes.h"

//Default constructor
Houses::Houses()
{
	colour = "red";
	number = 22;

}
Houses::Houses(string col, int num)
{
	colour = col;
	number = num;
}
void Houses:: setColour(string col)
{
	colour = col;
}
void Houses::setNum(int num)
{
	number = num;
}

//Default Constructor
Resources::Resources()
{
	coal = 24;
	oil = 24;
	garbage = 24;
	uranium = 12;
}
Resources::Resources(int cl, int ol, int gb, int ur)
{
	coal = cl;
	oil = ol;
	garbage = gb;
	uranium = ur;
}
void Resources::setCoal(int cl)
{
	coal = cl;
}
void Resources::setOil(int ol)
{
	oil = ol;
}
void Resources::setGarbage(int gb)
{
	garbage = gb;
}
void Resources::setUranium(int ur)
{
	uranium = ur;
}