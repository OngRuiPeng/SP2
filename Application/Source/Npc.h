#pragma once
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
	string CashierWelcome(void);
	string CashierLeave(void);
	string CSpeech(void);
	string SSpeech(void);
};

