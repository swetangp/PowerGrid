#include "Singleton.h"
Singleton::Singleton()
{
	Lvalue = 0;
}
int Singleton::getLvalue()
{
	return Lvalue;
}
void Singleton::increaseValue()
{
	Lvalue++;
}
void Singleton::setToZero()
{
	Lvalue = 0;
}

