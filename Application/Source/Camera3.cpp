#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 100.f;
	if(Application::IsKeyPressed('A')){
		Vector3 view = (target - position).Normalize();
		Vector3 right = view.Cross(up);
		position -= right* CAMERA_SPEED * dt;
		target -= right * CAMERA_SPEED * dt;

	}

	if(Application::IsKeyPressed('D')){
		Vector3 view = (target - position).Normalize();
		Vector3 right = view.Cross(up);
		position += right* CAMERA_SPEED * dt;
		target += right * CAMERA_SPEED * dt;

	}

	if(Application::IsKeyPressed('W')){
		Vector3 view = (target - position).Normalize();
		view.y = 0 ;
		position += view * CAMERA_SPEED * dt;
		target += view * CAMERA_SPEED * dt;

	}

	if(Application::IsKeyPressed('S')){
		Vector3 view = (target - position).Normalize();
		view.y = 0 ;
		position -= view * CAMERA_SPEED * dt;
		target -= view * CAMERA_SPEED * dt;

	}

	if(Application::IsKeyPressed(VK_LEFT))
	{
		float yaw = (float)(CAMERA_SPEED * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		target = rotation * (target - position) + position;
		up = rotation * up;
		temp_store += yaw;
	}

	if(Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = (float)(-CAMERA_SPEED * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		target = rotation * (target - position) + position;
		up = rotation * up;
		temp_store += yaw;
	}

	if(Application::IsKeyPressed(VK_UP) && target.y < 200)
	{
		float pitch = (float)(CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		target = rotation * (target - position) + position;
	}

	if(Application::IsKeyPressed(VK_DOWN) && target.y > -100)
	{
		float pitch = (float)(-CAMERA_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		target = rotation * (target - position) + position;
	}

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}


	position.y = 20;

	if ( position.x >= 480) 
	{
		position.x = 480; 
	}

	if ( position.x <= -480) 
	{
		position.x = -480; 
	}

	if ( position.z >= 480) 
	{
		position.z = 480; 
	}

	if ( position.z <= -480) 
	{
		position.z = -480; 
	}
	// end of boundary for skybox

}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}