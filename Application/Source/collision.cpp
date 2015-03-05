/******************************************************************************/
/*!
\file	collision.cpp
\author Job , Rui Peng , Jun Sen 
\par	nyp
\brief
CPP to define collision functions , including collision detection + response 
*/
/******************************************************************************/

#include "SceneSP.h"
#include "Application.h"
ISoundEngine* walk = createIrrKlangDevice(ESOD_AUTO_DETECT,ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
ISound* sound = walk->play2D("../irrKlang/media/walkm2.mp3", true,true);

/******************************************************************************/
/*!
\par const OBJs
\brief
return true if collision occurs
*/
/******************************************************************************/
bool SceneSP::AABBCheck(const Obj &box1,const Obj &box2)
{

	return (box1.max.x > box2.min.x && 
		box1.min.x < box2.max.x && 
		box1.max.y > box2.min.y && 
		box1.min.y < box2.max.y &&
		box1.max.z > box2.min.z && 
		box1.min.z < box2.max.z);


}

/******************************************************************************/
/*!
\par OBJ vector , a vector3 and another OBJ vector
\brief
this is called when you move and prevent collision by sliding 
*/
/******************************************************************************/
void SceneSP::collisionprevent(vector<Obj> a, Vector3 camerathing , vector<Obj> b ) 
{
	bool moveX = true ;

	Vector3 player = camerathing + camera.position; 

	Obj checkColli , forX , forZ;

	checkColli.max = player ;
	checkColli.min = player ;

	forX.max = Vector3(player.x , camera.position.y , camera.position.z ) ;
	forX.min = Vector3(player.x , camera.position.y , camera.position.z ) ;

	forZ.max = Vector3(camera.position.x , camera.position.y , player.z );
	forZ.min = Vector3(camera.position.x , camera.position.y , player.z );

	for(int x = 1 ; x < a.size() ; ++x)
	{
		if ( AABBCheck(OBJ[x],checkColli)) 
		{
			//if x axis is the one touching
			if ( AABBCheck ( OBJ[x], forX)) 
			{
				camerathing.x = 0 ;
				moveX = false;
			}

			//if z axis is the one touching
			if ( AABBCheck ( OBJ[x], forZ)) 
			{
				camerathing.z = 0 ;
				moveX = true;
			}
		}
	}

	for(int x = 0 ; x < b.size() ; ++x)
	{
		if ( AABBCheck(Interactables[x],checkColli)) 
		{
			//if x axis is the one touching
			if ( AABBCheck ( Interactables[x], forX)) 
			{
				camerathing.x = 0 ;
				moveX = false;
			}

			//if z axis is the one touching
			if ( AABBCheck ( Interactables[x], forZ)) 
			{
				camerathing.z = 0 ;
				moveX = true;
			}
		}
	}

	camera.position.x += camerathing.x ;
	camera.position.z += camerathing.z ;
	camera.target.x += camerathing.x ;
	camera.target.z += camerathing.z ;
	camera.targetwhere.x += camerathing.x ;
	camera.targetwhere.z += camerathing.z ;

}

/******************************************************************************/
/*!
\par dt 
\brief
updates collision 
*/
/******************************************************************************/
void SceneSP::updatecollision(double dt)
{
	float MOVE_SPEED = 20.0f;

	updateobj();

	if (Application::IsKeyPressed('W') && gamestate != MAINMENU && gamestate != CHOOSEMODE && gamestate != GAMEWINCHECKOUT && gamestate != GAMEWINTHIEF && gamestate != GAMEBUSTED && SecurityCam == false) 
	{

		walk->setAllSoundsPaused(false);



		if(sound)
		{
			//walk->setDefault3DSoundMaxDistance(1000000000.f);
			sound->setMinDistance(0.f);
		}


		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 precollide = view * dt * MOVE_SPEED; // if it moved it will be here 

		collisionprevent(OBJ,precollide,Interactables);
	}
	else if (Application::IsKeyPressed('S') && gamestate != MAINMENU && gamestate != CHOOSEMODE && gamestate != GAMEWINCHECKOUT && gamestate != GAMEWINTHIEF && gamestate != GAMEBUSTED && SecurityCam == false) 
	{
		walk->setAllSoundsPaused(false);
		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 backside = -view * dt * MOVE_SPEED;

		collisionprevent(OBJ,backside,Interactables);
	}
	else if (Application::IsKeyPressed('D') && gamestate != MAINMENU && gamestate != CHOOSEMODE && gamestate != GAMEWINCHECKOUT && gamestate != GAMEWINTHIEF && gamestate != GAMEBUSTED && SecurityCam == false) 
	{
		walk->setAllSoundsPaused(false);
		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 right = view.Cross(camera.up);
		right = right * dt * MOVE_SPEED;

		collisionprevent(OBJ,right,Interactables);
	}
	else if (Application::IsKeyPressed('A') && gamestate != MAINMENU && gamestate != CHOOSEMODE && gamestate != GAMEWINCHECKOUT && gamestate != GAMEWINTHIEF && gamestate != GAMEBUSTED && SecurityCam == false) 
	{
		walk->setAllSoundsPaused(false);
		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0 ;
		Vector3 left = view.Cross(camera.up);
		left = -left * dt * MOVE_SPEED;

		collisionprevent(OBJ,left,Interactables);
	}
	else
	{
		walk->setAllSoundsPaused(true);
	}
	NoItemTargetcollision();
	InteractableTargetcollision();

}

/******************************************************************************/
/*!
\brief
Updates the bounding box of moving OBJs
*/
/******************************************************************************/
void SceneSP::updateobj()
{
	OBJ[0].max = camera.position + Vector3(1,1,1);
	OBJ[0].min = camera.position - Vector3(1,1,1);

	Interactables[0].set(Vector3(10 - DoorSlide * 2 + 0.75 ,20,-5.5),Vector3(0.5 - DoorSlide * 2 + 0.75,0,-7.5)); //front door
	Interactables[1].set(Vector3(1 + DoorSlide * 2 + 0.75 ,20,-5.5),Vector3(-8 + DoorSlide * 2 + 0.75 ,0,-7.5)); //front door
	Interactables[9].set(PBPos + Vector3(1,20,1),PBPos - Vector3(1,4,1)); //Passerby1
	Interactables[10].set(Vector3(47.5 - Passerby2Dist,20,-28.5),Vector3(43.5 - Passerby2Dist,0,-31.5)); // Passerby2

	if ( toiletDoor == false )
	{
		Interactables[11].set(Vector3(23,20,38.5),Vector3(17.8,0,36.8));
	}
	if ( toiletDoor == true )
	{
		Interactables[11].set(Vector3(18.6,20,41.3),Vector3(17,0,37.7));
	}
	if ( securityDoor == false )
	{
		Interactables[12].set(Vector3(-10.7,20,39.0),Vector3(-16.0,0,36.8));
	}
	if ( securityDoor == true )
	{
		Interactables[12].set(Vector3(-10.5,20,42.7),Vector3(-12.5,0,37.2));
	}

	// thief mode
	if (AABBCheck(OBJ[0],NpcBB[0]) && gamestate == GAMETHIEF) // Security guard's range
		Caught = true;
	else
		Caught = false;

	NpcBB[0].set(SGPos + Vector3(8,20,8),SGPos - Vector3(8,4,8));
	Interactables[7].set(SGPos + Vector3(1.5,20,1.5),SGPos - Vector3(1.5,4,1.5));

	Interactables[8].set(Vector3(CashMovX , 20, CashMovZ) + Vector3(1.5, 1, 1.5), Vector3(CashMovX, 0, CashMovZ) - Vector3(1.5, 1, 1.5)); 


}

/******************************************************************************/
/*!
\par void
\brief
returns the item that the target has collided with
*/
/******************************************************************************/
Obj SceneSP::ItemTargetcollision() // returns the item that the target has collided with ( Obj format)
{
	Vector3 targetline = camera.position;
	Vector3 view = (camera.targetwhere - camera.position).Normalized();
	view *= 0.5;
	Obj see ;
	if(gamestate != GAMEFUN)
	{
		for ( int z = 0 ; z < 20 ; z++) 
		{
			targetline += view;
			see.set(targetline + Vector3(0.2,0.2,0.2),targetline - Vector3(0.2,0.2,0.2));

			for ( int x = 0 ; x < Items.size() ; x++ )
			{
				if ( AABBCheck(see,Items[x]) == true )
				{
					PickUpItem = true;
					return Items[x];
				}
				else
				{
					PickUpItem = false;
				}
			}

		}
	}
	if(gamestate == GAMEFUN)
	{
		for ( int z = 0 ; z < 20 ; z++) 
		{
			targetline += view;
			see.set(targetline + Vector3(0.2,0.2,0.2),targetline - Vector3(0.2,0.2,0.2));

			for ( int x = 0 ; x < Fun.size() ; x++ )
			{
				if ( AABBCheck(see,Fun[x]) == true )
				{
					PickUpItem = true;
					return Fun[x];
				}
				else
				{
					PickUpItem = false;
				}
			}

		}
	}
}

/******************************************************************************/
/*!
\par void
\brief
returns the number of the item that the target has collided with 
*/
/******************************************************************************/
int SceneSP::NoItemTargetcollision() // returns the item that the target has collided with ( Obj format)
{
	Vector3 targetline = camera.position;
	Vector3 view = (camera.targetwhere - camera.position).Normalized();
	view *= 0.5;
	Obj see ;
	if(gamestate != GAMEFUN)
	{
		for ( int z = 0 ; z < 20 ; z++) 
		{
			targetline += view;
			see.set(targetline + Vector3(0.2,0.2,0.2),targetline - Vector3(0.2,0.2,0.2));

			for ( int x = 0 ; x < Items.size() ; x++ )
			{
				if ( AABBCheck(see,Items[x]) == true )
				{
					if ( Items[x].getEmpty() == false )
						PickUpItem = true;
					else
					{
						for ( int y = 0 ; y < ItemData.size() ; y++ ) 
						{
							for ( int p = 0 ; p < InventoryData.size() ; p++ )
							{
								if ( InventoryData[p].getItemName() == ItemData[y].getItemName() && ItemData[Items[x].getNo()].getItemName() == InventoryData[p].getItemName() && InventoryData[p].getItemCount() > 0)
									PlaceItem = true ; 
							}
						}
					}
					return x ;
				}
				else
				{
					PickUpItem = false;
					PlaceItem = false;
				}
			}

		}
	}
	if(gamestate == GAMEFUN)
	{
		for ( int z = 0 ; z < 20 ; z++) 
		{
			targetline += view;
			see.set(targetline + Vector3(0.2,0.2,0.2),targetline - Vector3(0.2,0.2,0.2));

			for ( int x = 0 ; x < Fun.size() ; x++ )
			{
				if ( AABBCheck(see,Fun[x]) == true )
				{
					if ( Fun[x].getEmpty() == false )
						PickUpItem = true;
					else
					{
						for ( int y = 0 ; y < ItemData.size() ; y++ ) 
						{
							for ( int p = 0 ; p < InventoryData.size() ; p++ )
							{
								if ( InventoryData[p].getItemName() == ItemData[y].getItemName() && ItemData[Fun[x].getNo()].getItemName() == InventoryData[p].getItemName() && InventoryData[p].getItemCount() > 0)
									PlaceItem = true ; 
							}
						}
					}
					return x ;
				}
				else
				{
					PickUpItem = false;
					PlaceItem = false;
				}
			}

		}
	}
	return 0 ;
}

/******************************************************************************/
/*!
\par void
\brief
returns the interactable that target has collided with 
*/
/******************************************************************************/
Obj SceneSP::InteractableTargetcollision() // returns the Interactable that the target has collided with ( Obj format)
{
	Vector3 targetline = camera.position;
	Vector3 view = (camera.targetwhere - camera.position).Normalized();
	view *= 0.5;
	Obj see ;

	for ( int z = 0 ; z < 20 ; z++) 
	{
		targetline += view;
		see.set(targetline + Vector3(0.2,0.2,0.2),targetline - Vector3(0.2,0.2,0.2));

		for ( int x = 2 ; x < Interactables.size() ; x++ )
		{
			if ( AABBCheck(see,Interactables[x]) == true )
			{
				Interact = true;
				return Interactables[x];
			}
			else
			{
				Interact = false;
			}
		}

	}

}

/******************************************************************************/
/*!
\par void
\brief
returns the number of the interactable that target has collided with 
*/
/******************************************************************************/
int SceneSP::NoInteractableTargetcollision() // returns the Interactable that the target has collided with ( Obj format)
{
	Vector3 targetline = camera.position;
	Vector3 view = (camera.targetwhere - camera.position).Normalized();
	view *= 0.5;
	Obj see ;

	for ( int z = 0 ; z < 20 ; z++) 
	{
		targetline += view;
		see.set(targetline + Vector3(0.2,0.2,0.2),targetline - Vector3(0.2,0.2,0.2));

		for ( int x = 2 ; x < Interactables.size() ; x++ )
		{
			if ( AABBCheck(see,Interactables[x]) == true )
			{
				Interact = true;
				return x;
			}
			else
			{
				Interact = false;
			}
		}

	}

	return 0 ;
}
