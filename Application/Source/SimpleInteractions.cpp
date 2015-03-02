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
			if ( CheckoutList[x].getItemName() != "" )
			{
				if ( CheckoutList[x].getItemName() == whichItem.getItemName() )
				{
					CheckoutList[x].setItemCount( CheckoutList[x].getItemCount() + whichItem.getItemCount() ); 
					break;
				}
				else if ( x + 1 == CheckoutList.size() )
				{
					if ( CheckoutList[x].getItemCount() == 0 ) 
					{
						CheckoutList[x] = whichItem; 
						CheckoutList[x].setItemCount(whichItem.getItemCount());
					}
					else
					{
						CheckoutList.push_back(whichItem);
						CheckoutList[x + 1].setItemCount(0);
					}
				}
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
	}
	else
	{
		if ( AABBCheck(OBJ[0],SG) == false )
			SGPos += SGMov * dt  ; 
	}

	if (securityStay > 10 ) 
	{
		whichPoint = ( whichPoint + 1 ) % 3 ; 
		securityStay = 0 ;

		if ( whichPoint == 0 )
		{
			SGTar = Vector3(-12,4,0) ;
			InitSGOnce = true;
		}

		if ( whichPoint == 1 )
		{
			SGTar = Vector3(-16,4,34.5) ;
			InitSGOnce = true;
		}

		if ( whichPoint == 2 )
		{
			SGTar = Vector3(12,4,43) ;
			InitSGOnce = true;
		}
	}
}