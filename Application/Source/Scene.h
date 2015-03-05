#ifndef SCENE_H
#define SCENE_H

/******************************************************************************/
/*!
\file	Scene.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare functions and members for Scene
*/
/******************************************************************************/

#include "GL\glew.h"
#include "GLFW\glfw3.h"


class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init(GLFWwindow* m_window, float w, float h) = 0;
	virtual void Update(double dt, GLFWwindow* m_window, float w, float h) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif