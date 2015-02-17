#include "SceneSP.h"

void SceneSP::RenderSupermarket()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0.2, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SUPERMARKET], true);
	modelStack.PopMatrix();
}