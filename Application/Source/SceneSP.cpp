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
	camera.Init(Vector3(0, 9, -40), Vector3(0, 9, 0), Vector3(0, 1, 0));

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

	//variables
	gamestate = MAINMENU;

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_MainMenuScreen] = MeshBuilder::GenerateQuad("main menu screen", Color(1, 0, 0), 100, 100);
	meshList[GEO_MainMenuScreen]->textureID = LoadTGA("Image//MainMenu.tga");

	meshList[GEO_ChooseScreen] = MeshBuilder::GenerateQuad("choose mode screen", Color(1, 1, 1), 1, 1);
	meshList[GEO_ChooseScreen]->textureID = LoadTGA("Image//PlayScreen.tga");

	initSkybox();


	meshList[GEO_MainMenuText] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_MainMenuText]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_SUPERMARKET] = MeshBuilder::GenerateOBJ("Supermarket", "OBJ//Supermarket.obj");
	meshList[GEO_SUPERMARKET]->textureID = LoadTGA("Image//WallTxt.tga");


	meshList[GEO_SUPERMARKETFLOOR] = MeshBuilder::GenerateOBJ("SupermarketFloor", "OBJ//SupermarketFloor.obj");
	meshList[GEO_SUPERMARKETFLOOR]->textureID = LoadTGA("Image//SupermarketTiles.tga");

	meshList[GEO_DISPLAYCABINET] = MeshBuilder::GenerateOBJ("DisplayCabinet", "OBJ//DisplayCabinet.obj");
	meshList[GEO_DISPLAYCABINET]->textureID = LoadTGA("Image//DisplayCabinet.tga");

	meshList[GEO_SCANNER] = MeshBuilder::GenerateOBJ("Scanner", "OBJ//Scanner.obj");
	meshList[GEO_SCANNER]->textureID = LoadTGA("Image//Scanner.tga");

	meshList[GEO_DIVIDER] = MeshBuilder::GenerateOBJ("Divider", "OBJ//Divider.obj");
	meshList[GEO_DIVIDER]->textureID = LoadTGA("Image//Scanner.tga");

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


	meshList[GEO_DOORMAN] = MeshBuilder::GenerateOBJ("Doorman", "OBJ//doorman.obj");
	meshList[GEO_DOORMAN]->textureID = LoadTGA("Image//doorman.tga");
//
	meshList[GEO_HEAD] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//head.obj");
	meshList[GEO_HEAD]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_BODY] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//body.obj");
	meshList[GEO_BODY]->textureID = LoadTGA("image//NpcPink.tga");
	
	meshList[GEO_LEFTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//lefthand.obj");
	meshList[GEO_LEFTHAND]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_RIGHTHAND] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//righthand.obj");
	meshList[GEO_RIGHTHAND]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_LEFTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//leftleg.obj");
	meshList[GEO_LEFTLEG]->textureID = LoadTGA("image//NpcPink.tga");

	meshList[GEO_RIGHTLEG] = MeshBuilder::GenerateOBJ("NPC head", "OBJ//rightleg.obj");
	meshList[GEO_RIGHTLEG]->textureID = LoadTGA("image//NpcPink.tga");


	translateX = 0 ;
	collision = false; 
	collisionsia = false;

	box1.set(camera.position + Vector3(1,1,1),camera.position - Vector3(1,1,1));
	OBJ.push_back(box1);

	box1.set(Vector3(translateX + 10,20,10),Vector3(translateX + -10,0,-10));
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube" , (1,0,0), box1.max.x - box1.min.x , box1.max.y - box1.min.y , box1.max.z - box1.min.z);
	OBJ.push_back(box1);


	seewhere.set(camera.targetwhere + Vector3(0.2,0.1,0.2),camera.targetwhere - Vector3(0.2,0.1,0.2));
	meshList[GEO_SEE] = MeshBuilder::GenerateCube("cube" , (0,0,0), seewhere.max.x - seewhere.min.x , seewhere.max.y - seewhere.min.y , seewhere.max.z - seewhere.min.z);

	Mtx44 projection;
	projection.SetToPerspective(45.0f,4.0f/3.0f, 0.01f, 100000.0f);
	projectionStack.LoadMatrix(projection);

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

	//Game states
	if ( gamestate == MAINMENU )
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //enable cursor
		/*camera.Update(dt, w / 2, h / 2, &xpos, &ypos);*/
		int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT); // check for clicks
		if( state == GLFW_PRESS && (*xposition > 285 && *xposition < 515 && *yposition > 185 && *yposition < 263) )
		{
			gamestate = CHOOSEMODE;
		}
		if( state == GLFW_PRESS && (*xposition > 285 && *xposition < 515 && *yposition > 308 && *yposition < 383) )
		{
			exit(0);
		}
		std::cout << xpos << std::endl;
		std::cout << ypos << std::endl;
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

	updatecollision(dt) ;

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
	else if ( gamestate == EXIT )
	{

	}
	else 
	{
		RenderSkybox();
		RenderSupermarket();
		RenderCharacter();

		RenderInteractableObjs();

		modelStack.PushMatrix();
		modelStack.Translate(translateX,10,0);
		RenderMesh(meshList[GEO_CUBE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(camera.targetwhere.x,camera.targetwhere.y,camera.targetwhere.z);
		RenderMesh(meshList[GEO_SEE], true);
		modelStack.PopMatrix();

		if ( collision == true ) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "COLLISION", (1, 0, 1),3, 2, 18);

		if ( collisionsia == true ) 
			RenderTextOnScreen(meshList[GEO_MainMenuText], "TARGET DONG DAO LIAO", (1, 0, 1),3, 2, 16);


	}

	cout << camera.targetwhere.y << endl ; 

}

void SceneSP::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}