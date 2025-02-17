/******************************************************************************/
/*!
\file	SimpleInteractions.cpp
\author Job , Rui Peng , Jun Sen
\par	nyp
\brief
CPP to define functions of interactions in game 
*/
/******************************************************************************/

#include "SceneSP.h"

/******************************************************************************/
/*!
\par double dt (time)
\brief
for sliding of supermarket main door
*/
/******************************************************************************/
void SceneSP::SlidingDoor(double dt)
{
	if ((camera.position.x <= 9 && camera.position.x >= -7 && camera.position.z >= -16 && camera.position.z <= 2) || PBPos.x <= 9 && PBPos.x >= -7 && PBPos.z >= -16 && PBPos.z <= 2)
	{
		if (DoorSlide > -5)
		{
			DoorSlide -= (double)(3 * dt);
		}
	}

	else
	{
		if (DoorSlide < -0.78)
		{	
			DoorSlide += (double)(3 * dt);
		}

	}

}

/******************************************************************************/
/*!
\par double dt (time)
\brief
character jump
*/
/******************************************************************************/
void SceneSP::Jump (double dt)
{

	if (camera.position.y > 10 )
	{
		JumpDirection = false;
	}

	if (JumpDirection == true && JumpState == true)
	{

		if (AABBCheck(OBJ[0],OBJ[10]) == true || AABBCheck(OBJ[0],OBJ[31]) == true || AABBCheck(OBJ[0],OBJ[35]) == true)
		{
			JumpDirection = false;
		}
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

/******************************************************************************/
/*!
\par double dt (time) and int
\brief
update function for items to slide on the conveyor belt
*/
/******************************************************************************/
void SceneSP::updateItemSlide(double dt, int a )
{
	// to see which cashier table to render
	if ( a == 13 ) 
	{
		translateItemX = 0 ;
	}
	else if ( a == 14 )
	{
		translateItemX = 9 ; 
	}

	// so that it only runs once throughout the update and also to update checkoutlist 
	if ( Deletemah == true )
	{
		whichItem = InventoryData[0]; 

		for(int x = 0 ; x < CheckoutList.size() ; x++ )
		{
			if ( CheckoutList[x].getItemName() == whichItem.getItemName() )
			{
				CheckoutList[x].setItemCount( CheckoutList[x].getItemCount() + whichItem.getItemCount() ); 
				break;
			}
		}

		InventoryData[0].setItemCount(0) ;  
		Deletemah = false;
	}

	// to move everything up inventory if there is an item with 0 count 
	for ( int x = 0 ; x < 100 ; x++ )
	{
		for ( int y = 0 ; y < InventoryData.size() - 1 ; y++ )
		{
			if ( InventoryData[y].getItemCount() == 0 && InventoryData[y + 1].getItemCount() > 0 ) 
			{
				InventoryData[y] = InventoryData[y + 1] ; 
				InventoryData[y+1].setItemCount(0);
			}
		}
	}

	// translation and also a stop point 
	if ( translateItemZ < 5 ) 
		translateItemZ += (float)(10 * dt);
	else 
	{
		whichItem = nullthis; 
		translateItemZ = 0 ;
		translateItemX = 0 ;
		ItemSlide = false;
	}


}