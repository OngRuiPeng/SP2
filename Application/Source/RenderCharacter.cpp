#include "SceneSP.h"

void SceneSP::RenderCharacter()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_DOORMAN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 20);
	RenderMesh(meshList[GEO_BODY], true);
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_HEAD], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_LEFTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_RIGHTHAND], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_LEFTLEG], true);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_RIGHTLEG], true);
		modelStack.PopMatrix();
	modelStack.PopMatrix();



}