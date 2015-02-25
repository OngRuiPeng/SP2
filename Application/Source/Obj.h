#include <iostream>

#include "Vector3.h"

using namespace std; 

class Obj
{
private:
	bool empty;
public: 
	Vector3 min,max; 

	Obj();
	~Obj();

	void setEmpty(bool isit);

	bool getEmpty();

	void set(Vector3 maximum,Vector3 minimum);
};