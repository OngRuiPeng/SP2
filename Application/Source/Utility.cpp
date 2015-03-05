/******************************************************************************/
/*!
\file	Utility.cpp
\author SP'13 2015
\par	nyp
\brief
CPP to define functions for operation and also to convert float to string 
*/
/******************************************************************************/

#include "Utility.h"

Position operator*(const Mtx44& lhs, const Position& rhs)
{

	float b[4];
	for(int i = 0; i < 4; i++)
		b[i] = lhs.a[0 * 4 + i] * rhs.x + lhs.a[1 * 4 + i] * rhs.y + lhs.a[2 * 4 + i] * rhs.z + lhs.a[3 * 4 + i] * 1;
	return Position(b[0], b[1], b[2]);

}

std::string Convert (float number){
    std::ostringstream buff;
    buff<< std::setprecision(2) <<number;
    return buff.str();   
}

std::string Converts (float number){
    std::ostringstream buff;
    buff<< std::setprecision(3) <<number;
    return buff.str();   
}