//Subject.h
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#pragma once
#include "Observer.h"
#include <vector>
using namespace std;
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();
private:
	vector<Observer*> _observers;
};
