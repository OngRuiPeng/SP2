/******************************************************************************/
/*!
\file	Npc.cpp
\author Rui Peng
\par	nyp
\brief
CPP to define functions initialising Npc class objs
*/
/******************************************************************************/

#include "Npc.h"


CNpc::CNpc(void)
{
	name = "";
	type = "";
}

CNpc::~CNpc(void)
{
}

void CNpc::setName(string tempname)
{
	name = tempname;
}

void CNpc::setType(string temptype)
{
	type = temptype;
}

string CNpc::getName(void)
{
	return name;
}

string CNpc::getType(void)
{
	return type;
}
string CNpc::CashierWelcome(void)
{
	return "Welcome to J Mart";
}

string CNpc::CashierLeave(void)
{
	return "Thank you for shopping at J Mart";
}

string CNpc::CSpeech(void)
{
	return "Hello";
}

string CNpc::SSpeech(void)
{
	return "What ya looking at?";
}
