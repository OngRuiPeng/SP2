/******************************************************************************/
/*!
\file	main.cpp
\author SP'13 2015
\par	nyp
\brief
CPP to run application
*/
/******************************************************************************/

#include "Application.h"

int main( void )
{
	Application app;
	app.Init();
	app.Run();
	app.Exit();
}