#include "SceneSP.h"

bool PB2LForward = true;
bool PB2RForward = false;

bool CashROn = false;

float WalkingSpeed = 10.f;
float limit = 35;
void SceneSP::UpdateNPC(double dt)
{
	//Passerby2
	if ( PB2LForward == true )
	{
		Passerby2Left += (WalkingSpeed * dt);
		if ( Passerby2Left > limit )
		{
			PB2LForward = false;
		}
	}
	else
	{
		Passerby2Left -= (WalkingSpeed * dt);
		if ( Passerby2Left < -limit )
		{
			PB2LForward = true;
		}
	}
	if ( PB2RForward == true )
	{
		Passerby2Right += (WalkingSpeed * dt);
		if ( Passerby2Right > limit )
		{
			PB2RForward = false;
		}
	}
	else
	{
		Passerby2Right -= (WalkingSpeed * dt);
		if ( Passerby2Right < -limit )
		{
			PB2RForward = true;
		}
	}
	if ( (AABBCheck(OBJ[0], Interactables[10])) == false)
	{
		Passerby2Dist += (5 * dt);
		if ( Passerby2Dist > 100 )
		{
			Passerby2Dist = 0;

		}
	}

	//Passerby1
	Obj PB(PBPos + Vector3(1,20,1),PBPos - Vector3(1,4,1)); 
	Obj TarPB(PBTar + Vector3(1,20,1), PBTar - Vector3(1,4,1));

	if ( InitPBOnce == true )
	{
		PBMov = PBTar - PBPos ; 
		PBMov *= 0.1;
		InitPBOnce = false;
	}

	if (AABBCheck(PB,TarPB)) 
	{
		PBStay += dt;
		if ( PBPoint == 2 )
		{
			RotatePB = 90;
		}
		MovePBLegsOrNot = false;
		RotatePBLegs = 0;
		RotatePBHands = 0;
	}
	else
	{
		if ( AABBCheck(OBJ[0],PB) == false )
			PBPos += PBMov * dt  ; 
		MovePBLegsOrNot = true; 
	}

	if ( MovePBLegsOrNot == true ) 
	{
		if ( MovePBLegs == true )
		{
			if ( RotatePBLegs > limit )
				MovePBLegs = false;
			else
			{
				RotatePBHands -= (20 * dt);
				RotatePBLegs += (20 * dt);
			}
		}
		else if ( MovePBLegs == false ) 
		{ 
			if ( RotatePBLegs < -limit )
				MovePBLegs = true;
			else
				RotatePBLegs -= (20 * dt);
				RotatePBHands += (20 * dt);
		}
	}

	if (PBStay > 10 ) 
	{
		PBPoint = ( PBPoint + 1 ) % 5 ; 
		PBStay = 0 ;

		if ( PBPoint == 0 )
		{
			PBPos = Vector3(-55,4,-15);
			PBTar = Vector3(-55, 4, -15);
			RotatePB = 90;
		}
		if ( PBPoint == 1 )
		{
			PBTar = Vector3(-4,4,-15);
			RotatePB = 90;
			PBStay = 9;
		}
		if ( PBPoint == 2 )
		{
			PBTar = Vector3(-5,4,27);
			RotatePB = 0;
		}
		if ( PBPoint == 3 )
		{
			PBTar = Vector3(-5,4,-16);
			RotatePB = 0;
			PBStay = 9;
		}
		if ( PBPoint == 4 )
		{
			PBTar = Vector3(55,4,-15);
			RotatePB = 90;	
		}
		InitPBOnce = true;
	}
	UpdateCustomer(dt);
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
			if ( RotateSGLegs > limit )
				MoveSGLegs = false;
			else
			{
				RotateSGLegs += (20 * dt);
			}
		}
		else if ( MoveSGLegs == false ) 
		{ 
			if ( RotateSGLegs < -limit )
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

void SceneSP::UpdateCustomer(double dt)
{
	CashTimer += dt;
	cout << CashTimer << endl;
	if (CashWalk == true)					//Legs anim
	{
		if ( CashROn == true )
		{
			CashRight += (WalkingSpeed * dt);
			if ( CashRight > limit )
			{
				CashROn = false;
			}
		}
		else
		{
			CashRight -= (WalkingSpeed * dt);
			if ( CashRight < -limit )
			{
				CashROn = true;
			}
		}
	}
	else									//Legs off
	{
		CashRight = 0;
	}

	if (CashTimer > 20)
	{
		//ArmTransRight = 4;
		if (ArmRaise == true)
		{
			CashRotArm += (5 * dt);
			if (CashRotArm > 60)
			{
				ArmRaise == false;
			}
		}
		else
		{
			CashRotArm = 0;
		}
	}
}