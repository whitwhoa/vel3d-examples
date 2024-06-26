#include <iostream>
#include <vector>

#include "glm/gtx/string_cast.hpp"
#include "imgui/imgui.h"

#include "vel/App.h"
#include "vel/Material.h"
#include "vel/Actor.h"


#include "E1.h"


void E1::load()
{	
	// create cameras
	vel::Camera* firstTestStageCamera = this->addCamera("firstTestStageCamera", vel::CameraType::PERSPECTIVE);
	firstTestStageCamera->setNearPlane(0.1f);
	firstTestStageCamera->setFarPlane(100.0f);
	firstTestStageCamera->setFovOrScale(75.0f);

	vel::Camera* secondTestStageCamera = this->addCamera("secondTestStageCamera", vel::CameraType::PERSPECTIVE);
	secondTestStageCamera->setNearPlane(0.1f);
	secondTestStageCamera->setFarPlane(100.0f);
	secondTestStageCamera->setFovOrScale(75.0f);
	secondTestStageCamera->setPosition(glm::vec3(0.0f, 1.5f, 1.0f));
	secondTestStageCamera->setLookAt(glm::vec3(0.0f, 1.5f, -1.0f));
	secondTestStageCamera->setFinalRenderCam(false);
	secondTestStageCamera->setResolution(426, 240);

	// create test stage, add multiple cameras
	vel::Stage* testStage = this->addStage("testStage");
	testStage->addCamera(firstTestStageCamera);
	testStage->addCamera(secondTestStageCamera);


	// Animated cube load
	vel::Texture* g17Texture = this->loadTexture("g17", "data/textures/g17");
	vel::Texture* g17ColorTexture = this->loadTexture("g17Color", "data/textures/g17_color");

	vel::Material* g17Material = this->addMaterial("g17Material");
	g17Material->addAnimatedTexture(g17Texture, 14.0f); // add texture to slot 0
	g17Material->addAnimatedTexture(g17ColorTexture, 14.0f);

	this->loadMesh("data/meshes/multi_texture_cube2.fbx");

	vel::Actor* cubeActor2 = testStage->addActor("cubeActor2");
	cubeActor2->setDynamic(true);
	cubeActor2->setVisible(true);
	cubeActor2->setShader(this->getShader("default"));
	cubeActor2->setMesh(this->getMesh("Cube2"));
	cubeActor2->setMaterial(*g17Material);
	//cubeActor2->setColor(glm::vec4(1.0f, 0.25f, 0.25f, 1.0f));
	cubeActor2->getTransform().setTranslation(glm::vec3(1.0f, 1.0f, -3.0f));
	cubeActor2->getTransform().setRotation(90.0f, glm::vec3(0.0f,1.0f,0.0f));
	


	// Multi-Textured mesh load
	vel::Texture* stoneWall1Albedo = this->loadTexture("stoneWall1Albedo", "data/textures/stone_wall_1.png");
	vel::Texture* concreteDiffuse = this->loadTexture("concreteDiffuse", "data/textures/rough_concrete.png");
	vel::Texture* gridDiffuse = this->loadTexture("gridDiffuse", "data/textures/defaults/grid.jpg");
	
	vel::Material* mapMaterial = this->addMaterial("mapMaterial");
	mapMaterial->addTexture(gridDiffuse);
	mapMaterial->addTexture(concreteDiffuse);
	mapMaterial->addTexture(stoneWall1Albedo);

	this->loadMesh("data/meshes/small_test_scene.fbx");

	vel::Actor* gridActor = testStage->addActor("gridActor");
	gridActor->setDynamic(false);
	gridActor->setVisible(true);
	gridActor->setShader(this->getShader("default"));
	gridActor->setMesh(this->getMesh("Grid"));
	gridActor->setMaterial(*mapMaterial);
	gridActor->getTransform().setRotation(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	


	// TRANSLUCENT CUBE LOAD
	vel::Material* gridMaterial = this->addMaterial("gridMaterial");
	gridMaterial->addTexture(gridDiffuse);

	this->loadMesh("data/meshes/cube.fbx");

	vel::Actor* cubeActor = testStage->addActor("cubeActor");
	cubeActor->setDynamic(false);
	cubeActor->setVisible(true);
	cubeActor->setShader(this->getShader("default"));
	cubeActor->setMesh(this->getMesh("Cube"));
	cubeActor->setMaterial(*gridMaterial);
	cubeActor->setColor(glm::vec4(1.0f, 0.25f, 0.25f, 0.25f));
	


	// ANIMATED ACTOR LOAD
	vel::Texture* lpaDiff = this->loadTexture("lpaDiff", "data/textures/low_poly_animated.jpg");

	vel::Material* lpaMat = this->addMaterial("lpaMat");
	lpaMat->addTexture(lpaDiff);
	
	this->loadMesh("data/meshes/low_poly_animated.fbx");

	vel::Actor* lpaActor = testStage->addActor("lpaActor");
	lpaActor->setDynamic(true);
	lpaActor->setVisible(true);
	lpaActor->setShader(this->getShader("defaultSkinned"));
	lpaActor->setMesh(this->getMesh("character"));
	lpaActor->setMaterial(*lpaMat);
	

	vel::Armature* arm = testStage->addArmature(this->getArmature("Armature"), "walk", { "lpaActor" });
	arm->setShouldInterpolate(false); // set to false if this armature is for animations that are not logical, ie they're not for hitboxes or something
	arm->getTransform().setRotation(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));


	// HUD STAGE
	vel::Camera* fpTestStageCamera = this->addCamera("fpTestStageCamera", vel::CameraType::ORTHOGRAPHIC);
	fpTestStageCamera->setNearPlane(-0.1f);
	fpTestStageCamera->setFarPlane(10.0f);
	fpTestStageCamera->setFovOrScale(0.665f);
	fpTestStageCamera->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	fpTestStageCamera->setLookAt(glm::vec3(0.0f, 0.0f, -1.0f));

	vel::Stage* fpTestStage = this->addStage("fpTestStage");
	fpTestStage->addCamera(fpTestStageCamera);

	vel::Material* fpFriendScreenMaterial = this->addMaterial("fpFriendScreenMaterial");
	fpFriendScreenMaterial->addTexture(&secondTestStageCamera->getRenderTarget()->texture);
	
	this->loadMesh("data/meshes/plane_16x9.fbx");

	vel::Actor* plane16x9Actor = fpTestStage->addActor("plane16x9Actor");
	plane16x9Actor->setDynamic(false);
	plane16x9Actor->setVisible(true);
	plane16x9Actor->setShader(this->getShader("defaultInvertUV"));
	plane16x9Actor->setMesh(this->getMesh("plane_16x9"));
	plane16x9Actor->setMaterial(*fpFriendScreenMaterial);
	plane16x9Actor->getTransform().setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	plane16x9Actor->getTransform().setTranslation(glm::vec3(0.9f, 0.465f, 0.0f));
	

	// Some sample text
	vel::FontBitmap* fb = this->loadFontBitmap("Teko_bold_80", 75, "data/fonts/Teko/Teko-Bold.ttf");	

	vel::TextActor* sampleTextActor = this->addTextActor(fpTestStage, "sampleTextActor", "Hello, I am some sample text...",
		fb, vel::TextActorAlignment::LEFT_ALIGN, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	sampleTextActor->actor->getTransform().setTranslation(glm::vec3(-1.15f, -0.64f, 0.0f));
	sampleTextActor->actor->getTransform().setScale(glm::vec3(0.002f, 0.002f, 0.002f));




	this->fc = std::make_unique<FlyCam>(firstTestStageCamera, this->inputState);
}


// fixed loop
void E1::fixedLoop(float deltaTime) {}

// immediate loop
void E1::immediateLoop(float frameTime, float renderLerpInterval)
{
	this->fc->immediateUpdate(frameTime, renderLerpInterval);
	
	auto lightv = this->bt.update(frameTime);
	this->getStage("testStage")->getActor("gridActor")->setColor(glm::vec4(lightv, 1.0f));

}