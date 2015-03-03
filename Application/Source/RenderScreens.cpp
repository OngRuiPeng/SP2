#include "SceneSP.h"
#include "Utility.h"

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
	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_ThiefWinScreen], false);
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_MainMenuText], Convert(ItemsStolen), (1, 0, 1),2.5, 5, 4);
}

void SceneSP::RenderCheckoutWin()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_CheckoutWinScreen], false);
	modelStack.PopMatrix();
}