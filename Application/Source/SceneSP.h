#ifndef SCENE_SP_H
#define SCENE_SP_H

#include "Scene.h"
#include "Camera3.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GLFW\glfw3.h"

class SceneSP : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_MainMenuScreen,
		GEO_PlayScreen,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_SPHERE,
		GEO_MainMenuText,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_LIGHTBALL,
		NUM_GEOMETRY,
	};
	
	enum GAME_STATE
	{
		MAINMENU,
		CHOOSEMODE,
		GAMEROAM,
		GAMECHECKOUT,
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



	//Render
	void RenderCharacter();
	void RenderSkybox();
	void RenderMainMenu();
	void RenderChooseMode();
	//update
	void updateMainMenu();
	void updateChooseMode();
	void updateRoam();
	void updateCheckOut();
	void updateFun();

	void mouseInput(double* xpos, double* ypos);
	double xpos;
	double ypos;
	double* xposition;
	double* yposition;
	
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

	double FPS; 


};
#endif