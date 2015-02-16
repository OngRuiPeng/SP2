#ifndef SCENE_SP_H
#define SCENE_SP_H

#include "Scene.h"
#include "Camera3.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"


class SceneSP : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE,
		GEO_TEXT,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_LIGHTBALL,
		GEO_HEAD,
		GEO_BODY,
		GEO_BODYD1,
		GEO_BODYD2,
		GEO_LIMB,
		GEO_COAT,
		GEO_COAT1,
		GEO_ARM,
		GEO_SLEEVE,
		GEO_EYES1,
		GEO_EYES2,
		GEO_HEADT,
		GEO_STAR,
		GEO_HEADB,
		GEO_HEADBB,
		GEO_WEAPRING,
		GEO_BEAK,
		GEO_CYL,
		GEO_WEAP1,
		GEO_TREE,
		GEO_CASTLE,
		GEO_DOOR,
		GEO_BUSH,
		GEO_LAMPPOST,
		GEO_KIRBY,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_NUMLIGHTS, 
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_TOTAL,
	};

public:
	SceneSP();
	~SceneSP();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	float translateX;
	float rotateAngle2;
	float rotateAngle3;
	float rotatedoor;
	float scaleAll;
	float scalekirby;
	void RenderCharacter();
	void RenderSkybox();

	Camera3 camera;	

	
private:
	unsigned m_vertexArrayID;

	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack , viewStack , projectionStack;

	Light lights[2];

	
	void RenderMesh(Mesh *mesh, bool enableLight);

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	float FPS; 

	

};
#endif