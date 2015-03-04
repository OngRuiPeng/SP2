/******************************************************************************/
/*!
\file	Item.cpp
\author SP'13 2015
\par	nyp
\brief
CPP to define functions initialising CItem class objs
*/
/******************************************************************************/

#include "Item.h"
#include <iostream>

CItem::CItem(void)
{
	Item_Name = "";
	Item_Desc = "";
	count = 0 ;
}

CItem::CItem(string Name,string Desc,int counter)
{
	Item_Name = Name ;
	Item_Desc = Desc;
	count = counter;
}

void CItem::Set(string Name,string Desc,int counter)
{
	Item_Name = Name ;
	Item_Desc = Desc;
	count = counter;
}

CItem::~CItem(void)
{
}

void CItem::setItemName(string newName)
{
	Item_Name = newName;
}
void CItem::setItemDesc(string newDesc)
{
	Item_Desc = newDesc;
}

string CItem::getItemName()
{
	return Item_Name;
}
string CItem::getItemDesc()
{
	return Item_Desc;
}

void CItem::setItemCount(int a )
{
	count = a;
}

int CItem::getItemCount()
{
	return count;
}

void CItem::setNull()
{
	Item_Name = "";
	Item_Desc = "";
	count = NULL;
}