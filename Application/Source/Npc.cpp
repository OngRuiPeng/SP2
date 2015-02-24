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
	srand(0);
	int temp = rand() % 2;
	if ( temp == 1 )
	{
		return "Hello";
	}
	else
	{
		return "Fine day";
	}
}

string CNpc::SSpeech(void)
{
	srand(0);
	int temp = rand() % 2;
	if ( temp == 1 )
	{
		return "What ya looking at?";
	}
	else
	{
		return "I got my eyes on you";
	}
}
