#include "SceneSP.h"

void SceneSP::RenderMainMenu()
{

	//modelStack.PushMatrix();
	//RenderMesh(meshList[GEO_MainMenuScreen], false);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//RenderTextOnScreen(meshList[GEO_MainMenuText], "Main menu", (1, 1, 1),3, 2, 18);
	//RenderTextOnScreen(meshList[GEO_MainMenuText], "Play", (1, 1, 1),3, 2, 15);
	//RenderTextOnScreen(meshList[GEO_MainMenuText], "Exit", (1, 1, 1),3, 2, 12);
	//modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_MainMenuScreen], false);
	modelStack.PopMatrix();
}