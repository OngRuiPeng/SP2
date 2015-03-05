/******************************************************************************/
/*!
\file	UpdateNPC.cpp
\author Rui Peng , Job , Jun Sen
\par	nyp
\brief
CPP to define functions to update the AIs in the game 
*/
/******************************************************************************/

#include "SceneSP.h"
#include "Camera.h"
#include "Camera3.h"


bool PB2LForward = true;
bool PB2RForward = false;

bool CashROn = false;
bool ArmROn = false;

ISoundEngine* engine3 = createIrrKlangDevice(ESOD_AUTO_DETECT,ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
float WalkingSpeed = 25.f;
float limit = 35;

/******************************************************************************/
/*!
\par double dt (time)
\brief
updates npc's movement
*/
/******************************************************************************/
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

	if ( (AABBCheck(OBJ[0], Interactables[10])) == false)
	{
		Passerby2Dist += (2.5 * dt);
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
			PBStay = 9;
		}
		if ( PBPoint == 1 )
		{
			PBTar = Vector3(-4,4,-15);
			RotatePB = 90;
			PBStay = 9;
		}
		if ( PBPoint == 2 )
		{
			PBTar = Vector3(-6,4,27);
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
			PBStay = 9;
		}
		InitPBOnce = true;
	}
	UpdateCustomer(dt);
	Vector3 view = (camera.target - camera.position).Normalized();
	Vector3 right = view.Cross(camera.up);
	right.y = 0;
	right.Normalize();
	camera.up = right.Cross(view).Normalized();
	engine3->setListenerPosition(vec3df(camera.position.x,camera.position.y,camera.position.z),vec3df(view.x,view.y,view.z),vec3df(0,0,0),vec3df(-camera.up.x,-camera.up.y,-camera.up.z));
	//ISound* walkwalk = engine3->play3D("../irrKlang/media/walkm.mp3",vec3df(0,0,0),false);
}

/******************************************************************************/
/*!
\par double dt (time)
\brief
updates security guard's movement
*/
/******************************************************************************/
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
				RotateSGLegs += (40 * dt);
			}
		}
		else if ( MoveSGLegs == false ) 
		{ 
			if ( RotateSGLegs < -limit )
				MoveSGLegs = true;
			else
				RotateSGLegs -= (40 * dt);
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

/******************************************************************************/
/*!
\par double dt (time)
\brief
updates customer's movement
*/
/******************************************************************************/
void SceneSP::UpdateCustomer(double dt)
{
	Obj Customer(Vector3(CashMovX , 20, CashMovZ) + Vector3(1.5, 1, 1.5), Vector3(CashMovX, 0, CashMovZ) - Vector3(1.5, 1, 1.5));

	if (AABBCheck(OBJ[0],Customer) == false && AABBCheck(Customer,Interactables[9]) == false )
	{	
		CashTimer += dt;
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


		if (CycleOn == true && CashTimer > 0)
		{
			if (CashTimer > 10)
			{
				ArmTransUp = 0.2;
				ArmTransRight = -0.3;
				if (ArmRaise == true)
				{
					if (CashRotArm < 50)
					{
						CashRotArm += (20 * dt);
					}
					if (CashRotArm > 45)
					{
						ArmRaise = false;
					}
				}
				else
				{
					if (CashRotArm > 0)
					{
						CashRotArm -= (20 * dt);
					}
					if (CashRotArm < 0)
					{
						CashRotArm = 0;
					}
				}
			}				

			if (CashTimer > 20 && CashTimer < 50)
			{
				ArmTransUp = 0;
				ArmTransRight = 0;
			}

			if (CashTimer > 20 && CashTimer < 25)
			{
				RotBody = 0;
			}

			if (CashTimer > 25 && CashTimer < 30)
			{
				CashWalk = true;
				CashMovZ -= (4 * dt);
				if (CashMovZ < 15)
				{
					CashMovZ = 15;
					CashWalk = false;
					RotBody = 90;	
					CashWalk = true;
					CashMovX -= (4 * dt);
					if (CashMovX < -3.5)
					{
						CashMovX = -3.5;
						CashWalk = false;
						RotBody = 180;		
					}
				}
			}

			if (CashTimer > 31)
			{
				CashMovZ += (4 * dt);
				CashWalk = true;
				if (CashMovZ > 25)
				{
					CashMovZ = 25;
					CashWalk = false;
					RotBody = 270;
					if (CashTimer > 35)
					{
						CycleOn = false;
						CashTimer = 0;
					}
				}
			}
		}

		if (CycleOn == false && CashTimer > 0)
		{
			if (CashTimer > 5 && CashTimer < 15)
			{
				RotBody = 90;
				CashWalk = true;
				CashMovX -= (4 * dt);
				if (CashMovX < -7)
				{
					CashMovX = -7;
					CashWalk = false;

				}
			}

			if (CashTimer > 15 && CashTimer < 20)
			{
				RotBody = 0;
				CashWalk = true;
				CashMovZ -= (4 * dt);
				if (CashMovZ < 15)
				{
					CashMovZ = 15;
					CashWalk = false;
					RotBody = 270;
				}
			}
			if (CashTimer > 20 && CashTimer < 35)
			{
				CashWalk = true;
				CashMovX += (4 * dt);
				if (CashMovX > 10)
				{
					CashMovX = 10;
					CashWalk = false;
					RotBody = 180;
					CashWalk = true;
					CashMovZ += (4 * dt);
					if (CashMovZ > 25)
					{
						CashMovZ = 25;
						CashWalk = false;
						RotBody = 270;
					}
				}
			}

			if (CashTimer > 35)
			{
				RotBody = 90;
				CashWalk = true;
				CashMovX -= (4 * dt);
				if (CashMovX < 6)
				{
					CashMovX = 6;
					CashWalk = false;
					CycleOn = true;
					CashTimer = 0;
				}
			}
		}	//False cycle
	}//BB Check
}
