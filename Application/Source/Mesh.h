#ifndef MESH_H
#define MESH_H

/******************************************************************************/
/*!
\file	Mesh.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare functions and members for mesh
*/
/******************************************************************************/

#include <string>
#include "Material.h"
/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned colorBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	unsigned textureID;

	void Render(unsigned offset, unsigned count);

	Material material;
};

#endif