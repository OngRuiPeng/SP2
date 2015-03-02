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

void SceneSP::UpdateSG(double dt)
{
	Obj SG(SGPos + Vector3(1,20,1),SGPos - Vector3(1,4,1)); 
	Obj Tar(SGTar + Vector3(1,20,1), SGTar - Vector3(1,4,1));

	if ( InitSGOnce == true )
	{
		SGMov = SGTar - SGPos ; 
		SGMov *= 0.1;

		InitSGOnce = false;
	}

	if (AABBCheck(SG,Tar)) 
	{
		securityStay += dt;
		RotateSGLegs = 0 ; 
		MoveSGLegsOrNot = false;
	}
	else if ( AABBCheck(OBJ[0],SG) == false )
	{
		SGPos += SGMov * dt  ; 
		MoveSGLegsOrNot = true; 
	}

	if ( MoveSGLegsOrNot == true ) 
	{
		if ( MoveSGLegs == true )
		{
			if ( RotateSGLegs > 45 )
				MoveSGLegs = false;
			else
			{
				RotateSGLegs += (20 * dt);
			}
		}
		else if ( MoveSGLegs == false ) 
		{ 
			if ( RotateSGLegs < -45 )
				MoveSGLegs = true;
			else
				RotateSGLegs -= (20 * dt);
		}
	}

	if (securityStay > 10 ) 
	{
		SGPoint = ( SGPoint + 1 ) % 4 ; 
		securityStay = 0 ;

		if ( SGPoint == 0 )
		{
			SGTar = Vector3(-12,4,0) ;
			RotateSG = 90 ;
		}

		if ( SGPoint == 1 )
		{
			SGTar = Vector3(-18,4,35.5) ;
			RotateSG = 0;
		}

		if ( SGPoint == 2 )
		{
			SGTar = Vector3(12,4,43) ;
			RotateSG = 90 ;
		}

		if ( SGPoint == 3 ) 
		{
			SGTar = Vector3(6,4,13.3) ; 
			RotateSG = 0;
		}

		InitSGOnce = true;
	}

}