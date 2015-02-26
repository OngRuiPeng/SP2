#include "SceneSP.h"


void SceneSP::RenderInteractableObjs()
{
	modelStack.PushMatrix();					
	modelStack.Translate(0, -0.1, 0);
	modelStack.Scale(1.1, 1.1, 1.1);

	//DOORS
	modelStack.PushMatrix();
	modelStack.Scale(3.5, 2.5, 3.5);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(1.9, 0, -DoorSlideR + 0.6);
	RenderMesh(meshList[GEO_DOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(3.5, 2.5, 3.5);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(1.9, 0, DoorSlideR);
	RenderMesh(meshList[GEO_DOOR], true);
	modelStack.PopMatrix();
	//!DOORS


	modelStack.PushMatrix();		//LEFT DOOR
	modelStack.Translate(18, 0, 34.2);
	modelStack.Scale(2.7, 2.5, 1.5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BACKDOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();	   //RIGHT DOOR
	modelStack.Translate(-12.8, 0, 34.2);
	modelStack.Scale(3.5, 2.5, 1.5);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BACKDOOR], true);
	modelStack.PopMatrix();


	modelStack.PushMatrix();		//LEFT DISPLAY CABINET

	modelStack.PushMatrix();		//Bottom layer

	if ( Items[63].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(14, 1.7, 19);
	RenderMesh(meshList[GEO_CAN1], true);
	modelStack.PopMatrix();
	}
	if ( Items[64].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(13, 1.7, 18.5);
	RenderMesh(meshList[GEO_CAN1], true);
	modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//Bottom layer end

	modelStack.PushMatrix();		//Middle layer

	if ( Items[61].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(14, 3, 19);
	RenderMesh(meshList[GEO_CAN1], true);
	modelStack.PopMatrix();	
	}
	if ( Items[62].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(13, 3, 18.5);
	RenderMesh(meshList[GEO_CAN1], true);
	modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//Middle layer end

	if ( Items[60].getEmpty() == false)
	{
	modelStack.PushMatrix();		//Top layer
	modelStack.Translate(14, 4.1, 19);
	RenderMesh(meshList[GEO_CAN1], true);
	modelStack.PopMatrix();			//Top layer end
	}

	modelStack.PopMatrix();			//LEFT DISPLAY CABINET END

	modelStack.PushMatrix();		//MIDDLE DISPLAY CABINET

	if ( Items[66].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(1, 2.1, 19);
	RenderMesh(meshList[GEO_CAN2], true);
	modelStack.PopMatrix();
	}
	if ( Items[65].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(1, 3.3, 19);
	RenderMesh(meshList[GEO_CAN2], true);
	modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//MIDDLE DISPLAY CABINET END

	modelStack.PushMatrix();		//RIGHT DISPLAY CABINET

	if ( Items[68].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-10, 1.95, 19.5);
	RenderMesh(meshList[GEO_CAN3], true);
	modelStack.PopMatrix();
	}
	if ( Items[67].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-10, 3.2, 19.5);
	RenderMesh(meshList[GEO_CAN3], true);
	modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//RIGHT DISPLAY CABINET END


	modelStack.PushMatrix();		//PIZZA BOXES

	if ( Items[73].getEmpty() == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-20, 5, 0.8);
		RenderMesh(meshList[GEO_BOX1], true);
		modelStack.PopMatrix();
	}

	if ( Items[72].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-20, 5, 4);
	RenderMesh(meshList[GEO_BOX1], true);
	modelStack.PopMatrix();
	}

	if ( Items[74].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-20, 4, 4);
	RenderMesh(meshList[GEO_BOX1], true);
	modelStack.PopMatrix();
	}

	if ( Items[70].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-20, 2.3, 10.8);
	RenderMesh(meshList[GEO_BOX1], true);
	modelStack.PopMatrix();
	}
	if ( Items[69].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-20, 3.2, 14);
	RenderMesh(meshList[GEO_BOX1], true);
	modelStack.PopMatrix();
	}

	if ( Items[71].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-20, 0.1, 14);
	RenderMesh(meshList[GEO_BOX1], true);
	modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//PIZZA BOXES END

	modelStack.PushMatrix();		//MACNCHEESE BOXES

	if ( Items[2].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(14.5, 4.5, 23);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[0].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(14.5, 4.5, 27);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[4].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(14.5, 3, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	} 

	modelStack.PopMatrix();			//MACNCHEESE BOXES END

	modelStack.PushMatrix();		//MACNCHEESE BOXES 2

	if ( Items[27].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(0, 4.5, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[29].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(0, 4.5, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[31].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//MACNCHEESE BOXES 2 END

	modelStack.PushMatrix();		//MACNCHEESE BOXES 3

	if ( Items[23].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(2.5, 3, 23);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[21].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(2.5, 3, 27);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[25].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(2.5, 1.5, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//MACNCHEESE BOXES 3 END

	modelStack.PushMatrix();		//MACNCHEESE BOXES 4
	if ( Items[39].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-12, 3, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[41].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-12, 3, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	if ( Items[43].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-12, 1.5, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_BOX2], true);
	modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//MACNCHEESE BOXES 4 END



	RenderPacks();


	modelStack.PopMatrix();			//ALL POP
}