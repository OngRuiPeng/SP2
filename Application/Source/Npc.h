#pragma once

/******************************************************************************/
/*!
\file	Npc.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare functions and members for CNpc class
*/
/******************************************************************************/

#include <string>
using namespace std;

class CNpc
{
public:
	string name;
	string type;
	string dialogue[6];

	CNpc(void);
	~CNpc(void);
	void setName(string);
	void setType(string);
	string getName(void);
	string getType(void);
	string CashierWelcome(void);
	string CashierLeave(void);
	string CSpeech(void);
	string SSpeech(void);
};

