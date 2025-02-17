#ifndef APPLICATION_H
#define APPLICATION_H

/******************************************************************************/
/*!
\file	Application.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare Application members and functions
*/
/******************************************************************************/

#include "timer.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>
class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

	double getWidth();
	double getHeight();

private:

	double width;
	double height;

	//Declare a window object
	StopWatch m_timer;
};

#endif