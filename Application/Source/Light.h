#ifndef LIGHT_H
#define LIGHT_H

/******************************************************************************/
/*!
\file	Light.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare functions and members for light
*/
/******************************************************************************/

#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;

	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;


};



#endif