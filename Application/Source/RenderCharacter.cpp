#include "SceneSP.h"

void SceneSP::RenderCharacter()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_DOORMAN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 4, 0);
	modelStack.Rotate(0, 0, 1, 0);
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
		modelStack.Translate(-0.5, -2.75, 0);
		RenderMesh(meshList[GEO_LEFTLEG], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0.5, -2.75, 0);
		RenderMesh(meshList[GEO_RIGHTLEG], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();



}