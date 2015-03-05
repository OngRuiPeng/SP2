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

/******************************************************************************/
/*!
\brief
default constructor
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\par 2 vector3
\brief
set maximum and minimum when constructed
*/
/******************************************************************************/
Obj::Obj(Vector3 maximum , Vector3 minimum)
{
	max = maximum ; 
	min = minimum ; 
}

/******************************************************************************/
/*!
\par 2 vector3
\brief
set maximum and minimum
*/
/******************************************************************************/
void Obj::set(Vector3 maximum,Vector3 minimum)
{
	min = minimum; 
	max = maximum;
}

/******************************************************************************/
/*!
\par bool 
\brief
set empty to be true or false
*/
/******************************************************************************/
void Obj::setEmpty(bool isit)
{
	empty = isit ;
}

/******************************************************************************/
/*!
\brief
returns whether an object is empty or not 
*/
/******************************************************************************/
bool Obj::getEmpty()
{
	return empty;
}

/******************************************************************************/
/*!
\par int 
\brief
set the number(item) of the obj
*/
/******************************************************************************/
void Obj::set(int a)
{
	number = a ;
}

/******************************************************************************/
/*!
\brief
returns the number(item) of the obj
*/
/******************************************************************************/
int Obj::getNo()
{
	return number;
}