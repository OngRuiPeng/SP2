#include "SceneSP.h"
#include "Application.h"
ISoundEngine* engine2 = createIrrKlangDevice(ESOD_AUTO_DETECT,ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
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

		if ( cam_state == CAM5 )
		{
		camera.target = Vector3(0,6,-31);
		}
		else
		camera.target = Vector3(4,6,21);
	}

	if (Application::IsKeyPressed('N') && CamTime > 1 )
	{
        ISound* cameraswitch = engine2->play2D("../irrKlang/media/camera.mp3", false);
		cam_state = (cam_state + 1 ) % 6 ;
		CamTime = 0 ;
		
		if ( cam_state == CAM5 )
		{
		camera.target = Vector3(0,6,-31);
		}
		else
		camera.target = Vector3(4,6,21);
	}

}
