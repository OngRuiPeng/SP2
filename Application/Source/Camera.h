#ifndef CAMERA_H
#define CAMERA_H

/******************************************************************************/
/*!
\file	Camera.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare functions and members for camera
*/
/******************************************************************************/

#include "Vector3.h"

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif