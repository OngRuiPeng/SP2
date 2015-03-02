#include <iostream>

#include "Vector3.h"
#include <string>

using namespace std; 

class Obj
{
private:
	bool empty;
	int number;
public: 
	Vector3 min,max;
	Obj();
	~Obj();

	Obj(Vector3 maximum , Vector3 minimum ) ;

	void setEmpty(bool isit);

	bool getEmpty();

	void set(Vector3 maximum,Vector3 minimum);

	void set(int a );

	int getNo();

};