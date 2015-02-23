#ifndef SCENE_SP_H
#define SCENE_SP_H

#include "Scene.h"
#include "Camera3.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GLFW\glfw3.h"
#include "Obj.h"

class SceneSP : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_MainMenuScreen,
		GEO_ChooseScreen,
		GEO_MainMenuText,

		//Skybox------------------------------------------------
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		//Skybox------------------------------------------------

		//Supermarket stuff=====================================
		GEO_SUPERMARKET,
		GEO_SUPERMARKETFLOOR,
		GEO_DISPLAYCABINET,
		GEO_SCANNER,
		GEO_DOOR,
		GEO_BACKDOOR,
		GEO_DIVIDER,
		GEO_SHELF,
		GEO_SHELF2,
		GEO_SHELF3,
		GEO_CASHIERTABLE,
		GEO_REGISTER,
		GEO_CAN1,
		GEO_CAN2,
		GEO_CAN3,
		GEO_BOX1,
		GEO_BOX2,
		GEO_PACK1,
		GEO_PACK2,
		GEO_PACK3,
		GEO_PACK4,
		//Supermarket stuff=====================================

		//NPCs=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		//-------Insert npcs here-------
		GEO_DOORMAN,
		//NPCs=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

		GEO_LIGHTBALL,
		NUM_GEOMETRY,
	};
	//
	//enum GEOMETRY_TYPE2
	//{
	//	
	//	NUM_GEOMETRY2,
	//};


	enum GAME_STATE
	{
		MAINMENU,
		CHOOSEMODE,
		GAMEROAM,
		GAMECHECKOUT,
		GAMETHIEF,
		GAMEFUN,
		MAX_STATES,
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

	virtual void Init(GLFWwindow* m_window, float w, float h);
	virtual void Update(double dt, GLFWwindow* m_window, float w, float h);
	virtual void Render();
	virtual void Exit();
	float translateX;
	float rotateAngle2;
	float rotateAngle3;
	float rotatedoor;
	float scaleAll;
	float scalekirby;
	int gamestate;
	Camera3 camera;	
	//Functions---------------------------------------
	void initSkybox();
	void initSupermarket();


	//Render
	void RenderCharacter();
	void RenderSkybox();
	void RenderMainMenu();
	void RenderChooseMode();
	void RenderSupermarket();
	void RenderInteractableObjs();
	void RenderPacks ();
	//update
	void updateMainMenu();
	void updateChooseMode();
	void updateRoam();
	void updateCheckOut();
	void updateFun();

	//collision
	bool AABBCheck(const Obj &box1,const Obj &box2);
	void collisionprevent(Obj &boxA , Vector3 camerathing);
	void collisionprevent2(Obj &boxA , Vector3 camerathing);
	void updatecollision(double dt);
	void updateobj();
	bool collision ; 
	Obj box1 , box2;

	void mouseInput(double* xpos, double* ypos);
	double xpos;
	double ypos;
	double* xposition;
	double* yposition;
	
private:
	unsigned m_vertexArrayID;

	Mesh* meshList[NUM_GEOMETRY];
	//Mesh* meshList2[NUM_GEOMETRY2];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	MS modelStack , viewStack , projectionStack;

	Light lights[2];

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	double FPS; 


};
#endif