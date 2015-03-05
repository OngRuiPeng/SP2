/******************************************************************************/
/*!
\file	RenderSkybox.cpp
\author Job
\par	nyp
\brief
CPP to render skybox 
*/
/******************************************************************************/

#include "SceneSP.h"

void SceneSP::RenderSkybox()
{
	float scale = 500;
	float scalefloor = 250;
	float translate = 500;
	modelStack.PushMatrix();
	modelStack.Translate(0, -150, 0);



	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,translate,translate);
	modelStack.Rotate(180,0,0,1);
	modelStack.Rotate(180,0,1,0);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(scale,0,scale);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,translate,-translate + 10);
	modelStack.Rotate(180,0,0,1);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(scale,0,scale);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,translate + 495,0);
	modelStack.Rotate(90,0,1,0);
	modelStack.Rotate(180,1,0,0);
	modelStack.Scale(scale,0,scale);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(translate - 10,translate,0);
	modelStack.Rotate(90,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(scale + 50,0,scale);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-translate + 12,translate,0);
	modelStack.Rotate(-90,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(scale,0,scale);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(scalefloor,0, scalefloor);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();


}
