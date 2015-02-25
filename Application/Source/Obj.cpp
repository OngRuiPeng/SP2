#include "Obj.h"

Obj::Obj() 
{
	min = Vector3(0,0,0);
	max = Vector3(0,0,0);
	empty = false;
}

Obj::~Obj()
{
}

void Obj::set(Vector3 maximum,Vector3 minimum)
{
	min = minimum; 
	max = maximum;
}

void Obj::setEmpty(bool isit)
{
	empty = isit ;
}

bool Obj::getEmpty()
{
	return empty;
}

