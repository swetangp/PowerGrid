//Strategy.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once
class Strategy
{
public:
	virtual int pass() = 0;
	virtual int auction() = 0;
	virtual int buy() = 0;
	virtual int build() = 0;
};