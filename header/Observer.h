//Observer.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once

class Observer
{
public:
	~Observer();
	virtual void Update() = 0;
protected:
	Observer();
};