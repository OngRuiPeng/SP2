#include "SceneSP.h"
#include "Application.h"
//ISoundEngine* engine4 = createIrrKlangDevice(ESOD_AUTO_DETECT,ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
void SceneSP::RenderFunSMarket()
{

	modelStack.PushMatrix();		//LEFT DOOR
	modelStack.Translate(18.1, 0, 37.8);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 2.75, 3.0);
	modelStack.PushMatrix();
	modelStack.Rotate(toiletDoorMove, 0, 1, 0);
	modelStack.Translate(0, 0, 0.6);
	RenderMesh(meshList[GEO_BACKDOOR], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();	   //RIGHT DOOR
	modelStack.Translate(-11.9, 0, 37.8);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 2.75, 3.9);
	modelStack.PushMatrix();
	modelStack.Rotate(securityDoorMove, 0, 1, 0);
	modelStack.Translate(0, 0, -0.55);
	RenderMesh(meshList[GEO_BACKDOOR], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	//All push
	modelStack.PushMatrix();					
	modelStack.Translate(0, -0.1, 0);
	modelStack.Scale(1.1, 1.1, 1.1);
	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 19);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3.5, 2.5, 3.5);
	RenderMesh(meshList[GEO_SUPERMARKET], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2, -1, 19);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3.5, 2.5, 3.5);
	RenderMesh(meshList[GEO_SUPERMARKETFLOOR], true);
	modelStack.PopMatrix();

	//SCANNERS push
	modelStack.PushMatrix();				

	modelStack.PushMatrix();
	modelStack.Translate(5, 0, -2.5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SCANNER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-3, 0, -2.5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SCANNER], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	//SCANNERS pop

	//DIVIDERS
	modelStack.PushMatrix();
	modelStack.Translate(8.9, 0, -2);
	modelStack.Scale(1, 1, 0.7);
	RenderMesh(meshList[GEO_DIVIDER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-7, 0, -0.7);
	RenderMesh(meshList[GEO_DIVIDER], true);
	modelStack.PopMatrix();
	//!DIVIDERS


	//SHELVES
	int transShelfFwd = 15;
	for (int a = 0; a < 3; a++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(transShelfFwd, 0, 25);
		RenderMesh(meshList[GEO_SHELF], true);
		transShelfFwd -= 12;
		modelStack.PopMatrix();
	}

	float transShelfBac = 11.7;
	for (int b = 0; b < 3; b++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(transShelfBac, 0, 25);
		modelStack.Rotate(180, 0, 1, 0);		
		RenderMesh(meshList[GEO_SHELF], true);
		transShelfBac -= 12;
		modelStack.PopMatrix();		
	}
	//!SHELVES

	float transDisplay = 13.5;
	for (int c = 0; c < 3; c++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(transDisplay, -0.3, 19);
		RenderMesh(meshList[GEO_DISPLAYCABINET], true);
		transDisplay -= 12;
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();				//Light/dark brown shelf
	modelStack.Translate(-21, 0.2, 13);	
	RenderMesh(meshList[GEO_SHELF2], true);
	modelStack.PopMatrix();	

	modelStack.PushMatrix();
	modelStack.Translate(-21, 0.2, 3);
	RenderMesh(meshList[GEO_SHELF2], true);
	modelStack.PopMatrix();	

	modelStack.PushMatrix();				//Red shelf
	modelStack.Translate(0, 0, 40.9);
	RenderMesh(meshList[GEO_SHELF3], true);
	modelStack.PopMatrix();	

	modelStack.PushMatrix(); //CASHIER SET PUSH

	modelStack.PushMatrix();
	modelStack.Translate(21.5, 0, 7);
	modelStack.Scale(0.7, 1, 0.7);
	RenderMesh(meshList[GEO_CASHIERTABLE], true);
	modelStack.PopMatrix();	

	modelStack.PushMatrix();
	modelStack.Translate(23, 3.8, 4.8);
	modelStack.Scale(0.7, 1, 0.7);
	RenderMesh(meshList[GEO_REGISTER], true);
	modelStack.PopMatrix();	

	modelStack.PopMatrix();	//CASHIER SET POP

	modelStack.PushMatrix(); //CASHIER SET2 PUSH

	modelStack.PushMatrix();
	modelStack.Translate(13, 0, 7);
	modelStack.Scale(0.7, 1, 0.7);
	RenderMesh(meshList[GEO_CASHIERTABLE], true);
	modelStack.PopMatrix();	

	modelStack.PushMatrix();
	modelStack.Translate(14.5, 3.8, 4.8);
	modelStack.Scale(0.7, 1, 0.7);
	RenderMesh(meshList[GEO_REGISTER], true);
	modelStack.PopMatrix();	

	modelStack.PopMatrix();	//CASHIER SET2 POP

	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 19);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3.5, 2.5, 3.5);
	RenderMesh(meshList[GEO_CONTROLPANEL], true);
	modelStack.PopMatrix();	

	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 19);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3.5, 2.5, 3.5);
	RenderMesh(meshList[GEO_SINK], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2, 0, 19);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3.5, 2.5, 3.5);
	RenderMesh(meshList[GEO_TOILET], true);
	modelStack.PopMatrix();	

	RenderTapWater();

	modelStack.PushMatrix();
	modelStack.Translate(2, flushUp, 19);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3.5, 2.5, 3.5);
	RenderMesh(meshList[GEO_BIGWATER], true);
	modelStack.PopMatrix();	

	RenderFlush();

	RenderFunPic();

	RenderFunStuff();

	if ( whichItem.getItemName() == "Doritos" )
	{
		modelStack.PushMatrix();
		modelStack.Translate(12 + translateItemX , 4 , 12 - translateItemZ) ;
		RenderMesh(meshList[GEO_DORITOS], true);
		modelStack.PopMatrix();
	}
	else if ( whichItem.getItemName() == "Mountain Dew" )
	{
		modelStack.PushMatrix();
		modelStack.Translate(12 + translateItemX , 4 , 12 - translateItemZ) ;
		RenderMesh(meshList[GEO_MTN], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Scale(3.5, 2.5, 3.2);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(1.9, 0, -DoorSlide + 0.68);
	RenderMesh(meshList[GEO_DOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(3.5, 2.5, 3.2);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(1.9, 0, DoorSlide);
	RenderMesh(meshList[GEO_DOOR], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	//All pop


}
void SceneSP::RenderFunPic()
{
	modelStack.PushMatrix();
	modelStack.Translate(15,5,-6.75);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(4,4,4);
	RenderMesh(meshList[GEO_SNOOPDOG],false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-15,5,-6.75);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(4,4,4);
	RenderMesh(meshList[GEO_WEED],false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-13.9, 6, 42.75);
	modelStack.Rotate(-90,1,0,0);
	//modelStack.Rotate(-90,0,0,1);
	RenderMesh(meshList[GEO_ILLUMINATI],false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(24,10,20);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Rotate(-90,0,0,1);
	modelStack.Scale(5,5,5);
	RenderMesh(meshList[GEO_WEEDP],false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(26.69,2,25);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Rotate(-90,0,0,1);
	modelStack.Scale(1,1,1);
	RenderMesh(meshList[GEO_DOGE],false);
	modelStack.PopMatrix();


}

void SceneSP::RenderFunStuff()
{
	for(int k= 0; k < 27; k++)
	{
		Fun[k].set(Doritos);
	}
	for(int j= 27; j < Fun.size(); j++)
	{
		Fun[j].set(MountainDew);
	}

	int counter = 0 ;
	for(int i = 0; i < 3; i++)
	{
		for(int x = 0; x < 2; x++)
		{
			for(int y = 0; y < 3; y++)
			{
				for(int z = 0; z < 3; z++)
				{
					if(Fun[counter].getEmpty() == false)
					{
						modelStack.PushMatrix();
						modelStack.Translate( 15 - ( x * 3 ) - (i * 12), (5 - (y * 1.4)) , (27 - z * 2));
						if( x % 2 == 0 && Fun[counter].getNo() == Doritos)
							modelStack.Rotate(180,0,1,0);
						modelStack.Rotate(-90,0,1,0);

						if ( Fun[counter].getNo() == Doritos )
							RenderMesh(meshList[GEO_DORITOS],true);
						else
							RenderMesh(meshList[GEO_MTN],true);

						modelStack.PopMatrix();
					}

					counter++;
				}
			}
		}
	}
}


