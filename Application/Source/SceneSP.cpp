#include <iostream>
#include "SceneSP.h"


#include "SceneSP.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"

#include "LoadTGA.h"

#include "Camera3.h"

#include "windows.h"

#include <sstream>
#include <fstream>

#define LSPEED 20.f 

ISoundEngine* engine = createIrrKlangDevice(ESOD_AUTO_DETECT,ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
ISound* detectors = engine->play2D("../irrKlang/media/Darudepasu.mp3", false,true); // Main main menu	
using namespace std;

SceneSP::SceneSP()
{

}

SceneSP::~SceneSP()
{
}

void SceneSP::Init(GLFWwindow* m_window, float w, float h)
{
	xpos = w / 2;
	ypos = h / 2;

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(m_window, xpos, ypos);

	readFontSize();

	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glDisable(GL_CULL_FACE);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader" );
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");


	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");	
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 1000, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 0.5;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_POINT;
	lights[1].position.Set(0, 25, 0);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 1.f, 0.f);

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Initialize camera settings
	camera.Init(Vector3(0, 6, -40), Vector3(0, 6, 0), Vector3(0, 1, 0));

	//After gluseprogram

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);



	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	//Inits
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_MainMenuScreen] = MeshBuilder::GenerateQuad("main menu screen", Color(1, 0, 0), 100, 100);
	meshList[GEO_MainMenuScreen]->textureID = LoadTGA("Image//MainMenu.tga");

	meshList[GEO_ChooseScreen] = MeshBuilder::GenerateQuad("choose mode screen", Color(1, 1, 1), 1, 1);
	meshList[GEO_ChooseScreen]->textureID = LoadTGA("Image//PlayScreen.tga");

	meshList[GEO_BustedScreen] = MeshBuilder::GenerateQuad("Busted screen", Color(1, 1, 1), 1, 1);
	meshList[GEO_BustedScreen]->textureID = LoadTGA("Image//Busted.tga");

	meshList[GEO_ThiefWinScreen] = MeshBuilder::GenerateQuad("Thief win screen", Color(1, 1, 1), 1, 1);
	meshList[GEO_ThiefWinScreen]->textureID = LoadTGA("Image//WinThief.tga");

	meshList[GEO_CheckoutWinScreen] = MeshBuilder::GenerateQuad("Checkout win screen", Color(1, 1, 1), 1, 1);
	meshList[GEO_CheckoutWinScreen]->textureID = LoadTGA("Image//WinCheckout.tga");

	initSkybox();

	//TEXT
	meshList[GEO_MainMenuText] = MeshBuilder::GenerateText("text", 16, 16 , fontSize );
	meshList[GEO_MainMenuText]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_NPCText] = MeshBuilder::GenerateText("text", 16, 16 , fontSize );
	meshList[GEO_NPCText]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_SUPERMARKET] = MeshBuilder::GenerateOBJ("Supermarket", "OBJ//Supermarket.obj");
	meshList[GEO_SUPERMARKET]->textureID = LoadTGA("Image//WallTxt.tga");

	meshList[GEO_CUSTOMERTEXT] = MeshBuilder::GenerateText("Customer text", 16, 16 , fontSize );
	meshList[GEO_CUSTOMERTEXT]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_CASHIERTEXT] = MeshBuilder::GenerateText("Cashier text", 16, 16 , fontSize );
	meshList[GEO_CASHIERTEXT]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_SECURITYTEXT] = MeshBuilder::GenerateText("Security guard text", 16, 16 , fontSize );
	meshList[GEO_SECURITYTEXT]->textureID = LoadTGA("Image//ExportedFont.tga");

	//Supermarket
	meshList[GEO_SUPERMARKETFLOOR] = MeshBuilder::GenerateOBJ("SupermarketFloor", "OBJ//SupermarketFloor.obj");
	meshList[GEO_SUPERMARKETFLOOR]->textureID = LoadTGA("Image//SupermarketTiles.tga");

	meshList[GEO_DISPLAYCABINET] = MeshBuilder::GenerateOBJ("DisplayCabinet", "OBJ//DisplayCabinet.obj");
	meshList[GEO_DISPLAYCABINET]->textureID = LoadTGA("Image//DisplayCabinet.tga");

	meshList[GEO_SCANNER] = MeshBuilder::GenerateOBJ("Scanner", "OBJ//Scanner.obj");
	meshList[GEO_SCANNER]->textureID = LoadTGA("Image//Scanner.tga");

	meshList[GEO_DIVIDER] = MeshBuilder::GenerateOBJ("Divider", "OBJ//Divider.obj");
	meshList[GEO_DIVIDER]->textureID = LoadTGA("Image//Scanner.tga");

	meshList[GEO_CONTROLPANEL] = MeshBuilder::GenerateOBJ("Control Panel", "OBJ//ControlPanel.obj");
	meshList[GEO_CONTROLPANEL]->textureID = LoadTGA("Image//ControlPanel.tga");

	meshList[GEO_SINK] = MeshBuilder::GenerateOBJ("Sink", "OBJ//Sink.obj");
	meshList[GEO_SINK]->textureID = LoadTGA("Image//ToiletTxt.tga");

	meshList[GEO_TOILET] = MeshBuilder::GenerateOBJ("Toilet", "OBJ//Toilet.obj");
	meshList[GEO_TOILET]->textureID = LoadTGA("Image//ToiletTxt.tga");

	meshList[GEO_WATER] = MeshBuilder::GenerateOBJ("Water", "OBJ//Water.obj");
	meshList[GEO_WATER]->textureID = LoadTGA("Image//WaterTxt.tga");

	meshList[GEO_BIGWATER] = MeshBuilder::GenerateOBJ("BigWater", "OBJ//BigWater.obj");
	meshList[GEO_BIGWATER]->textureID = LoadTGA("Image//BigWater.tga");

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//Door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//Door.tga");

	meshList[GEO_BACKDOOR] = MeshBuilder::GenerateOBJ("Backdoor", "OBJ//Backdoor.obj");
	meshList[GEO_BACKDOOR]->textureID = LoadTGA("Image//Door.tga");

	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("Shelf", "OBJ//Shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//shelf.tga");

	meshList[GEO_SHELF2] = MeshBuilder::GenerateOBJ("Shelf2", "OBJ//Shelf2.obj");
	meshList[GEO_SHELF2]->textureID = LoadTGA("Image//Shelf2.tga");

	meshList[GEO_SHELF3] = MeshBuilder::GenerateOBJ("Shelf3", "OBJ//Shelf3.obj");
	meshList[GEO_SHELF3]->textureID = LoadTGA("Image//Shelf3Txt.tga");

	meshList[GEO_CASHIERTABLE] = MeshBuilder::GenerateOBJ("Cashier table", "OBJ//CashierTable.obj");
	meshList[GEO_CASHIERTABLE]->textureID = LoadTGA("Image//CashierTxt.tga");

	meshList[GEO_REGISTER] = MeshBuilder::GenerateOBJ("Register", "OBJ//Register.obj");
	meshList[GEO_REGISTER]->textureID = LoadTGA("Image//Register.tga");

	meshList[GEO_CAN1] = MeshBuilder::GenerateOBJ("Can1", "OBJ//Can1.obj");
	meshList[GEO_CAN1]->textureID = LoadTGA("Image//Can1.tga");

	meshList[GEO_CAN2] = MeshBuilder::GenerateOBJ("Can2", "OBJ//Can2.obj");
	meshList[GEO_CAN2]->textureID = LoadTGA("Image//Can2.tga");

	meshList[GEO_CAN3] = MeshBuilder::GenerateOBJ("Can3", "OBJ//Can3.obj");
	meshList[GEO_CAN3]->textureID = LoadTGA("Image//Can3.tga");

	meshList[GEO_BOX1] = MeshBuilder::GenerateOBJ("Box1", "OBJ//Box1.obj");
	meshList[GEO_BOX1]->textureID = LoadTGA("Image//Box1.tga");

	meshList[GEO_BOX2] = MeshBuilder::GenerateOBJ("Box2", "OBJ//Box2.obj");
	meshList[GEO_BOX2]->textureID = LoadTGA("Image//Box2.tga");

	meshList[GEO_PACK1] = MeshBuilder::GenerateOBJ("Pack1", "OBJ//Pack1.obj");
	meshList[GEO_PACK1]->textureID = LoadTGA("Image//Pack1.tga");

	meshList[GEO_PACK2] = MeshBuilder::GenerateOBJ("Pack2", "OBJ//Pack2.obj");
	meshList[GEO_PACK2]->textureID = LoadTGA("Image//Pack2.tga");

	meshList[GEO_PACK3] = MeshBuilder::GenerateOBJ("Pack3", "OBJ//Pack3.obj");
	meshList[GEO_PACK3]->textureID = LoadTGA("Image//Pack3.tga");

	meshList[GEO_PACK4] = MeshBuilder::GenerateOBJ("Pack4", "OBJ//Pack4.obj");
	meshList[GEO_PACK4]->textureID = LoadTGA("Image//Pack4.tga");

	meshList[GEO_LIGHTSWITCH] = MeshBuilder::GenerateOBJ("Light Switch", "OBJ//LightSwitch.obj");
	meshList[GEO_LIGHTSWITCH]->textureID = LoadTGA("Image//LightSwitch.tga");

	initNPC();
	// inventory init 

	meshList[GEO_INVENTORY] = MeshBuilder::GeneratePicture("Slots",1,1);
	meshList[GEO_INVENTORY]->textureID = LoadTGA("image//Inventory.tga");

	meshList[GEO_TOBLERONE] = MeshBuilder::GeneratePicture("toblerone",1,1);
	meshList[GEO_TOBLERONE]->textureID = LoadTGA("image//InvenToblerone.tga");

	meshList[GEO_MACARONI] = MeshBuilder::GeneratePicture("macaroni",1,1);
	meshList[GEO_MACARONI]->textureID = LoadTGA("image//Macaroni.tga");

	meshList[GEO_REDITOS] = MeshBuilder::GeneratePicture("reditos",1,1);
	meshList[GEO_REDITOS]->textureID = LoadTGA("image//Reditos.tga");

	meshList[GEO_CAMPBELLA] = MeshBuilder::GeneratePicture("campbella",1,1);
	meshList[GEO_CAMPBELLA]->textureID = LoadTGA("image//campbella.tga");

	meshList[GEO_CACTUS] = MeshBuilder::GeneratePicture("cactus",1,1);
	meshList[GEO_CACTUS]->textureID = LoadTGA("image//CactusJuice.tga");

	meshList[GEO_CHICKEN] = MeshBuilder::GeneratePicture("chicken",1,1);
	meshList[GEO_CHICKEN]->textureID = LoadTGA("image//Chicken.tga");

	meshList[GEO_PIZZA] = MeshBuilder::GeneratePicture("pizza",1,1);
	meshList[GEO_PIZZA]->textureID = LoadTGA("image//Pizza.tga");

	meshList[GEO_MAGGI] = MeshBuilder::GeneratePicture("maggi",1,1);
	meshList[GEO_MAGGI]->textureID = LoadTGA("image//Maggi.tga");

	meshList[GEO_DEWTOS] = MeshBuilder::GeneratePicture("dewtos",1,1);
	meshList[GEO_DEWTOS]->textureID = LoadTGA("image//Dewtos.tga");

	//variables
	gamestate = MAINMENU;

	inSupermarket = false;
	CashierText = false;
	DetectorsOn = true;
	CheckListDone = false;

	Cashier.setName("Jill");
	Cashier.setType("Cashier");
	Guard.setName("Bobby");
	Guard.setType("SecurityGuard");
	Customer.setName("James");
	Customer.setType("Customer");
	Passerby1.setName("Andrew");
	Passerby1.setType("Passerby");
	Passerby2.setName("Peter");
	Passerby2.setType("Passerby");

	DoorSlide = -0.75;

	time = 0;
	translateX = 0 ;
	PickUpItem = false;
	Interact = false;

	JumpDirection = false;
	JumpState = false;

	//interaction
	//sink and toiletbowl
	TapSwitch = false;
	TapTurn = false;
	SinkDrain = false;
	SinkDrainDir = false;
	sinkUp = 1.18;
	waterTurn = 90;
	waterScale = 2;
	waterTrans = 1.68;

	Flush = false;
	FlushDir = false;
	flushUp = 0.55;
	//door
	toiletDoorMove = 0;
	toiletDoor = false;
	securityDoorMove = 0;
	securityDoor = false;
	//Npc variables
	Passerby2Left = 0;
	Passerby2Right = 0;
	Passerby2Dist = 0;

	// security guard
	SGPos = Vector3(-12,4,0);
	SGMov = Vector3(0,0,0);
	SGTar = Vector3(0,0,0);
	Caught = false;
	securityStay = 11 ;
	SGPoint = 0 ;
	InitSGOnce = false;
	RotateSG = 0 ;
	RotateSGLegs = 0 ;
	MoveSGLegs = true;
	MoveSGLegsOrNot = false;

	//Passerby1
	PBPos = Vector3(-55,4,-15);
	PBMov = Vector3(0,0,0);
	PBTar = Vector3(0,0,0);
	PBStay = 11;
	PBPoint = 0;
	RotatePB = 0;
	RotatePBLegs = 0;
	RotatePBHands = 0;
	InitPBOnce = false;
	MovePBLegs = true;
	MovePBLegsOrNot = false;

	//Customer
	CashRight = 0;
	CashTimer = 0;
	CashWalk = false;
	CashRotArm = 0;
	ArmRaise = true;
	ArmTransUp = 0.2;
	ArmTransRight = -0.3;
	CashMovX = 6;
	CashMovZ = 25;
	RotBody = 90;
	CycleOn = true;
	//**********************************************************   collisions 
	box1.set(camera.position + Vector3(1,1,1),camera.position - Vector3(1,1,1));
	OBJ.push_back(box1);

	collisionOBJinit();
	collisionITEMSinit();
	collisionInteractionsinit();

	//************ Camera

	SecurityCam = false;
	cam_state = NORMAL;
	CamTime = 0 ;

	ChooseWhich = false ;

	//Inventory
	ItemsInInventory = false;
	Inventorytimer = 0;

	// Items init 
	InitItemData();
	
	ItemNo = 0;

	nullthis.Set("lol","",0); 
	InventoryData.push_back(nullthis);
	CheckoutList.push_back(nullthis);


	// cashier slider init

	ItemSlide = false;
	translateItemZ = 0 ;
	translateItemX = 0 ;
	WhichCashier = 0 ;
	Deletemah = false;

	// checklist 
	genCheckList();
	toggleCheck = false;

	ItemsStolen = 0;
	meshList[GEO_CHECKLIST] = MeshBuilder::GeneratePicture("checklist",1,1);
	meshList[GEO_CHECKLIST]->textureID = LoadTGA("image//checklist.tga");

	Mtx44 projection;
	projection.SetToPerspective(45.0f,4.0f/3.0f, 0.01f, 100000.0f);
	projectionStack.LoadMatrix(projection);


	//Music
	music = false;
}

void SceneSP::InitItemData()
{
	ifstream datafile;
	string line;

	string name , description ;

	datafile.open("ItemData.txt");

	if(datafile.is_open() )
	{ 

		while (!datafile.eof())
		{
			getline(datafile, name, ',');
			getline(datafile, description);

			CItem newitem(name, description , 0 ) ;
			ItemData.push_back(newitem);
			CheckoutList.push_back(newitem);
		}

		datafile.close();
	}
}

void SceneSP::readFontSize()
{
	ifstream datafile;
	string line;

	string name , width ;
	int WIDTH= 0;
	int counter = 0 ;

	datafile.open("fontSize.txt");

	if(datafile.is_open() )
	{ 

		while (!datafile.eof())
		{
			getline(datafile, name, ',');
			getline(datafile, width);

			WIDTH = stoi(width);

			fontSize[counter] = (float)WIDTH;

			counter++;
		}

		datafile.close();
	}
}

void SceneSP::genCheckList()
{
	checklistitem = ItemData[0] ; checklistitem.setItemCount(rand() % 11 ); // reditos
	CheckList[0] = checklistitem;

	checklistitem = ItemData[1] ; checklistitem.setItemCount(rand() % 2 ); // campbella
	CheckList[1] = checklistitem;

	checklistitem = ItemData[2] ; checklistitem.setItemCount(rand() % 9 ); // toblerone
	CheckList[2] = checklistitem;

	checklistitem = ItemData[3] ; checklistitem.setItemCount(rand() % 22 ); // dewtos
	CheckList[3] = checklistitem;

	checklistitem = ItemData[4] ; checklistitem.setItemCount(rand() % 6 ); // pizza
	CheckList[4] = checklistitem;

	checklistitem = ItemData[5] ; checklistitem.setItemCount(rand() % 2 ); // cactus juice
	CheckList[5] = checklistitem;

	checklistitem = ItemData[6] ; checklistitem.setItemCount(rand() % 5 ); // chicken soup
	CheckList[6] = checklistitem;

	checklistitem = ItemData[7] ; checklistitem.setItemCount(rand() % 6 ); // maggie mien
	CheckList[7] = checklistitem;

	checklistitem = ItemData[8] ; checklistitem.setItemCount(rand() % 12 ); // macaroni
	CheckList[8] = checklistitem;

}

void SceneSP::collisionOBJinit()
{
	//*****************************************(SKYBOX)
	box1.set(Vector3(51,51,51),Vector3(49,0,-51)); // skybox (left)
	OBJ.push_back(box1);

	box1.set(Vector3(51,51,51),Vector3(-51,0,49)); // skybox (front)
	OBJ.push_back(box1);

	box1.set(Vector3(-49,51,51),Vector3(-51,0,-51)); // skybox (right)
	OBJ.push_back(box1);

	box1.set(Vector3(51,51,-49),Vector3(-51,0,-51)); // skybox (back)
	OBJ.push_back(box1);

	//******************************************(SUPERMARKET)

	box1.set(Vector3(30,25,51),Vector3(26,0,-6)); // supermarket(left)
	OBJ.push_back(box1);

	box1.set(Vector3(30,25,51),Vector3(-26,0,47)); // supermarket (back)
	OBJ.push_back(box1);

	box1.set(Vector3(-24,25,51),Vector3(-27.5,0,-7.5)); // supermarket (right)
	OBJ.push_back(box1);

	box1.set(Vector3(-7,25,-5),Vector3(-27.5,0,-7.5)); // supermarket (front right)
	OBJ.push_back(box1);

	box1.set(Vector3(30,25,-5),Vector3(9,0,-7.5)); // supermarket (front left)
	OBJ.push_back(box1);


	// *************************************(BLOCKAGE)
	box1.set(Vector3(-7,10,2),Vector3(-8.2,0,-6)); // block right 
	OBJ.push_back(box1);

	box1.set(Vector3(10,10,0),Vector3(9.3,0,-6)); // block left
	OBJ.push_back(box1);

	// ************************************(DETECTORS)
	box1.set(Vector3(-2.5,10,-1),Vector3(-4,0,-4)); // detector right
	OBJ.push_back(box1);

	box1.set(Vector3(6,10,-1),Vector3(4.5,0,-4)); // detector left
	OBJ.push_back(box1);

	//****************************************(CASHIERS)
	box1.set(Vector3(17.5,10,6.5),Vector3(12,0,4)); // right cashier part 1 
	OBJ.push_back(box1);

	box1.set(Vector3(15,10,13),Vector3(12,0,4)); // right cashier part 2 
	OBJ.push_back(box1);

	box1.set(Vector3(27,10,6.5),Vector3(21,0,4)); // left cashier part 1
	OBJ.push_back(box1);

	box1.set(Vector3(24.5,10,13),Vector3(21,0,4)); // left cashier part 2 
	OBJ.push_back(box1);

	// ************************************** ( right side shelves )
	box1.set(Vector3(-19.5,20,8.5),Vector3(-27,0,-1.5)); // front shelf  
	OBJ.push_back(box1);

	box1.set(Vector3(-19.5,20,20),Vector3(-27,0,9.5)); // back shelf
	OBJ.push_back(box1);

	// ************************************** ( shelf right at the back )
	box1.set(Vector3(5,20,49),Vector3(-5,0,42)); // way back shelf
	OBJ.push_back(box1);

	// *************************************  ( center shelves  )
	box1.set(Vector3(18,20,33),Vector3(11,0,22)); // left shelf 
	OBJ.push_back(box1);

	box1.set(Vector3(5,20,33),Vector3(-2,0,22)); // middle shelf 
	OBJ.push_back(box1);

	box1.set(Vector3(-8,20,33),Vector3(-15.5,0,22)); // right shelf 
	OBJ.push_back(box1);

	// ***************************************** ( center small shelves )
	box1.set(Vector3(17,20,23),Vector3(13,0,19)); // left shelf 
	OBJ.push_back(box1);

	box1.set(Vector3(4,20,23),Vector3(-0.5,0,19)); // middle shelf 
	OBJ.push_back(box1);

	box1.set(Vector3(-9.5,20,23),Vector3(-13.5,0,19)); // right shelf 
	OBJ.push_back(box1);

	// ***************************************** ( toilet ) 
	box1.set(Vector3(17.5,20,49),Vector3(15.8,0,36.8)); // right wall 
	OBJ.push_back(box1);

	box1.set(Vector3(29,20,38.5),Vector3(21.8,0,36.8)); // front left wall 
	OBJ.push_back(box1);

	box1.set(Vector3(18,20,38.5),Vector3(15.8,0,36.8)); // front right wall 
	OBJ.push_back(box1);

	// ******************************************* ( security room )
	box1.set(Vector3(-8.6,20,49),Vector3(-11,0,36.8)); // left wall 
	OBJ.push_back(box1);

	box1.set(Vector3(-8.6,20,39),Vector3(-11.3,0,36.8)); // front left wall 
	OBJ.push_back(box1);

	box1.set(Vector3(-16,20,39),Vector3(-26,0,36.8)); // front right wall 
	OBJ.push_back(box1);
}

void SceneSP::collisionITEMSinit()
{
	// ******************************** (left shelf)
	for ( float x = 0.0f ; x < 2 ; x++ ) 
	{
		for ( float y = 0.0f ; y < 3 ; y++ )
		{
			for ( float z = 0.0f ; z < 3 ; z++ )
			{
				box1.set(Vector3(17.0f - x * 3.0f ,6.3f - y * 2.0f ,30.5f - z * 2.3f ),Vector3(15.5f - x * 3.0f ,5.3f - y * 2.0f ,29.0f - z * 2.3f));
				Items.push_back(box1);
			}
		}
	}

	//*********************************(middle shelf)
	// top shelf
	for ( float x = 0 ; x < 3 ; x++ )
	{
		box1.set(Vector3(4.3,6,31 - x * 3 ),Vector3(3,5.2,29 - x * 3 ));
		Items.push_back(box1);
	}
	// middle and bottom 
	for ( float y = 0 ; y < 2 ; y++ ) 
	{
		box1.set(Vector3(4,4.1 - y * 2.5 ,31.5 ),Vector3(3,3 - y * 2.5 ,29.5));
		Items.push_back(box1);
		box1.set(Vector3(4,4.1 - y * 2.5 ,28.5 ),Vector3(3,3 - y * 2.5 ,27));
		Items.push_back(box1);
		box1.set(Vector3(4,4.1 - y * 2.5 ,26.2 ),Vector3(3,3 - y * 2.5 ,24.5));
		Items.push_back(box1);
	}

	// ******************** other side + right shelf's other side 
	for ( float z = 0 ; z < 2 ; z++)
	{
		for ( float y = 0 ; y < 3 ; y++)
		{
			for ( float x = 0 ; x < 3 ; x++ )
			{
				box1.set(Vector3(0.5 - z * 13,6 - y * 1.5 , 25.5 + x * 2.5),Vector3(-0.5 - z * 13 ,5 - y * 1.5 , 24.5 + x * 2.5));
				Items.push_back(box1);
			}
		}
	}
	// ************************* right side shelf 
	for ( float y = 0 ; y < 3 ; y++ )
	{
		if ( y == 0 ) 
		{
			box1.set(Vector3(-9.5,6 - y * 1.5,31),Vector3(-10.5,5 - y * 1.5,29));
			Items.push_back(box1);
			box1.set(Vector3(-9.5,6 - y * 1.5,28.5),Vector3(-10.5,5 - y * 1.5,27.5));
			Items.push_back(box1);
			box1.set(Vector3(-9.5,6 - y * 1.5,26),Vector3(-10.5,5 - y * 1.5,23.5));
			Items.push_back(box1);
		}
		if ( y == 1 ) 
		{
			box1.set(Vector3(-9.5,6 - y * 1.5,32),Vector3(-10.5,5 - y * 1.5,29.5));
			Items.push_back(box1);
			box1.set(Vector3(-9.5,6 - y * 1.5,28.5),Vector3(-10.5,5 - y * 1.5,27.5));
			Items.push_back(box1);
			box1.set(Vector3(-9.5,6 - y * 1.5,26.5),Vector3(-10.5,5 - y * 1.5,25));
			Items.push_back(box1);
		}
		if ( y == 2 ) 
		{
			box1.set(Vector3(-9.5,6 - y * 1.5,31),Vector3(-10.5,5 - y * 1.5,29.5));
			Items.push_back(box1);
			box1.set(Vector3(-9.5,6 - y * 1.5,29),Vector3(-10.5,5 - y * 1.5,26.5));
			Items.push_back(box1);
			box1.set(Vector3(-9.5,6 - y * 1.5,26),Vector3(-10.5,5 - y * 1.5,25));
			Items.push_back(box1);
		}
	}

	// ********************************* ( maggie shelves) 
	for ( float y = 0 ; y < 3 ; y++ )
	{
		for ( float x = 0 ; x < 2 ; x++ )
		{
			box1.set(Vector3(6 - x * 4,7 - y * 3 ,46 ),Vector3(1.5 - x * 4 ,5.5 - y * 3,44));
			Items.push_back(box1);
		}
	}

	//************************************ ( left display cabinet ) 
	box1.set(Vector3(16.2,4.5,22),Vector3(15.7,4,20)) ;
	Items.push_back(box1);

	for ( float y = 0 ; y < 2 ; y++)
	{
		for ( float x = 0 ; x < 2 ; x++ )
		{
			box1.set(Vector3(16.2 - x * 1.4 ,3.5 - y * 1.5 ,22),Vector3(15.7 - x * 1.4 ,2.8 - y * 1.5 ,20)) ;
			Items.push_back(box1);
		}
	}

	//************************************* ( middle display cabinet)
	for ( float y = 0 ; y < 2 ; y++)
	{
		box1.set(Vector3(2,3.7 - y * 1.5 ,21 ),Vector3(0.5,3 - y * 1.5 ,20));
		Items.push_back(box1);
	}

	//************************************ ( right display cabinet) 

	for ( float y = 0 ; y < 2 ; y++ )
	{
		box1.set(Vector3(-9.7, 5 - y * 1.4 ,21.5 ),Vector3(-10.7, 4 - y * 1.4 ,21));
		Items.push_back(box1);
	}

	//******************************** ( right side pizza shelf part 1 ) 
	box1.set(Vector3(-20, 4.4 , 17 ),Vector3(-23.5, 3.95 ,14.5));
	Items.push_back(box1);

	box1.set(Vector3(-20, 3.9 , 13.5 ),Vector3(-23.5, 3 ,11.5));
	Items.push_back(box1);

	box1.set(Vector3(-20, 2 , 17 ),Vector3(-23.5, 1.2 ,14.5));
	Items.push_back(box1);

	//******************************** ( right side pizza shelf part 2 ) 
	box1.set(Vector3(-20, 6.6 , 6.2 ),Vector3(-23.5, 5.4 ,4.3));
	Items.push_back(box1);
	box1.set(Vector3(-20, 6.6 , 2 ),Vector3(-23.5, 5.4 , 0.2 ));
	Items.push_back(box1);
	box1.set(Vector3(-20, 4.4 , 6.2 ),Vector3(-23.5, 3.95 , 4.3 ));
	Items.push_back(box1);

}

void SceneSP::collisionInteractionsinit()
{
	box1.set(Vector3(10,20,-5.5),Vector3(0.5,0,-7.5)); // left sliding door  0
	Interactables.push_back(box1);

	box1.set(Vector3(1,20,-5.5),Vector3(-8,0,-7.5)); // right sliding door  1
	Interactables.push_back(box1);

	box1.set(Vector3(29,20,49),Vector3(22.5,0,43)); // sink  2
	Interactables.push_back(box1);

	box1.set(Vector3(23,20,49),Vector3(15.8,0,42.5)); // toilet bowl   3
	Interactables.push_back(box1);

	box1.set(Vector3(-20.5,20,49),Vector3(-26,0,36.8)); // control panel    4
	Interactables.push_back(box1);

	box1.set(Vector3(16.8,20,9.3),Vector3(14.5,0,6)); // cashier1    5
	Interactables.push_back(box1);

	box1.set(Vector3(25.8,20,9.3),Vector3(23.5,0,6)); // cashier2    6
	Interactables.push_back(box1);

	box1.set(Vector3(-10.5,20,1.5),Vector3(-13.5,0,-1.5)); // security guard     7
	Interactables.push_back(box1);

	box1.set(Vector3(-8.5,20,3.5),Vector3(-15.5,0,-3.5)); // security guard warning BB
	NpcBB.push_back(box1);

	box1.set(Vector3(6.5,20,26.5),Vector3(3.5,0,23.5)); // customer     8 
	Interactables.push_back(box1);

	box1.set(PBPos + Vector3(1,20,1),PBPos - Vector3(1,4,1)); // passerby1     9 
	Interactables.push_back(box1);

	box1.set(Vector3(47.5,20,-28.5),Vector3(43.5,0,-31.5)); // passerby2     10 
	Interactables.push_back(box1);

	box1.set(Vector3(23,20,38.5),Vector3(17.8,0,36.8)); // toiletdoor 11
	Interactables.push_back(box1);

	box1.set(Vector3(-10.7,20,39),Vector3(-16,0,36.8)); // security room door 12
	Interactables.push_back(box1);

	box1.set(Vector3(15,4,13),Vector3(12,0,4)); // right cashier conveyor 13 
	Interactables.push_back(box1);

	box1.set(Vector3(24.5,4,13),Vector3(21,0,4)); // left cashier conveyor 14 
	Interactables.push_back(box1);

	box1.set(Vector3(-15,8,49),Vector3(-16,6,46)); // switch 15 
	Interactables.push_back(box1);
}

void SceneSP::initSkybox()
{
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right3.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left3.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top3.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 0.3f , 0.3f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Base.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1),1.f ,  1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front3.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f ,  1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back3.tga");

}

void SceneSP::initNPC()
{
	//NPC
	meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("Doorman", "OBJ//doorman.obj");
	meshList[GEO_DOORMAN]->textureID = LoadTGA("Image//doorman.tga");

	//Customer
	meshList[GEO_HEAD] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//head.obj");
	meshList[GEO_HEAD]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_BODY] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//body.obj");
	meshList[GEO_BODY]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_LEFTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//hand.obj");
	meshList[GEO_LEFTHAND]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_RIGHTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//hand.obj");
	meshList[GEO_RIGHTHAND]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_LEFTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//leg.obj");
	meshList[GEO_LEFTLEG]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_RIGHTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//leg.obj");
	meshList[GEO_RIGHTLEG]->textureID = LoadTGA("image//NpcPink.tga");

	//Cashier
	meshList[GEO_CHEAD] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//head.obj");
	meshList[GEO_CHEAD]->textureID = LoadTGA("image//NpcBlue.tga");

	meshList[GEO_CBODY] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//body.obj");
	meshList[GEO_CBODY]->textureID = LoadTGA("image//NpcBlue.tga");

	meshList[GEO_CLEFTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//hand.obj");
	meshList[GEO_CLEFTHAND]->textureID = LoadTGA("image//NpcBlue.tga");

	meshList[GEO_CRIGHTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//hand.obj");
	meshList[GEO_CRIGHTHAND]->textureID = LoadTGA("image//NpcBlue.tga");

	meshList[GEO_CLEFTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//leg.obj");
	meshList[GEO_CLEFTLEG]->textureID = LoadTGA("image//NpcBlue.tga");

	meshList[GEO_CRIGHTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//leg.obj");
	meshList[GEO_CRIGHTLEG]->textureID = LoadTGA("image//NpcBlue.tga");

	//Security guard
	meshList[GEO_SHEAD] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//head.obj");
	meshList[GEO_SHEAD]->textureID = LoadTGA("image//NpcBlack.tga");

	meshList[GEO_SBODY] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//body.obj");
	meshList[GEO_SBODY]->textureID = LoadTGA("image//NpcBlack.tga");

	meshList[GEO_SLEFTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//hand.obj");
	meshList[GEO_SLEFTHAND]->textureID = LoadTGA("image//NpcBlack.tga");

	meshList[GEO_SRIGHTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//hand.obj");
	meshList[GEO_SRIGHTHAND]->textureID = LoadTGA("image//NpcBlack.tga");

	meshList[GEO_SLEFTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//leg.obj");
	meshList[GEO_SLEFTLEG]->textureID = LoadTGA("image//NpcBlack.tga");

	meshList[GEO_SRIGHTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//leg.obj");
	meshList[GEO_SRIGHTLEG]->textureID = LoadTGA("image//NpcBlack.tga");
}

void SceneSP::Update(double dt, GLFWwindow* m_window, float w, float h)
{
	glfwGetCursorPos(m_window, &xpos, &ypos);
	xposition = &xpos;
	yposition = &ypos;

	FPS = 1.0 / dt ; 
	UpdateNPC(dt);
	if(Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if(Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if(Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if(Application::IsKeyPressed('5'))
	{
		CheckListDone = true;
	}

	if (Application::IsKeyPressed(VK_SPACE) && JumpState == false)
	{

		ISound* jump = engine->play2D("../irrKlang/media/Jump2.mp3", false); // Jump duh
		JumpState = true;
		JumpDirection = true;
	}
	if (JumpState == true)
	{
		Jump(dt);
	}

	if(Application::IsKeyPressed('Z'))
	{
		music = true;
		cout << " Music Start!" << endl;
	}
	if(Application::IsKeyPressed('X'))
	{
		music = false;
		cout << "Music Stop!" << endl;
	}

	if(Application::IsKeyPressed(VK_ESCAPE) && ChooseWhich == false)
	{
		gamestate = MAINMENU;
		DetectorsOn = true;

		genCheckList();

		for ( int x = 0 ; x < InventoryData.size() ; x++ )
		{
			InventoryData[x].setItemCount(0);
		}

		for ( int x = 0 ; x < CheckoutList.size() ; x++ )
		{
			CheckoutList[x].setItemCount(0);
		}

		for ( int x = 0 ; x < 9 ; x++ )
		{
			CheckCheckOut[x] = false;
		}

		for ( int x = 0 ; x < Items.size() ; x++ )
		{
			Items[x].setEmpty(false);
		}


		Caught = false;
		CheckListDone = false;
		Alarm = false;
		ItemsInInventory = false;
		Inventorytimer = 0;
		ItemsStolen = false;
	}

	//Game states	 
	if ( gamestate == MAINMENU )
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //enable cursor
		camera.Reset();
		int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT); // check for clicks
		if( state == GLFW_PRESS && (*xposition > 285 && *xposition < 515 && *yposition > 185 && *yposition < 263) )
		{

			ISound* mainmenu = engine->play2D("../irrKlang/media/MMbutt.mp3", false); // Main main menu
			gamestate = CHOOSEMODE;
		}
		else if( state == GLFW_PRESS && (*xposition > 285 && *xposition < 515 && *yposition > 308 && *yposition < 383))
		{

			ISound* mainmenu = engine->play2D("../irrKlang/media/MMbutt.mp3", false); // Main main menu	
			exit(0);
		}

	}
	if ( gamestate == CHOOSEMODE )
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //enable cursor
		/*camera.Update(dt, w / 2, h / 2, &xpos, &ypos);*/
		int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT); // check for clicks
		if( state == GLFW_PRESS && (*xposition > 54 && *xposition < 285 && *yposition > 101 && *yposition < 179))
		{

			ISound* mainmenu = engine->play2D("../irrKlang/media/MMbutt.mp3", false); // Main main menu	
			gamestate = GAMEROAM;
			xpos = w / 2;
			ypos = h / 2;
		}
		else if( state == GLFW_PRESS && (*xposition > 54 && *xposition < 285 && *yposition > 221 && *yposition < 279))
		{
			ISound* mainmenu = engine->play2D("../irrKlang/media/MMbutt.mp3", false); // Main main menu	
			gamestate =	GAMECHECKOUT;
			xpos = w / 2;
			ypos = h / 2;
		}
		else if( state == GLFW_PRESS && (*xposition > 54 && *xposition < 285 && *yposition > 341 && *yposition < 419))
		{
			ISound* mainmenu = engine->play2D("../irrKlang/media/MMbutt.mp3", false); // Main main menu	
			gamestate = GAMETHIEF;
			xpos = w / 2;
			ypos = h / 2;
		}
		else if( state == GLFW_PRESS && (*xposition > 54 && *xposition < 285 && *yposition > 466 && *yposition < 544))
		{
			ISound* mainmenu = engine->play2D("../irrKlang/media/MMbutt.mp3", false); // Main main menu	
			gamestate = GAMEFUN;
			xpos = w / 2;
			ypos = h / 2;
		}
	}
	if ( gamestate != MAINMENU && gamestate != CHOOSEMODE && gamestate != GAMEWINCHECKOUT && gamestate != GAMEWINTHIEF && gamestate != GAMEBUSTED && gamestate != EXIT )
	{
		glfwSetCursorPos(m_window, w / 2, h / 2); // set cursor to middle
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor
		camera.Update(dt, w / 2, h / 2, &xpos, &ypos);
	}

	if ( gamestate == GAMEBUSTED )
	{
		camera.Reset();
	}

	if ( Caught == true ) // Caught by security guard in Thief Mode
	{
		gamestate = GAMEBUSTED;
	}

	if ( CheckListDone == true )
	{
		gamestate = GAMEWINCHECKOUT;
		camera.Reset();
	}
	//Entering
	if ( camera.position.z > -7 && camera.position.z < 49 && camera.position.x < 28 && camera.position.x > -27 )
	{
		inSupermarket = true;
	}
	else
	{
		inSupermarket = false;
	}

	if ( ItemsInInventory == true && inSupermarket == false && DetectorsOn == true ) // if players leave supermarket with items
	{
		Alarm = true;
		Inventorytimer += dt;
		if ( Inventorytimer > 5 && gamestate != GAMEBUSTED)
		{
			gamestate = GAMEBUSTED;
		}
	}
	if ( ItemsInInventory == true && inSupermarket == false && DetectorsOn == false && gamestate == GAMETHIEF)
	{
		gamestate = GAMEWINTHIEF;
		for ( int x = 0; x < InventoryData.size(); ++x )
		{
			ItemsStolen += InventoryData[x].getItemCount();
		}
		cout << ItemsStolen << endl;
		camera.Reset();
	}
	if ( ItemsInInventory == true && inSupermarket == true ) // if players return to the supermarket
	{
		Alarm = false;
		Inventorytimer = 0;
	}

	updatecollision(dt) ;

	//Interaction
	if(Application::IsKeyPressed('E') && PickUpItem == true && SecurityCam == false)
	{
		if ( Items[NoItemTargetcollision()].getEmpty() == false) 
			Items[NoItemTargetcollision()].setEmpty(true);

		ISound* pickup = engine->play2D("../irrKlang/media/Pickup.mp3", false); // pickup item

		updateInventory(ItemData[Items[NoItemTargetcollision()].getNo()] , true ) ;
	}

	if(Application::IsKeyPressed('Q') && PlaceItem == true && SecurityCam == false)
	{
		if ( Items[NoItemTargetcollision()].getEmpty() == true) 
		{
			for ( int x = 0 ; x < InventoryData.size() ; x++)
			{
				if ( InventoryData[x].getItemName() == ItemData[ItemTargetcollision().getNo()].getItemName() &&  InventoryData[x].getItemCount() > 0)
				{
					Items[NoItemTargetcollision()].setEmpty(false);
					updateInventory(ItemData[Items[NoItemTargetcollision()].getNo()] , false ) ;
				}
			}
		}
	}

	//Talking with NPCs & door
	if(Application::IsKeyPressed('E') && Interact == true)
	{
		if ( NoInteractableTargetcollision() == 5 || NoInteractableTargetcollision() == 6 ) // Cashier
		{
			ISound* simlish = engine->play2D("../irrKlang/media/Simlishm.mp3", false); // Npc talking
			time = 0;
			CashierText = true;
			if ( SecurityText == true)
			{
				SecurityText = false;
			}
			if ( CustomerText == true ) 
			{
				CustomerText = false;
			}
		}
		if ( NoInteractableTargetcollision() == 7 ) // Security Guard
		{
			ISound* simlish = engine->play2D("../irrKlang/media/Simlishm.mp3", false); // Npc talking
			time = 0;
			SecurityText = true;
			if ( CashierText == true)
			{
				CashierText = false;
			}
			if ( CustomerText == true ) 
			{
				CustomerText = false;
			}
		}
		if ( NoInteractableTargetcollision() == 8 || NoInteractableTargetcollision() == 9 || NoInteractableTargetcollision() == 10 )
		{

			ISound* simlish = engine->play2D("../irrKlang/media/Simlishm.mp3", false); // Npc talking
			time = 0;
			CustomerText = true;
			if ( SecurityText == true)
			{
				SecurityText = false;
			}
			if ( CashierText == true ) 
			{
				CashierText = false;
			}
		}

		if ( NoInteractableTargetcollision() == 11 && toiletDoor == false && time > 1)
		{

			ISound* door = engine->play2D("../irrKlang/media/door.mp3", false); // back doors
			//door->setIsPaused(false);
			toiletDoor = true;
			toiletDoorMove = -90;
			time = 0;
		}
		if ( NoInteractableTargetcollision() == 11 && toiletDoor == true && time > 1)
		{

			ISound* door = engine->play2D("../irrKlang/media/door.mp3", false); // back doors
			//door->setIsPaused(false);
			toiletDoor = false;
			toiletDoorMove = 0;
			time = 0;
		}
		if ( NoInteractableTargetcollision() == 12  && securityDoor == false && time > 0.5)
		{

			ISound* door = engine->play2D("../irrKlang/media/door.mp3", false); // back doors
			securityDoor = true;
			securityDoorMove = 90;
			time = 0;
		}
		if ( NoInteractableTargetcollision() == 12 && securityDoor == true && time > 0.5)
		{

			ISound* door = engine->play2D("../irrKlang/media/door.mp3", false); // back doors
			securityDoor = false;
			securityDoorMove = 0;
			time = 0;
		}

	}

	//Conveyor belt @ cashier
	if ( Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 13 && InventoryData[0].getItemCount() != 0 && ItemSlide == false || Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 14 && InventoryData[0].getItemCount() != 0 && ItemSlide == false )
	{
		ISound* checkout = engine->play2D("../irrKlang/media/Cashregister.mp3", false); //checkout
		ItemSlide = true;
		Deletemah = true;
		WhichCashier = NoInteractableTargetcollision();
	}
	//Toilet
	if(Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 2 && TapSwitch == false && TapTurn == false) //Tap water switch on
	{
		TapSwitch = true;
		TapTurn = true;
	}

	if (Application::IsKeyPressed('Q') && NoInteractableTargetcollision() == 2 && TapSwitch == true && TapTurn == true)
	{
		TapTurn = false;
		TapSwitch = false;
	}

	if(Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 3  && Flush == false ) //Flush On
	{
		ISound* flushT = engine->play2D("../irrKlang/media/flush.mp3", false); // Flush the loo loo, then eat da poo poo.
		Flush = true;
		FlushDir = true;
	}

	//Control panel
	if(Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 4 && ChooseWhich == false && gamestate != GAMEROAM) 
	{
		ChooseWhich = true;
	}

	if(Application::IsKeyPressed('G') && ChooseWhich == true && gamestate == GAMETHIEF) // choose to deactivate detectors
	{
		ISound* button = engine->play2D("../irrKlang/media/Button.mp3", false); // Main main menu	
		DetectorsOn = false;
		ChooseWhich = false;
	}

	if (Application::IsKeyPressed('T') && ChooseWhich == true ) // choose to escape 
	{
		ChooseWhich = false;
	}

	if (Application::IsKeyPressed('C') && ChooseWhich == true ) // choose camera 
	{

		ISound* cameraswitch = engine->play2D("../irrKlang/media/camera.mp3", false); // Camera switch-eroo
		StorePos = camera.position ; 
		StoreTarget1 = camera.target ;
		StoreTarget2 = camera.targetwhere;

		cam_state = CAM1;

		SecurityCam = true ;
		ChooseWhich = false;
	}

	if ( SecurityCam == true )
	{
		updateCam(dt);
	}
	//Timer for NPC text
	if ( time > 2 && CashierText == true)
	{
		CashierText = false;
	}
	if ( time > 2 && SecurityText == true)	
	{
		SecurityText = false;
	}
	if ( time > 2 && CustomerText == true)
	{
		CustomerText = false;
	}

	ItemNo = Items[NoItemTargetcollision()].getNo();

	if ( Application::IsKeyPressed('B') && time > 1) // Checklist
	{
		if ( toggleCheck == true )
			toggleCheck = false;
		else
			toggleCheck = true;

		time = 0 ;
	}

	
	if ( Application::IsKeyPressed('K')) // Randomize checklist
		genCheckList();

	if (ItemSlide == true) //Conveyor belt
		updateItemSlide(dt,WhichCashier);


	if (Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 15 && lights[0].power != 0 && lights[1].power != 0 && time > 1 )
	{

		ISound* Switch = engine->play2D("../irrKlang/media/switchoff.mp3", false); // light switch
		//SWITCH OFF
		lights[0].power = 0;
		glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);

		lights[1].power = 0;
		glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);

		time = 0 ;
	}

	if (Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 15 && lights[0].power == 0 && lights[1].power == 0 && time > 1 )
	{
		ISound* Switch = engine->play2D("../irrKlang/media/switchon.mp3", false); // light switch
		lights[0].power = 0.5;
		glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);

		lights[1].power = 2;
		glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);

		time = 0 ;
	}

	UpdateSG(dt);
	UpdateNPC(dt);
	time += dt;

	updateCheckList();

	UpdateNPC(dt);
	SlidingDoor(dt);
	//irrKlang
	Vector3 view = (camera.target - camera.position).Normalized();
	Vector3 right = view.Cross(camera.up);
	right.y = 0;
	right.Normalize();
	camera.up = right.Cross(view).Normalized();
	engine->setListenerPosition(vec3df(camera.position.x,camera.position.y,camera.position.z),vec3df(view.x,view.y,view.z),vec3df(0,0,0),vec3df(-camera.up.x,-camera.up.y,-camera.up.z));
}

int SceneSP::Renderirr()
{

	Vector3 view = (camera.target - camera.position).Normalized();
	if(!engine)
	{
		return 0;
	}

	ISound* sound = engine->play3D("../irrKlang/media/icejj.mp3",vec3df(0.f,0.f,20.f), false);

	if(sound)
	{
		engine->setDefault3DSoundMaxDistance(1000000000.f);
		sound->setMinDistance(0.f);
	}
	engine->setListenerPosition(vec3df(camera.position.x,camera.position.y,camera.position.z),vec3df(view.x,view.y,view.z),vec3df(0,0,0),vec3df(-camera.up.x,-camera.up.y,-camera.up.z));
	return 0;
}

void SceneSP::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Render VBO here

	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x,camera.position.y,camera.position.z,camera.target.x,camera.target.y,camera.target.z,camera.up.x,camera.up.y,camera.up.z);

	modelStack.LoadIdentity();

	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	if(lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else if(lights[1].type == Light::LIGHT_POINT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}


	if ( gamestate == MAINMENU )
	{
		RenderMainMenu();
	}
	else if ( gamestate == CHOOSEMODE )
	{
		RenderChooseMode();
	}
	else if ( gamestate == GAMEWINCHECKOUT )
	{
		RenderCheckoutWin();
	}
	else if ( gamestate == GAMEWINTHIEF )
	{
		RenderThiefWin();
	}
	else if ( gamestate == GAMEBUSTED )
	{
		RenderBusted();
	}
	else 
	{
		RenderSkybox();
		RenderSupermarket();
		RenderCharacter();
		RenderInteractableObjs();

		RenderInventory();

		if(music == true)
		{
			Renderirr();
			music = false;
		}

		if ( ChooseWhich == true ) 
		{
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press C to use camera", (1, 0, 1),2, 5, 4);
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press G to deactivate detectors", (1, 0, 1),2, 5, 6);
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press T to escape", (1, 0, 1),2, 5, 5);
		}
		if ( PickUpItem == true && Interact == false) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press E to pick up item", (1, 0, 1),2.5, 5, 4);
		if ( cam_state != NORMAL ) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press N for next , Y for previous", (0, 1, 0),2, 3, 4);
		if ( DetectorsOn == false)
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Detectors successfully deactivated", (0, 1, 0), 2, 3, 25);
		if ( PlaceItem == true && Interact == false) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press Q to put back item", (1, 0, 1),2.5, 5, 4);
		if (TapSwitch == true)
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press Q to turn off tap", (1, 0, 1),2.5, 5, 5);
		if ( Interact == true && ChooseWhich == false) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press E to interact", (1, 0, 1),2.5, 5, 4);

		string temp;
		string stemp;
		string ctemp;
		if ( CashierText == true )
			temp = Cashier.getType() + " : " + Cashier.CashierWelcome();
		RenderTextOnScreen(meshList[GEO_CASHIERTEXT], temp, (1, 0, 1), 1.6, 8, 23);
		if ( SecurityText == true ) 
			stemp = Guard.getType() + " : " + Guard.SSpeech();
		RenderTextOnScreen(meshList[GEO_SECURITYTEXT], stemp, (1, 0, 1), 1.6, 5, 23);
		if ( CustomerText == true )
			ctemp = Customer.getType() + " : " +  Guard.CSpeech();
		RenderTextOnScreen(meshList[GEO_CUSTOMERTEXT], ctemp, (1, 0, 1), 1.6, 13, 23);

		if ( PickUpItem == true || PlaceItem == true )
		{
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Target :" , (1, 0, 1),2, 2, 28);
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Info   :", (1, 0, 1),2, 2, 27);
			RenderTextOnScreen(meshList[GEO_MainMenuText], ItemData[ItemNo].getItemName() , (1, 0, 1),2, 10, 28);
			RenderTextOnScreen(meshList[GEO_MainMenuText], ItemData[ItemNo].getItemDesc() , (1, 0, 1),2, 10, 27);
		}

		if ( Alarm == true ) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Please return in 5 seconds", (1, 0, 1),2, 5, 16);

		if ( toggleCheck == true )
		{
			RenderPictureOnScreen(meshList[GEO_CHECKLIST],100,40,0.47,0.7);

			for ( int z = 0 ; z < 9 ; z++ )
			{
				RenderTextOnScreen(meshList[GEO_MainMenuText],CheckList[z].getItemName(), (1,0,0) , 2 , 10 , 20 - z );
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(CheckoutList[z].getItemCount()), (1,0,0) , 2 , 24 , 20 - z );
				RenderTextOnScreen(meshList[GEO_MainMenuText],"/", (1,0,0) , 2 , 26 , 20 - z );
				RenderTextOnScreen(meshList[GEO_MainMenuText],Convert(CheckList[z].getItemCount()), (1,0,0) , 2 , 27 , 20 - z );
				if ( CheckCheckOut[z] == true ) 
					RenderTextOnScreen(meshList[GEO_MainMenuText], "Done" , (1,0,0) , 2 , 30 , 20 - z );
				else
					RenderTextOnScreen(meshList[GEO_MainMenuText], "Not done" , (1,0,0) , 2 , 30 , 20 - z );

			}
		}

	}
}

void SceneSP::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}