#include "SceneSP.h"

void SceneSP::RenderSupermarket()
{
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


	if ( TapSwitch == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, 0, 19);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(3.5, 2.5, 3.5);
		RenderMesh(meshList[GEO_WATER], true);
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, -10, 19);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(3.5, 2.5, 3.5);
		RenderMesh(meshList[GEO_WATER], true);
		modelStack.PopMatrix();	
	}
	
	
	modelStack.PushMatrix();
	modelStack.Translate(2, flushUp, 19);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3.5, 2.5, 3.5);
	RenderMesh(meshList[GEO_BIGWATER], true);
	modelStack.PopMatrix();	

	RenderFlush();

	
	modelStack.PopMatrix();
	//All pop
}

void SceneSP::RenderFlush()
{
	if (flushUp < -0.1)
	{
		FlushDir = false;
	}

	if (FlushDir == true && Flush == true)
	{
		flushUp -= 0.01;
	}

	else if (FlushDir == false && Flush == true)
	{
		if (flushUp < 0.7)
		{
			flushUp += 0.01;
		}
		else if (flushUp > 0.7)
		{
			Flush = false;
		}
	}
	


}