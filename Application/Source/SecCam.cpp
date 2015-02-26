#include "SceneSP.h"
#include "Application.h"

void SceneSP::updateCam(double dt)
{
	if ( cam_state == NORMAL )
	{
		camera.position = StorePos;
		camera.target = StoreTarget1;
		camera.targetwhere = StoreTarget2;

		SecurityCam = false;
	}
	else if ( cam_state == CAM1 )
	{
		camera.position = Vector3(24.5,15,-4.7);
	}
	else if ( cam_state == CAM2 )
	{
		camera.position = Vector3(25.5,15,36.4);
	}
	else if ( cam_state == CAM3 )
	{
		camera.position = Vector3(-23.5,15,36);
	}
	else if ( cam_state == CAM4 )
	{
		camera.position = Vector3(-23.5,15,-4.8);
	}
	else if ( cam_state == CAM5 )
	{
		camera.position = Vector3(0.2,15,-11.5);
	}

	CamTime += dt;

	if (Application::IsKeyPressed('Y') && CamTime > 1 )
	{
		cam_state = (cam_state - 1 ) % 6 ;
		CamTime = 0 ;
	}

	if (Application::IsKeyPressed('N') && CamTime > 1 )
	{
		cam_state = (cam_state + 1 ) % 6 ;
		CamTime = 0 ;
	}

}
