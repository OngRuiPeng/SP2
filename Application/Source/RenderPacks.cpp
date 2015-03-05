/******************************************************************************/
/*!
\file	RenderPacks.cpp
\author Job , Jun Sen
\par	nyp
\brief
CPP to render items on the shelves 
*/
/******************************************************************************/

#include "SceneSP.h"

/******************************************************************************/
/*!
\brief
render packs on shelves
*/
/******************************************************************************/
void SceneSP::RenderPacks()
{
	modelStack.PushMatrix();		//ALL PUSH

	modelStack.PushMatrix();		//PACK1 1

	if ( Items[1].getEmpty() == false)
	{
		Items[1].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(14.5, 5, 25);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	if ( Items[5].getEmpty() == false)
	{
		Items[5].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(14.5, 3.6, 23);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	if ( Items[3].getEmpty() == false)
	{
		Items[3].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(14.5, 3.6, 27);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK1 1 END

	modelStack.PushMatrix();		//PACK1 2

	if ( Items[10].getEmpty() == false)
	{
		Items[10].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 5, 25);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	if ( Items[14].getEmpty() == false)
	{
		Items[14].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 3.6, 23);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	if ( Items[12].getEmpty() == false)
	{
		Items[12].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 3.6, 27);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK1 2 END

	modelStack.PushMatrix();		//PACK1 2

	if ( Items[28].getEmpty() == false)
	{
		Items[28].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(0, 5, 25);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	if ( Items[30].getEmpty() == false)
	{
		Items[30].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(0, 3.6, 23);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	if ( Items[32].getEmpty() == false)
	{
		Items[32].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(0, 3.6, 27);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//PACK1 2 END

	modelStack.PushMatrix();		//PACK1 2

	if ( Items[46].getEmpty() == false)
	{
		Items[46].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 5, 25);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}

	if ( Items[49].getEmpty() == false)
	{
		Items[49].set(Reditos);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 3.6, 25);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK1], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK1 2 END

	modelStack.PushMatrix();		//PACK4 1

	if ( Items[52].getEmpty() == false)
	{
		Items[52].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 2, 25);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	if ( Items[48].getEmpty() == false)
	{
		Items[48].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 3.4, 28);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	if ( Items[47].getEmpty() == false)
	{
		Items[47].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 4.9, 22);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK4 1 END

	modelStack.PushMatrix();		//PACK4 2

	if ( Items[7].getEmpty() == false)
	{
		Items[7].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(14.5, 2, 25);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	if ( Items[6].getEmpty() == false)
	{
		Items[6].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(14.5, 2, 28);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}

	if ( Items[8].getEmpty() == false)
	{
		Items[8].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(14.5, 2, 22);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK4 2 END

	modelStack.PushMatrix();		//PACK4 3
	if ( Items[19].getEmpty() == false)
	{
		Items[19].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(3, 4.9, 25);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	if ( Items[18].getEmpty() == false)
	{
		Items[18].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(3, 4.9, 28);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	if ( Items[20].getEmpty() == false)
	{
		Items[20].set(Toblerone);
		modelStack.PushMatrix();
		modelStack.Translate(3, 4.9, 22);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK4], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK4 3 END

	modelStack.PushMatrix();		//PACK2 1

	if ( Items[13].getEmpty() == false)
	{
		Items[13].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 3.6, 25);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[9].getEmpty() == false)
	{
		Items[9].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 5, 27);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[11].getEmpty() == false)
	{
		Items[11].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 5, 23);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[16].getEmpty() == false)
	{
		Items[16].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 2.1, 25);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[15].getEmpty() == false)
	{
		Items[15].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 2.1, 27);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[17].getEmpty() == false)
	{
		Items[17].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(12, 2.1, 23);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK2 1 END

	modelStack.PushMatrix();		//PACK2 2

	if ( Items[34].getEmpty() == false)
	{
		Items[34].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2.1, 25);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[35].getEmpty() == false)
	{
		Items[35].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2.1, 27);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[33].getEmpty() == false)
	{
		Items[33].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(0, 2.1, 23);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK2 2 END

	modelStack.PushMatrix();		//PACK2 3
	if ( Items[37].getEmpty() == false)
	{
		Items[37].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-12, 5, 25);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[38].getEmpty() == false)
	{
		Items[38].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-12, 5, 27);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[36].getEmpty() == false)
	{
		Items[36].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-12, 5, 23);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//PACK2 3 END

	modelStack.PushMatrix();		//PACK2 4

	if ( Items[40].getEmpty() == false)
	{
		Items[40].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-12, 3.6, 25);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}

	if ( Items[44].getEmpty() == false)
	{
		Items[44].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-12, 2.1, 27);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[42].getEmpty() == false)
	{
		Items[42].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-12, 2.1, 23);
		modelStack.Rotate(-90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK2 4 END

	modelStack.PushMatrix();		//PACK2 5

	if ( Items[22].getEmpty() == false)
	{
		Items[22].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(2.5, 3.6, 25);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[24].getEmpty() == false)
	{
		Items[24].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(2.5, 2.1, 27);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[26].getEmpty() == false)
	{
		Items[26].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(2.5, 2.1, 23);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK2 5 END

	modelStack.PushMatrix();		//PACK2 6

	if ( Items[45].getEmpty() == false)
	{
		Items[45].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 5, 27);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[50].getEmpty() == false)
	{
		Items[50].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 3.6, 23);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[53].getEmpty() == false)
	{
		Items[53].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 2.1, 23);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	if ( Items[51].getEmpty() == false)
	{
		Items[51].set(Dewtos);
		modelStack.PushMatrix();
		modelStack.Translate(-9.5, 2.1, 27);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_PACK2], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();			//PACK2 6 END

	modelStack.PushMatrix();		//PACK3 1 

	if ( Items[54].getEmpty() == false)
	{
		Items[54].set(Maggi);
		modelStack.PushMatrix();
		modelStack.Translate(2, 5.8, 40);
		RenderMesh(meshList[GEO_PACK3], true);
		modelStack.PopMatrix();
	}

	if ( Items[55].getEmpty() == false)
	{
		Items[55].set(Maggi);
		modelStack.PushMatrix();
		modelStack.Translate(-2, 5.8, 40);
		RenderMesh(meshList[GEO_PACK3], true);
		modelStack.PopMatrix();
	}

	if ( Items[56].getEmpty() == false)
	{
		Items[56].set(Maggi);
		modelStack.PushMatrix();
		modelStack.Translate(2, 3.4, 40);
		RenderMesh(meshList[GEO_PACK3], true);
		modelStack.PopMatrix();
	}

	if ( Items[57].getEmpty() == false)
	{
		Items[57].set(Maggi);
		modelStack.PushMatrix();
		modelStack.Translate(-2, 3.4, 40);
		RenderMesh(meshList[GEO_PACK3], true);
		modelStack.PopMatrix();
	}

	if ( Items[58].getEmpty() == false)
	{
		Items[58].set(Maggi);
		modelStack.PushMatrix();
		modelStack.Translate(2, 1, 40);
		RenderMesh(meshList[GEO_PACK3], true);
		modelStack.PopMatrix();
	}

	if ( Items[59].getEmpty() == false)
	{
		Items[59].set(Maggi);
		modelStack.PushMatrix();
		modelStack.Translate(-2, 1, 40);
		RenderMesh(meshList[GEO_PACK3], true);
		modelStack.PopMatrix();
	}

	modelStack.PopMatrix();			//PACK3 1 END


	modelStack.PopMatrix();
	//ALL POP
}