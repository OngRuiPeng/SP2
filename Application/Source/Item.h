#pragma once

/******************************************************************************/
/*!
\file	Item.h
\author Jun Yan
\par	nyp
\brief
CPP to declare functions and members for CItem class
*/
/******************************************************************************/

#include <iostream>
using namespace std;
class CItem 
{
private:
	string Item_Name;
	string Item_Desc;

	int count ;
public:
	CItem(void);
	~CItem(void);

	CItem(string Name,string Desc,int counter);

	void Set(string Name,string Desc, int counter);

	void setItemName(string Name);
	void setItemDesc(string Desc);
	void setItemCount(int a );

	void setNull();

	string getItemName();
	string getItemDesc();
	int getItemCount();
};

