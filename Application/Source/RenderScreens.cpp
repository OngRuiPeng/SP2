#include "SceneSP.h"

void SceneSP::RenderMainMenu()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_MainMenuScreen], false);
	modelStack.PopMatrix();
}

void SceneSP::RenderChooseMode()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_ChooseScreen], false);
	modelStack.PopMatrix();
}

void SceneSP::RenderBusted()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_BustedScreen], false);
	modelStack.PopMatrix();
}

void SceneSP::RenderThiefWin()
{

}

void SceneSP::RenderCheckoutWin()
{

}