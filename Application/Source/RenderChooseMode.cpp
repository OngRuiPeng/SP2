#include "SceneSP.h"

void SceneSP::RenderChooseMode()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 9, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_ChooseScreen], false);
	modelStack.PopMatrix();
}