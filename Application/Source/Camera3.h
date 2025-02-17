#ifndef CAMERA_3_H
#define CAMERA_3_H

/******************************************************************************/
/*!
\file	Camera3.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare functions and members for camera
*/
/******************************************************************************/

#include "Camera.h"

class Camera3 : public Camera
{
	float temp_store;
public:
	
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 defaultTargetwhere;

	Vector3 targetwhere;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, float w, float h, double* xpos, double* ypos);
	virtual void Reset();

};

#endif