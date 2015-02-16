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

#include "RenderCharacter.h"

#define LSPEED 20.f 

SceneSP::SceneSP()
{
}

SceneSP::~SceneSP()
{
}

void SceneSP::Init()
{
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
		m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader" );
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
	camera.Init(Vector3(200, 20, 100), Vector3(0, 0, 0), Vector3(0, 1, 0));

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

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);


	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right3.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left3.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top3.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 0.3f , 0.3f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom2.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1),1.f ,  1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front3.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1),1.f ,  1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back3.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//ExportedFont.tga");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("model1", "OBJ//tree.obj");
	meshList[GEO_TREE]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_TREE]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_TREE]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_TREE]->material.kShininess = 100.f;
	meshList[GEO_TREE]->textureID = LoadTGA("Image//treee.tga");

	meshList[GEO_CASTLE] = MeshBuilder::GenerateOBJ("model1", "OBJ//castle.obj");
	meshList[GEO_CASTLE]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_CASTLE]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_CASTLE]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_CASTLE]->material.kShininess = 100.f;
	meshList[GEO_CASTLE]->textureID = LoadTGA("Image//wow.tga");

	meshList[GEO_LAMPPOST] = MeshBuilder::GenerateOBJ("model1", "OBJ//lampost.obj");
	meshList[GEO_LAMPPOST]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_LAMPPOST]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LAMPPOST]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_LAMPPOST]->material.kShininess = 100.f;
	meshList[GEO_LAMPPOST]->textureID = LoadTGA("Image//lampost.tga");

	meshList[GEO_BUSH] = MeshBuilder::GenerateOBJ("model1", "OBJ//bush.obj");
	meshList[GEO_BUSH]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_BUSH]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_BUSH]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_BUSH]->material.kShininess = 100.f;
	meshList[GEO_BUSH]->textureID = LoadTGA("Image//bush.tga");

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("model1", "OBJ//gate.obj");
	meshList[GEO_DOOR]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_DOOR]->material.kDiffuse.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_DOOR]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_DOOR]->material.kShininess = 100.f;
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//gate.tga");

	meshList[GEO_KIRBY] = MeshBuilder::GenerateOBJ("model1", "OBJ//kirby.obj");
	meshList[GEO_KIRBY]->material.kAmbient.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_KIRBY]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_KIRBY]->material.kSpecular.Set(0.4f, 0.4f,0.4f);
	meshList[GEO_KIRBY]->material.kShininess = 10.f;
	meshList[GEO_KIRBY]->textureID = LoadTGA("Image//kirby texture.tga");

	// ***************************************************************************   assignment 2 character
	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("head",Color(0,0,1) , 18  , 36 , 1.f );
	meshList[GEO_HEAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEAD]->material.kDiffuse.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_HEAD]->material.kSpecular.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_HEAD]->material.kShininess = 5.f;

	meshList[GEO_COAT] = MeshBuilder::GenerateSphere("coat",Color(1,0,0) , 18  , 36 , 1.f );
	meshList[GEO_COAT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_COAT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COAT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COAT]->material.kShininess = 5.f;

	meshList[GEO_COAT1] = MeshBuilder::GenerateSphere("coat1",Color(1,1,1) , 18  , 36 , 1.f );
	meshList[GEO_COAT1]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_COAT1]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COAT1]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COAT1]->material.kShininess = 5.f;

	meshList[GEO_BODY] = MeshBuilder::GenerateSphere("body",Color(0,0,1) , 18  , 36 , 1.f );
	meshList[GEO_BODY]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BODY]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODY]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODY]->material.kShininess = 5.f;

	meshList[GEO_BODYD1] = MeshBuilder::GenerateTriangle("bodyd1",Color(1,0,0) , 0.8 , 0.5);
	meshList[GEO_BODYD1]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BODYD1]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODYD1]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODYD1]->material.kShininess = 5.f;

	meshList[GEO_BODYD2] = MeshBuilder::GenerateTriangle("bodyd2",Color(1,1,0) , 0.8 , 0.5);
	meshList[GEO_BODYD2]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BODYD2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODYD2]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BODYD2]->material.kShininess = 5.f;

	meshList[GEO_LIMB] = MeshBuilder::GenerateSphere("limb",Color(1.5,1,0) , 36 , 36 , 1.f );
	meshList[GEO_LIMB]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_LIMB]->material.kDiffuse.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_LIMB]->material.kSpecular.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_LIMB]->material.kShininess = 5.f;

	meshList[GEO_BEAK] = MeshBuilder::GenerateSphere("beak",Color(1.5,1,0) , 2 , 3 , 1.f );
	meshList[GEO_BEAK]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BEAK]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BEAK]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BEAK]->material.kShininess = 5.f;

	meshList[GEO_EYES1] = MeshBuilder::GenerateSphere("eyes1",Color(1,1,1) , 36 , 36 , 1.f );
	meshList[GEO_EYES1]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYES1]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_EYES1]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_EYES1]->material.kShininess = 5.f;

	meshList[GEO_EYES2] = MeshBuilder::GenerateSphere("eyes2",Color(0,0,0) , 36 , 36 , 1.f );
	meshList[GEO_EYES2]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYES2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_EYES2]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_EYES2]->material.kShininess = 5.f;

	meshList[GEO_HEADT] = MeshBuilder::GenerateSphere("headt",Color(1,0,0) , 36 , 36 , 1.f );
	meshList[GEO_HEADT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEADT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADT]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADT]->material.kShininess = 5.f;

	meshList[GEO_HEADB] = MeshBuilder::GenerateSphere("headb",Color(1,1,0) , 36 , 36 , 1.f );
	meshList[GEO_HEADB]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEADB]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADB]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADB]->material.kShininess = 5.f;

	meshList[GEO_HEADBB] = MeshBuilder::GenerateSphere("headbb",Color(1,1,1) , 36 , 36 , 1.f );
	meshList[GEO_HEADBB]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEADBB]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADBB]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEADBB]->material.kShininess = 5.f;

	meshList[GEO_ARM] = MeshBuilder::GenerateCylinder("arm",Color(1,0,0) , 5 , 360 , 2 , 1.f );
	meshList[GEO_ARM]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ARM]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_ARM]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_ARM]->material.kShininess = 5.f;

	meshList[GEO_SLEEVE] = MeshBuilder::GenerateSphere("SLEEVE",Color(1,1,1) , 18  , 36 , 1.f );
	meshList[GEO_SLEEVE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SLEEVE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SLEEVE]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SLEEVE]->material.kShininess = 5.f;

	meshList[GEO_WEAP1] = MeshBuilder::GenerateCylinder("weap1",Color(0.65,0.49 , 0.24) , 5 , 360 , 2 , 1.f );
	meshList[GEO_WEAP1]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WEAP1]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WEAP1]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WEAP1]->material.kShininess = 5.f;

	meshList[GEO_WEAPRING] = MeshBuilder::GenerateCylinder("WEAPRING",Color(1,1 , 1) , 5 , 360 , 0.5 , 1.f );
	meshList[GEO_WEAPRING]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WEAPRING]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WEAPRING]->material.kSpecular.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WEAPRING]->material.kShininess = 5.f;

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("floor",Color(0,0.5,0), 1, 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kShininess = 5.f;

	meshList[GEO_STAR] = MeshBuilder::GenerateStar("star",Color(1,1,0), 1, 1);
	meshList[GEO_STAR]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_STAR]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_STAR]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_STAR]->material.kShininess = 5.f;

	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle",Color(1,0,0) ,36 , 1);
	meshList[GEO_CIRCLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CIRCLE]->material.kDiffuse.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_CIRCLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CIRCLE]->material.kShininess = 5.f;
	// end of character

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1,1,1), 10, 10,1);


	Mtx44 projection;
	projection.SetToPerspective(45.0f,4.0f/3.0f, 0.01f, 100000.0f);
	projectionStack.LoadMatrix(projection);


}


void SceneSP::Update(double dt)
{
	//hitting code 
	
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

	FPS = 1 / dt ; 


	if(Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(LSPEED * dt);


	camera.Update(dt);
}

static float ROT_LIMIT = 45.f ;
static float SCALE_LIMIT = 5.f; 

void SceneSP::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, 
			&mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}


	mesh->Render();

	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


}

void SceneSP::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneSP::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -0.1, 0.1); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
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

	RenderSkybox();

	RenderCharacter();

	modelStack.PushMatrix();
	modelStack.Scale(20,20,20);
	RenderMesh(meshList[GEO_CASTLE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(75,0,0);
	modelStack.Rotate(rotatedoor,0,0,1);
	modelStack.Scale(20,20,20);
	RenderMesh(meshList[GEO_DOOR], true);
	modelStack.PopMatrix();

	for (int x = -1 ; x < 2 ; x += 2 )
	{
		modelStack.PushMatrix();
		modelStack.Translate(125,0,150 * x);
		modelStack.Scale(6,6,6);
		RenderMesh(meshList[GEO_LAMPPOST], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(-20,10,30);
	modelStack.Scale(scalekirby,3 + (3- scalekirby),3 + (3- scalekirby));
	RenderMesh(meshList[GEO_KIRBY], true);
	modelStack.PopMatrix();

	for (int x = -500 ; x < 500 ; x += 21 )
	{
		modelStack.PushMatrix();
		modelStack.Translate(500,0,x);
		modelStack.Scale(6,4,6);
		RenderMesh(meshList[GEO_BUSH], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-500,0,x);
		modelStack.Scale(6,4,6);
		RenderMesh(meshList[GEO_BUSH], true);
		modelStack.PopMatrix();
	}

	for (int y = -500; y < 500 ; y += 30 )
	{
		modelStack.PushMatrix();
		modelStack.Translate(y,0,500);
		modelStack.Scale(6,4,6);
		RenderMesh(meshList[GEO_BUSH], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(y,0,-500);
		modelStack.Scale(6,4,6);
		RenderMesh(meshList[GEO_BUSH], true);
		modelStack.PopMatrix();
	}

	for ( int x = -1 ; x < 2 ; x ++)
	{
		int y = 0;
		if ( x == 0 ) 
			y = -300;

		modelStack.PushMatrix();
		modelStack.Translate(y,0,300 * x);
		modelStack.Scale(10,5,10);
		RenderMesh(meshList[GEO_TREE], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(20,10,40);
	modelStack.Rotate(180,0,1,0);
	RenderCharacter();
	modelStack.PopMatrix();

	

	RenderTextOnScreen(meshList[GEO_TEXT], "Press Y to turn Coordinates display on/off" , Color(1, 0, 0), 2.5 , 1.5, 2.5);

	RenderTextOnScreen(meshList[GEO_TEXT], "F P S =" , Color(1, 0, 0), 2.5, 1, 0.5);
	RenderTextOnScreen(meshList[GEO_TEXT], Convert(FPS) , Color(1, 0, 0), 2.5, 5, 0.5);

	RenderTextOnScreen(meshList[GEO_TEXT], "W ,A ,S,D to move,arrow keys to view , B to open/close door " , Color(1, 0, 0), 2.5, 1, 1.5);
	//RenderTextOnScreen(meshList[GEO_TEXT], Convert(FPS) , Color(1, 0, 0), 2.5, 5.5, 0.5);





}

void SceneSP::Exit()
{
	// Cleanup VBO here

	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}