/******************************************************************************/
/*!
\file	RenderInventory.cpp
\author Jun Yan , Jun Sen
\par	nyp
\brief
CPP to render inventory and also to update checklist 
*/
/******************************************************************************/

#include "SceneSP.h"
#include "Utility.h"

/******************************************************************************/
/*!
\brief
renders inventory 
*/
/******************************************************************************/
void SceneSP::RenderInventory()
{
	GLfloat alpha = 0;
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);

	RenderTextOnScreen(meshList[GEO_MainMenuText],"+",Color(1,0,0),5,8,6);

	/*modelStack.PushMatrix();
	for(alpha = 0.0; alpha < 1.0; alpha += 0.05)
	{

	RenderTextOnScreen(meshList[GEO_MainMenuText],
	"You have just picked up an item!",Color(0.f,1.f,0.f),
	2.2f,3.f,3.f);
	}
	modelStack.PopMatrix();*/

	float base = 14;
	float width = 3.5;

	modelStack.PushMatrix();
	RenderPictureOnScreen(meshList[GEO_INVENTORY],47.5,5.5,0.872,0.5);
	modelStack.PopMatrix();

	

	for ( int x = 0 ; x < InventoryData.size() ; x++ )
	{
		if ( InventoryData[x].getItemCount() > 0 ) 
		{
			if ( InventoryData[x].getItemName() == "Reditos" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_REDITOS],7, 4.5, 2.875 + x * 0.75 , 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();

			}
			else if ( InventoryData[x].getItemName() == "Campbella" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_CAMPBELLA],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
			else if ( InventoryData[x].getItemName() == "Toblerone" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_TOBLERONE],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
			else if ( InventoryData[x].getItemName() == "Dewtos" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_DEWTOS],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
			else if ( InventoryData[x].getItemName() == "Pizza" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_PIZZA],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
			else if ( InventoryData[x].getItemName() == "Cactus juice" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_CACTUS],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
			else if ( InventoryData[x].getItemName() == "Chicken soup" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_CHICKEN],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
			else if ( InventoryData[x].getItemName() == "Maggie Noodles" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_MAGGI],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
			else if ( InventoryData[x].getItemName() == "Macaroni" )
			{
				modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_MACARONI],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
			}
            else if( InventoryData[x].getItemName() == "Doritos" )
            {
                modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_DORITOSPIC],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
            }
            else if(InventoryData[x].getItemName() == "Mountain Dew")
            {
                modelStack.PushMatrix();
				RenderPictureOnScreen(meshList[GEO_MTNPIC],7, 4.5, 2.875 + x * 0.75, 0.65);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(InventoryData[x].getItemCount()), (1,0,0) , 1.5 , base + x * width , 0.65);
				modelStack.PopMatrix();
            }
		}
	}
}

/******************************************************************************/
/*!
\brief
updates checklist when checking stuffs out at the cashier
*/
/******************************************************************************/
void SceneSP::updateCheckList()
{
	for ( int y = 0 ; y < 9 ; y++ )
	{
		for ( int x = 0 ; x < CheckoutList.size() ; x++ )
		{
			if ( CheckoutList[x].getItemName() == CheckList[y].getItemName() ) 
			{
				if ( CheckoutList[x].getItemCount() >= CheckList[y].getItemCount()) 
					CheckCheckOut[y] = true ; 
				else
					CheckCheckOut[y] = false ; 
				break; 
			}
		}
	}
	for ( int x = 0; x < InventoryData.size(); ++x )
	{
		if ( InventoryData[x].getItemCount() > 0 )
		{
			ItemsInInventory = true;
			break;
		}
		else
		{
			ItemsInInventory = false;
		}
	}
	
	int counter = 0;
	for ( int y = 0; y < 9; y++ )
	{
		if ( CheckCheckOut[y] == true )
		{
			++counter;
		}
		if ( counter == 9 )
		{
			CheckListDone = true;
		}
	}
}