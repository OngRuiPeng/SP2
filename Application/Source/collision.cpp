#include "SceneSP.h"
#include "Application.h"

bool SceneSP::AABBCheck(const Obj &box1,const Obj &box2)
{

	return (box1.max.x > box2.min.x && 
		box1.min.x < box2.max.x && 
		box1.max.y > box2.min.y && 
		box1.min.y < box2.max.y &&
		box1.max.z > box2.min.z && 
		box1.min.z < box2.max.z);


}

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

void SceneSP::updatecollision(double dt)
{
	float MOVE_SPEED = 20.0f;

	updateobj();

	if (Application::IsKeyPressed('W') && gamestate != MAINMENU && gamestate != CHOOSEMODE) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 precollide = view * dt * MOVE_SPEED; // if it moved it will be here 

		collisionprevent(OBJ,precollide,Interactables);
	}
	else if (Application::IsKeyPressed('S') && gamestate != MAINMENU && gamestate != CHOOSEMODE) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 backside = -view * dt * MOVE_SPEED;

		collisionprevent(OBJ,backside,Interactables);
	}
	else if (Application::IsKeyPressed('D') && gamestate != MAINMENU && gamestate != CHOOSEMODE) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 right = view.Cross(camera.up);
		right = right * dt * MOVE_SPEED;

		collisionprevent(OBJ,right,Interactables);
	}
	else if (Application::IsKeyPressed('A') && gamestate != MAINMENU && gamestate != CHOOSEMODE) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0 ;
		Vector3 left = view.Cross(camera.up);
		left = -left * dt * MOVE_SPEED;

		collisionprevent(OBJ,left,Interactables);
	}

	ItemTargetcollision();
	InteractableTargetcollision();

}

void SceneSP::updateobj()
{
	OBJ[0].max = camera.position + Vector3(1,1,1);
	OBJ[0].min = camera.position - Vector3(1,1,1);

	Interactables[0].set(Vector3(9.5 + DoorSlideR,20,-5.5),Vector3(1 + DoorSlideR,0,-7.5));
	Interactables[1].set(Vector3(1 - DoorSlideR ,20,-5.5),Vector3(-8 - DoorSlideR,0,-7.5));
}

Obj SceneSP::ItemTargetcollision()
{
	Vector3 targetline = camera.position;
	Vector3 view = (camera.targetwhere - camera.position).Normalized();
	view *= 0.5;
	Obj see ;

	for ( int z = 0 ; z < 20 ; z++) 
	{
		targetline += view;
		see.set(targetline + Vector3(0.2,0.2,0.2),targetline - Vector3(0.2,0.2,0.2));

		for ( int x = 0 ; x < Items.size() ; x++ )
		{
			if ( AABBCheck(see,Items[x]) == true )
			{
				collisionsia = true;
				return Items[x];
			}
			else
			{
				collisionsia = false;
			}
		}

	}

}

Obj SceneSP::InteractableTargetcollision()
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
				interactmah = true;
				return Interactables[x];
			}
			else
			{
				interactmah = false;
			}
		}

	}

}