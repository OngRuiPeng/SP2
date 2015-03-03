#include "SceneSP.h"

void SceneSP::RenderCharacter()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_DOORMAN], true);
	modelStack.PopMatrix();

	//Customer
	modelStack.PushMatrix();
	modelStack.Translate(5, 4, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BODY], true);
		
		modelStack.PushMatrix();
		modelStack.Translate(0, 2, 0);
		RenderMesh(meshList[GEO_HEAD], true);	
		modelStack.PopMatrix();
		
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(meshList[GEO_LEFTHAND], true);
		modelStack.PopMatrix();
		
		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 0);
		RenderMesh(meshList[GEO_RIGHTHAND], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(CashRight, 1, 0, 0);
		modelStack.Translate(-0.5, -2.75, 0);
		RenderMesh(meshList[GEO_LEFTLEG], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(-CashRight, 1, 0, 0);
		modelStack.Translate(0.5, -2.75, 0);
		RenderMesh(meshList[GEO_RIGHTLEG], true);
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	//Passerby1
	modelStack.PushMatrix();
	modelStack.Translate(PBPos.x, PBPos.y, PBPos.z );
	modelStack.Rotate(RotatePB , 0, 1, 0);
	RenderMesh(meshList[GEO_BODY], true);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2, 0);
		RenderMesh(meshList[GEO_HEAD], true);	
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(-RotatePBHands, 1, 0, 0);
		modelStack.Translate(-1, 0, 0);
		RenderMesh(meshList[GEO_LEFTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(RotatePBHands, 1, 0, 0);
		modelStack.Translate(1, 0, 0);
		RenderMesh(meshList[GEO_RIGHTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(-RotatePBLegs,1,0,0);
		modelStack.Translate(-0.5, -2.75, 0);
		RenderMesh(meshList[GEO_LEFTLEG], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(RotatePBLegs,1,0,0);
		modelStack.Translate(0.5, -2.75, 0);
		RenderMesh(meshList[GEO_RIGHTLEG], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Passerby2
	modelStack.PushMatrix();
	modelStack.Translate(45 - Passerby2Dist, 4, -30);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_BODY], true);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2, 0);
		RenderMesh(meshList[GEO_HEAD], true);	
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(meshList[GEO_LEFTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 0);
		RenderMesh(meshList[GEO_RIGHTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(Passerby2Left, 1, 0, 0);
		modelStack.Translate(-0.5, -2.75, 0);
		RenderMesh(meshList[GEO_LEFTLEG], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(Passerby2Right, 1, 0, 0);
		modelStack.Translate(0.5, -2.75, 0);
		RenderMesh(meshList[GEO_RIGHTLEG], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Cashier
	modelStack.PushMatrix();
	modelStack.Translate(16, 4, 8);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_CBODY], true);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2, 0);
		RenderMesh(meshList[GEO_CHEAD], true);	
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(meshList[GEO_CLEFTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 0);
		RenderMesh(meshList[GEO_CRIGHTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(-0.5, -2.75, 0);
		RenderMesh(meshList[GEO_CLEFTLEG], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0.5, -2.75, 0);
		RenderMesh(meshList[GEO_CRIGHTLEG], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Cashier 2
	modelStack.PushMatrix();
	modelStack.Translate(25, 4, 8);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_CBODY], true);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2, 0);
		RenderMesh(meshList[GEO_CHEAD], true);	
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(meshList[GEO_CLEFTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 0);
		RenderMesh(meshList[GEO_CRIGHTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(-0.5, -2.75, 0);
		RenderMesh(meshList[GEO_CLEFTLEG], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0.5, -2.75, 0);
		RenderMesh(meshList[GEO_CRIGHTLEG], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Security Guard
	modelStack.PushMatrix();
	modelStack.Translate(SGPos.x, SGPos.y, SGPos.z);
	modelStack.Rotate(RotateSG, 0, 1, 0);
	modelStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_SBODY], true);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2, 0);
		RenderMesh(meshList[GEO_SHEAD], true);	
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(-1, 0, 0);
		RenderMesh(meshList[GEO_SLEFTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(1, 0, 0);
		RenderMesh(meshList[GEO_SRIGHTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(-RotateSGLegs,1,0,0);
		modelStack.Translate(-0.5, -2.75, 0);
		RenderMesh(meshList[GEO_SLEFTLEG], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Rotate(RotateSGLegs,1,0,0);
		modelStack.Translate(0.5, -2.75, 0);
		RenderMesh(meshList[GEO_SRIGHTLEG], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

}