#include "SceneSP.h"

void SceneSP::SlidingDoor(double dt)
{
	if (camera.position.x <= 9 && camera.position.x >= -7 && camera.position.z >= -16 && camera.position.z <= 2)
	{
		if (DoorSlide >= -5)
		{
			DoorSlide -= (double)(3 * dt);
		}
	}

	else
	{
		if (DoorSlide < -0.75  )
		{	
			DoorSlide += (double)(3 * dt);
		}

	}

}

void SceneSP::Jump (double dt)
{

	if (camera.position.y > 10 )
	{
		JumpDirection = false;
	}

	if (JumpDirection == true && JumpState == true)
	{
		camera.target.y += (double)(12 * dt);
		camera.targetwhere.y += (double)(12 * dt);
		camera.position.y += (double)(12 * dt);
	}

	else if (JumpDirection == false && JumpState == true)
	{
		if ( camera.position.y > 6 )
		{
			camera.target.y -= (double)(12 * dt);
			camera.targetwhere.y -= (double)(12 * dt);
			camera.position.y -= (double)(12 * dt);
		}
		else if (camera.position.y < 7 )
		{
			JumpState = false;
		}


	}

}