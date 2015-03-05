#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

/******************************************************************************/
/*!
\file	LoadOBJ.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare functions and members for loading Objs
*/
/******************************************************************************/

#include <vector>
#include "Vertex.h"
#include "Vector3.h"

bool LoadOBJ(
	const char *file_path, 
	std::vector<Position> & out_vertices, 
	std::vector<TexCoord> & out_uvs, 
	std::vector<Vector3> & out_normals
);

void IndexVBO(
	std::vector<Position> & in_vertices,
	std::vector<TexCoord> & in_uvs,
	std::vector<Vector3> & in_normals,

	std::vector<unsigned> & out_indices,
	std::vector<Vertex> & out_vertices
);

#endif