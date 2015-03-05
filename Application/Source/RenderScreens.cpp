/******************************************************************************/
/*!
\file	RenderScreens.cpp
\author Rui Peng
\par	nyp
\brief
CPP to render the different menu of the game states
*/
/******************************************************************************/

#include "SceneSP.h"
#include "Utility.h"

/******************************************************************************/
/*!
\brief
renders main menu
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
renders choose mode
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
renders busted screen
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
renders thief win screen
*/
/******************************************************************************/
void SceneSP::RenderThiefWin()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 6, 0);
	modelStack.Scale(23, 17, 10);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_ThiefWinScreen], false);
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_MainMenuText], Convert(ItemsStolen), (1, 0, 1),2.5, 20.1, 15.3);
}

/******************************************************************************/
/*!
\brief
renders check out win screen
*/
/******************************************************************************/
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