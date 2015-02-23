#include "SceneSP.h"

void SceneSP::RenderCharacter()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_DOORMAN], true);
	modelStack.PopMatrix();
}