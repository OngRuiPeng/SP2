#include "Obj.h"

Obj::Obj() 
{
	min = Vector3(0,0,0);
	max = Vector3(0,0,0);
}

Obj::~Obj()
{
}

void Obj::set(Vector3 minumum,Vector3 maximum)
{
	min = minumum; 
	max = maximum;
}


