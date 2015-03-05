/******************************************************************************/
/*!
\file	Item.cpp
\author Jun Yan
\par	nyp
\brief
CPP to define functions initialising CItem class objs
*/
/******************************************************************************/

#include "Item.h"
#include <iostream>

/******************************************************************************/
/*!
\brief
default constructor for item class
*/
/******************************************************************************/
CItem::CItem(void)
{
	Item_Name = "";
	Item_Desc = "";
	count = 0 ;
}

/******************************************************************************/
/*!
\par name , description and int counter
\brief
construct and set item
*/
/******************************************************************************/
CItem::CItem(string Name,string Desc,int counter)
{
	Item_Name = Name ;
	Item_Desc = Desc;
	count = counter;
}

/******************************************************************************/
/*!
\par name , description and int counter
\brief
set item data member
*/
/******************************************************************************/
void CItem::Set(string Name,string Desc,int counter)
{
	Item_Name = Name ;
	Item_Desc = Desc;
	count = counter;
}

CItem::~CItem(void)
{
}

/******************************************************************************/
/*!
\par name
\brief
sets name of item
*/
/******************************************************************************/
void CItem::setItemName(string newName)
{
	Item_Name = newName;
}

/******************************************************************************/
/*!
\par description
\brief
sets description of item
*/
/******************************************************************************/
void CItem::setItemDesc(string newDesc)
{
	Item_Desc = newDesc;
}

/******************************************************************************/
/*!
\brief
returns name of item
*/
/******************************************************************************/
string CItem::getItemName()
{
	return Item_Name;
}

/******************************************************************************/
/*!
\brief
returns description of item
*/
/******************************************************************************/
string CItem::getItemDesc()
{
	return Item_Desc;
}

/******************************************************************************/
/*!
\par int for count
\brief
sets the number of item it exists in inventory/checklist
*/
/******************************************************************************/
void CItem::setItemCount(int a )
{
	count = a;
}

/******************************************************************************/
/*!
\brief
returns the count of item 
*/
/******************************************************************************/
int CItem::getItemCount()
{
	return count;
}

/******************************************************************************/
/*!
\brief
sets everything to be null for an item
*/
/******************************************************************************/
void CItem::setNull()
{
	Item_Name = "";
	Item_Desc = "";
	count = NULL;
}