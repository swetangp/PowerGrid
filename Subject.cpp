//Subject.cpp
//COMP345 Assignment #3
//Swetang Patel 12/04/2019
#include "Subject.h"
#include "Observer.h"
Subject::Subject() {
	
}
Subject::~Subject() {
	
}
void Subject::Attach(Observer* o) {
	_observers.push_back(o);
};
void Subject::Detach(Observer* o) {
	//_observers.erase(o);
};
void Subject::Notify() {
	vector<Observer *>::iterator i = _observers.begin();
	for (int i = 0; i < _observers.size(); ++i)
	{
		_observers[i]->Update();
	}
		
};
