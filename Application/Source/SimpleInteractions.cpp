#include "SceneSP.h"

void SceneSP::SlidingDoor(double dt)
{
	if (camera.position.x <= 9 && camera.position.x >= -7 && camera.position.z >= -15 && camera.position.z <= -3)
	{
		if (DoorSlideR >= -5)
		{
			DoorSlideR -= (float)(1 * dt);
		}
	}

	else
	{
		if (DoorSlideR < -0.75  )
		{	
			DoorSlideR += (float)(1 * dt);
		}
		
	}

}