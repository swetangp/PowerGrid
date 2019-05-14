//Singleton.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once
class Singleton
{
private:

	int Lvalue;
	static Singleton *ptr_instance;
public:
	//Default Constructor
	Singleton()
	{
		Lvalue = 0;
	}
	//Return global value;
	int getLvalue()
	{
		return Lvalue;
	}
	//Increments global value
	void increaseValue()
	{
		Lvalue++;
	}
	//Sets global value to zero
	void setToZero()
	{
		Lvalue = 0;
	}
	//returns instance
	static Singleton *instance()
	{
		if (!ptr_instance)
		{
			ptr_instance = new Singleton();
		}
		return ptr_instance;
	}
};
Singleton* Singleton::ptr_instance = 0;