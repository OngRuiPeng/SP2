#ifndef SCENE_SP_H
#define SCENE_SP_H

#include "Scene.h"
#include "Camera3.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GLFW\glfw3.h"
#include "Obj.h"
#include "Npc.h"
#include <vector>
#include <string>
#include "timer.h"
using namespace std;

class SceneSP : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_MainMenuScreen,
		GEO_ChooseScreen,
		GEO_CUBE,
		GEO_MainMenuText,
		GEO_NPCText,
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
		GEO_CONTROLPANEL,
		GEO_SINK,
		GEO_WATER,
		GEO_TOILET,
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
		GEO_HEAD,
		GEO_BODY,
		GEO_LEFTHAND,
		GEO_RIGHTHAND,
		GEO_LEFTLEG,
		GEO_RIGHTLEG,

		GEO_CHEAD,
		GEO_CBODY,
		GEO_CLEFTHAND,
		GEO_CRIGHTHAND,
		GEO_CLEFTLEG,
		GEO_CRIGHTLEG,

		GEO_SHEAD,
		GEO_SBODY,
		GEO_SLEFTHAND,
		GEO_SRIGHTHAND,
		GEO_SLEFTLEG,
		GEO_SRIGHTLEG,

		GEO_DOORMAN,
		//NPCs=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		//NPC text
		GEO_CUSTOMERTEXT,
		GEO_CASHIERTEXT,
		GEO_SECURITYTEXT,
		//
		GEO_LIGHTBALL,

		GEO_SEE,

		NUM_GEOMETRY,
	};
	
	enum GAME_STATE
	{
		MAINMENU,
		CHOOSEMODE,
		GAMEROAM,
		GAMECHECKOUT,
		GAMETHIEF,
		GAMEFUN,
		EXIT,
		MAX_STATES,
	};

	enum CAM_STATE
	{
		NORMAL,
		CAM1,
		CAM2,
		CAM3,
		CAM4,
		CAM5,
		MAX_CAM,
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
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderCharacter();
	void RenderSkybox();
	void RenderMainMenu();
	void RenderChooseMode();
	void RenderSupermarket();
	void RenderInteractableObjs();
	void RenderPacks ();

	//collision
	bool AABBCheck(const Obj &box1,const Obj &box2);
	void collisionprevent(vector <Obj> a ,Vector3 camerathing, vector <Obj> b );
	Obj ItemTargetcollision();
	int NoItemTargetcollision();
	Obj InteractableTargetcollision();
	int NoInteractableTargetcollision();
	void updatecollision(double dt);
	void updateobj();

	//Interactions and their other variables
	void SlidingDoor(double);

	bool canput ;
	bool PickUpItem; 
	bool interactmah;
	bool DetectorsOn;

	float DoorSlideL; // Variable to move left door
	float DoorSlideR; // Variable to move right door
	bool inSupermarket; // Variable to check whether player is in the supermarket

	//NPC interactions, // Variable to check whether NPC is interacted with
	bool CashierText;  
	bool SecurityText; 
	bool CustomerText; 

	double time; // timer
	//Collision

	vector <Obj> OBJ ;
	vector <Obj> Items ;
	vector <Obj> Interactables ;

	Obj box1 ;
	Obj seewhere;

	//Npcs
	CNpc Cashier;
	CNpc Guard;
	CNpc Customer;
	CNpc Passerby1;
	CNpc Passerby2;

	void collisionOBJinit(void);
	void collisionITEMSinit(void);
	void collisionInteractionsinit(void);

	//Security camera
	bool SecurityCam ;
	int cam_state;
	void updateCam(double dt);
	Vector3 StorePos, StoreTarget1 , StoreTarget2;
	double CamTime;

	bool ChooseWhich;
	int WhichMode ;

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

	double FPS; 

	StopWatch mytimer;
};

#endif