/******************************************************************************/
/*!
\file	Inventory.cpp
\author Jun Yan
\par	nyp
\brief
CPP to update inventory when you checkout,pick up and put back item
*/
/******************************************************************************/

#include "SceneSP.h"

void SceneSP::updateInventory( CItem a , bool b )
{
	// to add item

	if ( b == true ) 
	{
		for(int x = 0 ; x < InventoryData.size() ; x++ )
		{
			if ( InventoryData[x].getItemName() != "" )
			{
				if ( InventoryData[x].getItemName() == a.getItemName() )
				{
					InventoryData[x].setItemCount( InventoryData[x].getItemCount() + 1 ); 
					break;
				}
				else if ( x + 1 == InventoryData.size() )
				{
					if ( InventoryData[x].getItemCount() == 0 ) 
					{
						InventoryData[x] = a; 
						InventoryData[x].setItemCount(1);
					}
					else
					{
						InventoryData.push_back(a);
						InventoryData[x + 1].setItemCount(0);
					}
				}
			}
		}
	}

	// to reduce count of the item
	else if ( b == false)
	{
		for(int x = 0 ; x < InventoryData.size() ; x++ )
		{
			if ( InventoryData[x].getItemName() == a.getItemName() )
			{
				InventoryData[x].setItemCount( InventoryData[x].getItemCount() - 1 ); 
				break;
			}
		}
	}

	// to move everything up if there is an item with 0 count 
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

}