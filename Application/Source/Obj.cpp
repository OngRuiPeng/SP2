/******************************************************************************/
/*!
\file	Obj.cpp
\author Jun Sen
\par	nyp
\brief
Defining functions used to initialise OBJs for collision 
*/
/******************************************************************************/

#include "Obj.h"

Obj::Obj() 
{
	max = Vector3(0,0,0);
	min = Vector3(0,0,0);
	empty = false;
	number = 9;
}

Obj::~Obj()
{
}

Obj::Obj(Vector3 maximum , Vector3 minimum)
{
	max = maximum ; 
	min = minimum ; 
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

void Obj::set(int a)
{
	number = a ;
}

int Obj::getNo()
{
	return number;
}