#include "SceneSP.h"

void SceneSP::RenderPacks()
{
	modelStack.PushMatrix();		//ALL PUSH

	modelStack.PushMatrix();		//PACK1 1
	
	modelStack.PushMatrix();
	modelStack.Translate(14.5, 5, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(14.5, 3.6, 23);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(14.5, 3.6, 27);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK1 1 END

	modelStack.PushMatrix();		//PACK1 2
	
	modelStack.PushMatrix();
	modelStack.Translate(12, 5, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 3.6, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 3.6, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK1 2 END

	modelStack.PushMatrix();		//PACK1 2
	
	modelStack.PushMatrix();
	modelStack.Translate(0, 5, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.6, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.6, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK1 2 END

	modelStack.PushMatrix();		//PACK1 2
	
	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 5, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 3.6, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK1], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK1 2 END

	modelStack.PushMatrix();		//PACK4 1
	
	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 2, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 3.4, 28);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 4.9, 22);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK4 1 END

	modelStack.PushMatrix();		//PACK4 2
	
	modelStack.PushMatrix();
	modelStack.Translate(14.5, 2, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(14.5, 2, 28);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(14.5, 2, 22);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK4 2 END

	modelStack.PushMatrix();		//PACK4 3
	
	modelStack.PushMatrix();
	modelStack.Translate(3, 4.9, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(3, 4.9, 28);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(3, 4.9, 22);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK4], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK4 3 END

	modelStack.PushMatrix();		//PACK2 1
	
	modelStack.PushMatrix();
	modelStack.Translate(12, 3.6, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 5, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 5, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 2.1, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 2.1, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 2.1, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK2 1 END

	modelStack.PushMatrix();		//PACK2 2

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.1, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.1, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 2.1, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK2 2 END

	modelStack.PushMatrix();		//PACK2 3

	modelStack.PushMatrix();
	modelStack.Translate(-12, 5, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-12, 5, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-12, 5, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK2 3 END

	modelStack.PushMatrix();		//PACK2 4

	modelStack.PushMatrix();
	modelStack.Translate(-12, 3.6, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-12, 2.1, 25);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-12, 2.1, 27);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-12, 2.1, 23);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK2 4 END

	modelStack.PushMatrix();		//PACK2 5

	modelStack.PushMatrix();
	modelStack.Translate(2.5, 3.6, 25);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.5, 2.1, 27);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.5, 2.1, 23);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK2 5 END

	modelStack.PushMatrix();		//PACK2 6

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 5, 27);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 3.6, 23);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 2.1, 23);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, 2.1, 27);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_PACK2], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();			//PACK2 6 END

	modelStack.PushMatrix();		//PACK3 1 

	if ( Items[54].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(2, 5.8, 40);
	RenderMesh(meshList[GEO_PACK3], true);
	modelStack.PopMatrix();
	}

	if ( Items[55].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-2, 5.8, 40);
	RenderMesh(meshList[GEO_PACK3], true);
	modelStack.PopMatrix();
	}

	if ( Items[56].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(2, 3.4, 40);
	RenderMesh(meshList[GEO_PACK3], true);
	modelStack.PopMatrix();
	}

	if ( Items[57].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-2, 3.4, 40);
	RenderMesh(meshList[GEO_PACK3], true);
	modelStack.PopMatrix();
	}

	if ( Items[58].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(2, 1, 40);
	RenderMesh(meshList[GEO_PACK3], true);
	modelStack.PopMatrix();
	}

	if ( Items[59].getEmpty() == false)
	{
	modelStack.PushMatrix();
	modelStack.Translate(-2, 1, 40);
	RenderMesh(meshList[GEO_PACK3], true);
	modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//PACK3 1 END


	modelStack.PopMatrix();
	//ALL POP
}