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

void SceneSP::collisionprevent(Obj &boxA, Vector3 camerathing) 
{
	Vector3 player = camerathing + camera.position;
	box2.max = player + Vector3(1,1,1);
	box2.min = player - Vector3(1,0,1);

	if ( AABBCheck(boxA,box2) == true ) 
	{
		box2.max = camerathing + Vector3(1,1,1);
		box2.min = camerathing - Vector3(1,0,1);
		if ( AABBCheck(boxA , box2) == true ) 
		{
			Obj forX , forY, forZ ; 

			forX.max.x = camerathing.x + 1;
			forX.min.x = camerathing.x - 1;

			forY.max.y = camerathing.y + 1;
			forY.min.y = camerathing.y ;

			forZ.max.z = camerathing.z + 1;
			forZ.min.z = camerathing.z - 1;

			//if x axis is the one touching
			if ( AABBCheck ( boxA, forX) == true ) 
				camerathing.x = 0 ;
			//if y axis is the one touching
			if ( AABBCheck ( boxA, forY) == true ) 
				camerathing.y = 0 ;
			//if z axis is the one touching
			if ( AABBCheck ( boxA, forZ) == true ) 
				camerathing.z = 0 ;

			camera.position.x -= camerathing.x ;
			camera.position.z -= camerathing.z;
			camera.target.x -= camerathing.x;
			camera.target.z -= camerathing.z;
		}

	}

}

void SceneSP::updatecollision(double dt)
{
	float MOVE_SPEED = 20.0f;

	updateobj();

	if ( AABBCheck(box1,box2) == true  && Application::IsKeyPressed('W')) 
	{
		collision = true ; 

		Vector3 view = (camera.target - camera.position).Normalize();
		Vector3 precollide = view * dt * MOVE_SPEED;

		collisionprevent(box1,precollide);

		cout << collision << "got collision" << dt << endl ;
	}
	else if ( AABBCheck(box1,box2) == true  && Application::IsKeyPressed('S')) 
	{
		collision = true ; 

		Vector3 view = (camera.target - camera.position).Normalize();
		Vector3 backside = -view * dt * MOVE_SPEED;

		collisionprevent(box1,backside);

		cout << collision << "got collision" << dt << endl ;
	}
	else if ( AABBCheck(box1,box2) == true  && Application::IsKeyPressed('D')) 
	{
		collision = true ; 

		Vector3 view = (camera.target - camera.position).Normalize();
		Vector3 right = view.Cross(camera.up);
		right *= dt * MOVE_SPEED;

		collisionprevent(box1,right);

		cout << collision << "got collision" << dt << endl ;
	}
	else if ( AABBCheck(box1,box2) == true  && Application::IsKeyPressed('A')) 
	{
		collision = true ; 

		Vector3 view = (camera.target - camera.position).Normalize();
		Vector3 left = -view.Cross(camera.up);
		left *= dt * MOVE_SPEED;

		collisionprevent(box1,left);

		cout << collision << "got collision" << dt << endl ;
	}
	else if ( AABBCheck(box1,box2) == true ) 
	{
		collision = true ; 
	}
	else
	{
		collision = false;

	/*	if ( translateX < 50 ) 
			translateX += (float)(8 * dt) ; 
		else 
			translateX = 0 */;

		cout << collision << " no collision" << dt << endl ;

	}

}

void SceneSP::updateobj()
{
	box1.max = Vector3(translateX + 10,10,10);
	box1.min = Vector3(translateX + -10,0,-10);

	box2.max = camera.position + Vector3(1,1,1);
	box2.min = camera.position - Vector3(1,0,1);


}