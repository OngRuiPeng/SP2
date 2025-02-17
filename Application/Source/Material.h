#ifndef MATERIAL_H
#define MATERIAL_H

/******************************************************************************/
/*!
\file	Material.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare members for material
*/
/******************************************************************************/

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f) 
	{Set(r, g, b);}
	void Set(float r, float g, float b) 
	{this->r = r; this->g = g; this->b = b;}
};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;

	Material()
	{
		kAmbient.Set(0.6f,0.6f,0.6f);
		kDiffuse.Set(0.3f,0.3f,0.3f);
		kSpecular.Set(0.1f,0.1f,0.1f);
		kShininess = 10.f;
	}

};

#endif