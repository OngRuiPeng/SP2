#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color , float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color ,float lengthX , float lengthY , float lengthZ );
	static Mesh* GenerateCircle(const std::string &meshName, Color color ,unsigned numSlice,float radius);
	static Mesh* GenerateRing(const std::string &meshName, Color color ,unsigned numSlice,float outerR , float innerR);
	static Mesh* GenerateSphere(const std::string &meshName, Color color , unsigned numStack ,unsigned numSlice,float radius);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path) ;
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol , float font[]);
	static Mesh* GeneratePicture(const std::string &meshName, unsigned numRow, unsigned numCol);
	static Mesh* GenerateTriangle(const std::string &meshName, Color color , float lengthX, float lengthY);
	static Mesh* GenerateStar(const std::string &meshName, Color color , float lengthX, float lengthY);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color , unsigned numStack ,unsigned numSlice,float height,float radius);
};

#endif