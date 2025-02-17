#ifndef SCENE_SP_H
#define SCENE_SP_H

/******************************************************************************/
/*!
\file	SceneSP.h
\author SP'13 2015
\par	nyp
\brief
CPP to declare SceneSP members and functions
*/
/******************************************************************************/

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
#include <stdio.h>

#include <irrKlang.h>
#include "timer.h"
#include "Item.h"
//Music include
#pragma comment(lib, "irrKlang.lib")


using namespace irrklang;
using namespace std;
static float pop;
class SceneSP : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_CUBE,
		GEO_MainMenuScreen,
		GEO_ChooseScreen,
		GEO_MainMenuText,
		GEO_BustedScreen,
		GEO_ThiefWinScreen,
		GEO_CheckoutWinScreen,
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
		GEO_BIGWATER,
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
		GEO_LIGHTSWITCH,
		GEO_SECURITYCAM,
		//Supermarket stuff=====================================
		
		//TV stuff=====================================
		GEO_TV,
		//TV stuff=====================================

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
		
		//INVENTORY STUFF~~~~~~~~~~~~~~~~~~~~
		GEO_INVENTORYTEXT,
		GEO_INVENTORY,
		GEO_TOBLERONE,
		GEO_MACARONI,
		GEO_REDITOS,
		GEO_CAMPBELLA,
		GEO_CACTUS,
		GEO_CHICKEN,
		GEO_PIZZA,
		GEO_MAGGI,
		GEO_DEWTOS,
        GEO_MTNPIC,
        GEO_DORITOSPIC,
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		//Fun Stuff~~~~~~~~~~~~~~~~~~~~~~~~~~
		GEO_HITMARKER,
		GEO_SNOOPDOG,
		GEO_WEED,
        GEO_MTN,
        GEO_DORITOS,
        GEO_WEEDP,
        GEO_ILLUMINATI,
        GEO_DOGE,
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		GEO_LIGHTBALL,

		GEO_SEE,

		GEO_CHECKLIST,

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
		GAMEWINCHECKOUT,
		GAMEWINTHIEF,
		GAMEBUSTED,
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

	enum ITEM
	{
		Reditos, // PACK1 
		Campbella, // CAN2
		Toblerone, // PACK4
		Dewtos, // PACK2
		Pizza, // GEO_BOX1
		Cactus, // CAN3
		Chicken, // CAN1
		Maggi, // PACK3
		Macaroni, // GEO_BOX2
        Doritos,
        MountainDew,
		MAX_ITEM,
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
		U_LIGHTENABLED,

		//Light 0
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		//Light 0

		//Light 1
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		//Light 1


		U_NUMLIGHTS, 
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
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
	int gamestate;
	Camera3 camera;	
	
	//fontsize
	float fontSize[256];
	void readFontSize() ;

	//Functions---------------------------------------
	void initSkybox();
	void initTV();
	void initSupermarket();
	void initNPC();

	//Render
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderCharacter();
	void RenderSkybox();
	void RenderTV();
	void RenderMainMenu();
	void RenderChooseMode();
	void RenderBusted();
	void RenderThiefWin();
	void RenderCheckoutWin();
	void RenderSupermarket();
	void RenderInteractableObjs();
	void RenderPacks ();
	void RenderInventory();
	void RenderPictureOnScreen(Mesh* mesh, float sizeX , float sizeY , float x, float y);
	void RenderTapWater();
	void RenderFlush();
	int Renderirr();
	void RenderCams();
	void RenderFunSMarket();
    void RenderFunPic();
    void RenderFunStuff();

	void UpdateNPC(double);
	void UpdateCustomer(double);
	//collision
	bool AABBCheck(const Obj &box1,const Obj &box2);
	void collisionprevent(vector <Obj> a ,Vector3 camerathing, vector <Obj> b );
	Obj ItemTargetcollision();
	int NoItemTargetcollision();
	Obj InteractableTargetcollision();
	int NoInteractableTargetcollision();
	void updatecollision(double dt);
	void updateobj();

	vector <Obj> OBJ ;
	vector <Obj> Items ;
	vector <Obj> Interactables ;
	vector <Obj> Fun;

	Obj box1 ;
	Obj seewhere;
	


	int ItemNo;

	vector <CItem> ItemData;

	//Interactions and their other variables
	void SlidingDoor(double);
	double DoorSlide;

	void Jump (double);
	bool JumpDirection;
	bool JumpState;
	bool JumpSwitch;
	bool TapSwitch;
	bool TapTurn;
	bool SinkDrain;
	bool SinkDrainDir;
	bool Flush;
	bool FlushDir;
	float flushUp;
	float sinkUp;
	float waterTurn;
	float waterScale;
	float waterTrans;

	bool PlaceItem ;
	bool PickUpItem; 
	bool Interact;
	bool DetectorsOn;
	bool toiletDoor;
	bool securityDoor;

	float toiletDoorMove;
	float securityDoorMove;

	float DoorSlideL; // Variable to move left door
	float DoorSlideR; // Variable to move right door
	bool inSupermarket; // Variable to check whether player is in the supermarket

	//Npc movement
	float Passerby2Left;
	float Passerby2Right;
	float Passerby2Dist;

	float CashRight;
	float CashTimer;
	bool CashWalk;
	float CashRotArm;
	bool ArmRaise;
	float ArmTransUp;
	float ArmTransRight;
	float CashMovX;
	float CashMovZ;
	float RotBody;
	bool CycleOn;
	bool ArmCycleOn;
	bool FullArmCycle;
	//NPC interactions, // Variable to check whether NPC is interacted with
	bool CashierText;  
	bool SecurityText; 
	bool CustomerText; 

	//timer
	double time; 

	//NPC
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

	//Inventory 
	void InitItemData();
	void updateInventory( CItem a , bool b );
	
	vector <CItem> InventoryData;

	CItem nullthis;
	bool ItemsInInventory;
	double Inventorytimer;
	// cashier slide
	bool ItemSlide;
	bool Deletemah;
	float translateItemZ;
	float translateItemX;
	int WhichCashier;
	CItem whichItem;
	void updateItemSlide(double dt, int a);
	vector <CItem> CheckoutList;
	bool CheckListDone;

	// Security guard 
	bool Caught;
	Vector3 SGPos;
	Vector3 SGMov;
	Vector3 SGTar;
	vector <Obj> NpcBB ;
	float securityStay;
	int SGPoint;
	bool InitSGOnce;
	void UpdateSG(double dt) ;
	float RotateSG;
	float RotateSGLegs;
	bool MoveSGLegs;
	bool MoveSGLegsOrNot;

	//Passerby1
	Vector3 PBPos;
	Vector3 PBMov;
	Vector3 PBTar;
	float PBStay;
	int PBPoint;
	bool InitPBOnce;
	float RotatePB;
	float RotatePBLegs;
	float RotatePBHands;
	bool MovePBLegs;
	bool MovePBLegsOrNot;

	//Checklist 
	void genCheckList();
	CItem CheckList[9] ; 
	CItem checklistitem;
	bool CheckCheckOut[9];
	void updateCheckList();
	bool toggleCheck;

	//Position
	void mouseInput(double* xpos, double* ypos);
	double xpos;
	double ypos;
	double* xposition;
	double* yposition;
	
	//Music
	bool music;
	bool hitto;
    int hit;
	double hittimer;
	//Gamemode 
	bool Alarm;
	int ItemsStolen;

	bool inSecurityRoom;
	Vector3 VectorFromSG;
	float DistFromSG;
	double Supermarkettimer;
	double wintimer;

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