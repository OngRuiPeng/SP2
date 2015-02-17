#include "SceneSP.h"

void SceneSP::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 18, 0);

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,50,50);
	modelStack.Rotate(180,0,0,1);
	modelStack.Rotate(180,0,1,0);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(51,0,51);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,50,-50);
	modelStack.Rotate(180,0,0,1);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(51,0,51);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,50,0);
	modelStack.Rotate(90,0,1,0);
	modelStack.Rotate(180,1,0,0);
	modelStack.Scale(51,0,51);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(50,50,0);
	modelStack.Rotate(90,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(51,0,51);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-50,50,0);
	modelStack.Rotate(-90,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(51,0,51);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(51,0,51);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();


	modelStack.PopMatrix();
}
