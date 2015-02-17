#include <iostream>

#include "Vector3.h"

using namespace std; 

class Obj
{
public: 
	Vector3 min,max; 

	Obj();
	~Obj();

	void set(Vector3 minumum,Vector3 maximum);
};