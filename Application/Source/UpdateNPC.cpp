#include "SceneSP.h"

bool PB2LForward = true;
bool PB2RForward = false;
float WalkingSpeed = 100.f;
void SceneSP::UpdateNPC(double dt)
{
	//Passerby2
	if ( PB2LForward == true )
	{
		Passerby2Left += (WalkingSpeed * dt);
		if ( Passerby2Left > 45 )
		{
			PB2LForward = false;
		}
	}
	else
	{
		Passerby2Left -= (WalkingSpeed * dt);
		if ( Passerby2Left < -45 )
		{
			PB2LForward = true;
		}
	}
	if ( PB2RForward == true )
	{
		Passerby2Right += (WalkingSpeed * dt);
		if ( Passerby2Right > 45 )
		{
			PB2RForward = false;
		}
	}
	else
	{
		Passerby2Right -= (WalkingSpeed * dt);
		if ( Passerby2Right < -45 )
		{
			PB2RForward = true;
		}
	}
	Passerby2Dist += (5 * dt);
	if ( Passerby2Dist > 100 )
	{
		Passerby2Dist = 0;
	}
}