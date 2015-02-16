#include "SceneSP.h"

void SceneSP::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x ,0, camera.position.z);

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,500,985);
	modelStack.Rotate(180,0,0,1);
	modelStack.Rotate(180,0,1,0);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(1000,0,500);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,500,-985);
	modelStack.Rotate(180,0,0,1);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(1000,0,500);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(0,990,0);
	modelStack.Rotate(90,0,1,0);
	modelStack.Rotate(180,1,0,0);
	modelStack.Scale(1000,0,1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(985,500,0);
	modelStack.Rotate(90,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(1000,0,500);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Translate(-985,500,0);
	modelStack.Rotate(-90,0,1,0);
	modelStack.Rotate(-90,1,0,0);
	modelStack.Scale(1000,0,500);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();


	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(2000,0,2000);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

}
