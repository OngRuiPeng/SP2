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

void Camera3::Update(double dt,float width, float height, double* xpos, double* ypos)
{
	double mouseX = width;
	double mouseY = height;
	std::cout << *xpos << std::endl;
	std::cout << *ypos << std::endl;
	static const float CAMERA_SPEED = 20.f;
	static const float MOVE_SPEED = 100.0f;

	if(Application::IsKeyPressed('A')){
		Vector3 view = (target - position).Normalize();
		Vector3 right = view.Cross(up);
		position -= right* MOVE_SPEED * dt;
		target -= right * MOVE_SPEED * dt;

	}

	if(Application::IsKeyPressed('D')){
		Vector3 view = (target - position).Normalize();
		Vector3 right = view.Cross(up);
		position += right* MOVE_SPEED * dt;
		target += right * MOVE_SPEED * dt;

	}

	if(Application::IsKeyPressed('W')){
		Vector3 view = (target - position).Normalize();
		view.y = 0 ;
		position += view * MOVE_SPEED * dt;
		target += view * MOVE_SPEED * dt;

	}

	if(Application::IsKeyPressed('S')){
		Vector3 view = (target - position).Normalize();
		view.y = 0 ;
		position -= view * MOVE_SPEED * dt;
		target -= view * MOVE_SPEED * dt;

	}

	if(Application::IsKeyPressed(VK_LEFT) || (*xpos < mouseX))
	{
		float yaw = (float)(CAMERA_SPEED * dt * (mouseX - *xpos));
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		target = rotation * (target - position) + position;
		up = rotation * up;
		temp_store += yaw;
	}

	if(Application::IsKeyPressed(VK_RIGHT) || (*xpos > mouseX))
	{
		float yaw = (float)(-CAMERA_SPEED * dt * (*xpos - mouseX));
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		target = rotation * (target - position) + position;
		up = rotation * up;
		temp_store += yaw;
	}

	if(Application::IsKeyPressed(VK_UP) && target.y < 200 || (*ypos < mouseY))
	{
		float pitch = (float)(CAMERA_SPEED * dt * (mouseY - *ypos));
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		target = rotation * (target - position) + position;
	}

	if(Application::IsKeyPressed(VK_DOWN) && target.y > -100 || (*ypos > mouseY))
	{
		float pitch = (float)(-CAMERA_SPEED * dt * (*ypos - mouseY));
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