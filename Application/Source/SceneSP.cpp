#include <iostream>
#include "SceneSP.h"

using namespace std;

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

#define LSPEED 20.f 

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
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights"); //in case you missed out practical 7
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

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

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	//Initialize camera settings
	camera.Init(Vector3(0, 6, -40), Vector3(0, 6, 0), Vector3(0, 1, 0));

	//After gluseprogram
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	//Inits
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_MainMenuScreen] = MeshBuilder::GenerateQuad("main menu screen", Color(1, 0, 0), 100, 100);
	meshList[GEO_MainMenuScreen]->textureID = LoadTGA("Image//MainMenu.tga");

	meshList[GEO_ChooseScreen] = MeshBuilder::GenerateQuad("choose mode screen", Color(1, 1, 1), 1, 1);
	meshList[GEO_ChooseScreen]->textureID = LoadTGA("Image//PlayScreen.tga");

	initSkybox();

	//TEXT
	meshList[GEO_MainMenuText] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_MainMenuText]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_NPCText] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_NPCText]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_SUPERMARKET] = MeshBuilder::GenerateOBJ("Supermarket", "OBJ//Supermarket.obj");
	meshList[GEO_SUPERMARKET]->textureID = LoadTGA("Image//WallTxt.tga");

	meshList[GEO_CUSTOMERTEXT] = MeshBuilder::GenerateText("Customer text", 16, 16);
	meshList[GEO_CUSTOMERTEXT]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_CASHIERTEXT] = MeshBuilder::GenerateText("Cashier text", 16, 16);
	meshList[GEO_CASHIERTEXT]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_SECURITYTEXT] = MeshBuilder::GenerateText("Security guard text", 16, 16);
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

	// inventory init 

	meshList[GEO_INVENTORY] = MeshBuilder::GenerateText("Slots",1,1);
	meshList[GEO_INVENTORY]->textureID = LoadTGA("image//Inventory.tga");

	meshList[GEO_TOBLERONE] = MeshBuilder::GenerateText("toblerone",1,1);
	meshList[GEO_TOBLERONE]->textureID = LoadTGA("image//InvenToblerone.tga");

	meshList[GEO_MACARONI] = MeshBuilder::GenerateText("macaroni",1,1);
	meshList[GEO_MACARONI]->textureID = LoadTGA("image//Macaroni.tga");

	meshList[GEO_REDITOS] = MeshBuilder::GenerateText("reditos",1,1);
	meshList[GEO_REDITOS]->textureID = LoadTGA("image//Reditos.tga");

	meshList[GEO_CAMPBELLA] = MeshBuilder::GenerateText("campbella",1,1);
	meshList[GEO_CAMPBELLA]->textureID = LoadTGA("image//campbella.tga");

	meshList[GEO_CACTUS] = MeshBuilder::GenerateText("cactus",1,1);
	meshList[GEO_CACTUS]->textureID = LoadTGA("image//CactusJuice.tga");

	meshList[GEO_CHICKEN] = MeshBuilder::GenerateText("chicken",1,1);
	meshList[GEO_CHICKEN]->textureID = LoadTGA("image//Chicken.tga");

	meshList[GEO_PIZZA] = MeshBuilder::GenerateText("pizza",1,1);
	meshList[GEO_PIZZA]->textureID = LoadTGA("image//Pizza.tga");

	meshList[GEO_MAGGI] = MeshBuilder::GenerateText("maggi",1,1);
	meshList[GEO_MAGGI]->textureID = LoadTGA("image//Maggi.tga");

	meshList[GEO_DEWTOS] = MeshBuilder::GenerateText("dewtos",1,1);
	meshList[GEO_DEWTOS]->textureID = LoadTGA("image//Dewtos.tga");

	//variables
	gamestate = MAINMENU;

	inSupermarket = false;
	CashierText = false;
	DetectorsOn = true;

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
	interactmah = false;

	JumpDirection = false;
	JumpState = false;

	//**********************************************************   collisions 
	box1.set(camera.position + Vector3(1,1,1),camera.position - Vector3(1,1,1));
	OBJ.push_back(box1);

	collisionOBJinit();
	collisionITEMSinit();
	collisionInteractionsinit();

	SecurityCam = false;
	cam_state = NORMAL;
	CamTime = 0 ;

	ChooseWhich = false ;

	CItem reditos("Reditos" , "red color lai de",0); ItemData.push_back(reditos);
	CItem campbella("Campbella" , " campmes" ,0); ItemData.push_back(campbella);
	CItem toblerone("Toblerone" ,  " sadsad " ,0 ); ItemData.push_back(toblerone);
	CItem dewtos("Dewtos" , "sadadsasd" ,0); ItemData.push_back(dewtos);
	CItem pizza("Pizza" , "asdasddsadsad" ,0); ItemData.push_back(pizza);
	CItem cactus("Cactus juice" , "1254321532" ,0); ItemData.push_back(cactus);
	CItem chicken("Chicken soup" ,  "sadsadsad" ,0); ItemData.push_back(chicken);
	CItem maggi("Maggie mien" ,  "sadsafgew" ,0); ItemData.push_back(maggi);
	CItem macaroni("Macaroni" ,  "sadsadsadsada" ,0); ItemData.push_back(macaroni);

	ItemNo = 0;

	nullthis.Set("lol","",0); 
	InventoryData.push_back(nullthis);
	CheckoutList.push_back(nullthis);

	ItemSlide = false;
	translateItemZ = 0 ;
	translateItemX = 0 ;
	WhichCashier = 0 ;
	Deletemah = false;

	Mtx44 projection;
	projection.SetToPerspective(45.0f,4.0f/3.0f, 0.01f, 100000.0f);
	projectionStack.LoadMatrix(projection);

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

	box1.set(Vector3(29,20,38.5),Vector3(22,0,36.8)); // front left shelf 
	OBJ.push_back(box1);

	box1.set(Vector3(18,20,38.5),Vector3(15.8,0,36.8)); // front right shelf 
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

	box1.set(Vector3(6.5,20,26.5),Vector3(3.5,0,23.5)); // customer     8 
	Interactables.push_back(box1);

	box1.set(Vector3(-43.5,20,-13.5),Vector3(-47.5,0,-16.5)); // passerby1     9 
	Interactables.push_back(box1);

	box1.set(Vector3(47.5,20,-28.5),Vector3(43.5,0,-31.5)); // passerb2     10 
	Interactables.push_back(box1);

	box1.set(Vector3(15,4,13),Vector3(12,0,4)); // right cashier conveyor 11 
	Interactables.push_back(box1);

	box1.set(Vector3(24.5,4,13),Vector3(21,0,4)); // left cashier conveyor 12 
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

void SceneSP::Update(double dt, GLFWwindow* m_window, float w, float h)
{
	glfwGetCursorPos(m_window, &xpos, &ypos);
	xposition = &xpos;
	yposition = &ypos;

	FPS = 1.0 / dt ; 

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

	if(Application::IsKeyPressed('6'))
	{
		gamestate = MAINMENU;
	}

	if (Application::IsKeyPressed(VK_SPACE) && JumpState == false)
	{
		JumpState = true;
		JumpDirection = true;
	}

	if (JumpState == true)
		Jump(dt);

	if(Application::IsKeyPressed('8'))
	{
		//SWITCH OFF
		lights[0].power = 0.5;
		glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	}

	if(Application::IsKeyPressed('9'))
	{
		//SWITCH OFF
		lights[0].power = 0;
		glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	}

	//Game states	 
	if ( gamestate == MAINMENU )
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //enable cursor
		camera.Reset();
		int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT); // check for clicks
		if( state == GLFW_PRESS && (*xposition > 285 && *xposition < 515 && *yposition > 185 && *yposition < 263) )
		{
			gamestate = CHOOSEMODE;
		}
		if( state == GLFW_PRESS && (*xposition > 285 && *xposition < 515 && *yposition > 308 && *yposition < 383) )
		{
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
			gamestate = GAMEROAM;
			xpos = w / 2;
			ypos = h / 2;
		}
		if( state == GLFW_PRESS && (*xposition > 54 && *xposition < 285 && *yposition > 221 && *yposition < 279))
		{
			gamestate =	GAMECHECKOUT;
			xpos = w / 2;
			ypos = h / 2;
		}
		if( state == GLFW_PRESS && (*xposition > 54 && *xposition < 285 && *yposition > 341 && *yposition < 419))
		{
			gamestate = GAMETHIEF;
			xpos = w / 2;
			ypos = h / 2;
		}
		if( state == GLFW_PRESS && (*xposition > 54 && *xposition < 285 && *yposition > 466 && *yposition < 544))
		{
			gamestate = GAMEFUN;
			xpos = w / 2;
			ypos = h / 2;
		}
	}

	if ( gamestate != MAINMENU && gamestate != CHOOSEMODE && gamestate != EXIT)

	{
		glfwSetCursorPos(m_window, w / 2, h / 2); // set cursor to middle
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor
		camera.Update(dt, w / 2, h / 2, &xpos, &ypos);
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

	updatecollision(dt) ;
	//Interaction functions

	SlidingDoor(dt);

	if(Application::IsKeyPressed('E') && PickUpItem == true && SecurityCam == false)
	{
		if ( Items[NoItemTargetcollision()].getEmpty() == false) 
			Items[NoItemTargetcollision()].setEmpty(true);

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

	if(Application::IsKeyPressed('E') && interactmah == true )
	{
		if ( NoInteractableTargetcollision() == 5 || NoInteractableTargetcollision() == 6 ) // Cashier
		{
			time = 0;
			CashierText = true;
		}
		if ( NoInteractableTargetcollision() == 7 ) // Security Guard
		{
			time = 0;
			SecurityText = true;
		}
		if ( NoInteractableTargetcollision() == 8 || NoInteractableTargetcollision() == 9 || NoInteractableTargetcollision() == 10 )
		{
			time = 0;
			CustomerText = true;
		}


	}


	if(Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 4 && ChooseWhich == false) 
	{
		ChooseWhich = true;
	}

	// choose to deactivate detectors
	if(Application::IsKeyPressed('E') && ChooseWhich == true )
	{
		DetectorsOn = false;
	}

	if (Application::IsKeyPressed('T') && ChooseWhich == true ) // choose to escape 
	{
		ChooseWhich = false;
	}

	if (Application::IsKeyPressed('C') && ChooseWhich == true ) // choose camera 
	{
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


	time += dt;
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

	ItemNo = Items[NoItemTargetcollision()].getNo() ;


	if ( Application::IsKeyPressed('V'))
	{
		for ( int x = 0; x < CheckoutList.size() ; x++ )
		{
			cout << CheckoutList[x].getItemName() << " " << CheckoutList[x].getItemCount() << endl;
		}
	}

	if ( Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 11 && InventoryData[0].getItemCount() != 0 && ItemSlide == false || Application::IsKeyPressed('E') && NoInteractableTargetcollision() == 12 && InventoryData[0].getItemCount() != 0 && ItemSlide == false )
	{
		ItemSlide = true;
		Deletemah = true;
		WhichCashier = NoInteractableTargetcollision();
	}

	if (ItemSlide == true)
		updateItemSlide(dt,WhichCashier);


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

	if ( gamestate == MAINMENU )
	{
		RenderMainMenu();
	}
	else if ( gamestate == CHOOSEMODE )
	{
		RenderChooseMode();
	}
	else 
	{
		RenderSkybox();
		RenderSupermarket();
		RenderCharacter();
		RenderInteractableObjs();

		RenderInventory();

		if ( ChooseWhich == true ) 
		{
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press C to use camera", (1, 0, 1),2.5, 5, 4);
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press SuiBian to use camera", (1, 0, 1),2.5, 5, 6);
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press T to escape", (1, 0, 1),2.5, 5, 5);
		}
		if ( PickUpItem == true ) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press E to pick up item", (1, 0, 1),2.5, 5, 4);

		if ( cam_state != NORMAL ) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press N for next , Y for previous", (0, 1, 0),2, 3, 4);

		if ( PlaceItem == true ) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press Q to put back item", (1, 0, 1),2.5, 5, 4);

		if ( interactmah == true && ChooseWhich == false) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "Press E to interact", (1, 0, 1),2.5, 5, 4);

		if ( CashierText == true )
			RenderTextOnScreen(meshList[GEO_CASHIERTEXT], Cashier.CashierWelcome(), (1, 0, 1), 2, 2, 5);
		if ( SecurityText == true ) 
			RenderTextOnScreen(meshList[GEO_SECURITYTEXT], Guard.SSpeech(), (1, 0, 1), 2, 2, 5);
		if ( CustomerText == true )
			RenderTextOnScreen(meshList[GEO_CUSTOMERTEXT], Customer.CSpeech(), (1, 0, 1), 2, 2, 5);

		if ( PickUpItem == true || PlaceItem == true )
		{
			RenderTextOnScreen(meshList[GEO_MainMenuText], ItemData[ItemNo].getItemName() , (1, 0, 1),2.5, 2, 20);
			RenderTextOnScreen(meshList[GEO_MainMenuText], ItemData[ItemNo].getItemDesc() , (1, 0, 1),2.5, 2, 19);
		}

	}
}

void SceneSP::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}