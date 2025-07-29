#include <iostream>
#include <vector>

#include "glm/gtx/string_cast.hpp"
#include "imgui/imgui.h"

#include "vel/App.h"
//#include "vel/Material.h"
#include "vel/Materials.h"
#include "vel/Actor.h"


#include "E1.h"

E1::E1(const std::string& dataDir) :
	isWalking(false),
	walkingSound(nullptr),
	bgm(nullptr),
	canDecreaseBGMVol(true),
	canIncreaseBGMVol(true),
	canBark(true),
	vel::Scene(dataDir)
{}

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
	//secondTestStageCamera->setResolution(64, 64);
	secondTestStageCamera->setFixedResolution(true);


	// create test stage, add multiple cameras
	vel::Stage* testStage = this->addStage("testStage");
	testStage->addCamera(firstTestStageCamera);
	testStage->addCamera(secondTestStageCamera);


	// Animated cube load
	vel::Texture* g17Texture = this->loadTexture("g17", "data/textures/g17");
	vel::Texture* g17ColorTexture = this->loadTexture("g17Color", "data/textures/g17_color");

	vel::DiffuseAnimatedMaterial* g17Material = this->addDiffuseAnimatedMaterial("g17Material", true);
	g17Material->addAnimatedTexture(g17Texture, 14.0f); // add texture to slot 0
	g17Material->addAnimatedTexture(g17ColorTexture, 14.0f);

	this->loadMesh("data/meshes/multi_texture_cube2.fbx");

	vel::Actor* cubeActor2 = testStage->addActor("cubeActor2", this->getMesh("Cube2"), g17Material);
	cubeActor2->setDynamic(true);
	cubeActor2->setVisible(true);
	//cubeActor2->setColor(glm::vec4(1.0f, 0.25f, 0.25f, 1.0f));
	cubeActor2->getTransform().setTranslation(glm::vec3(1.0f, 1.0f, -3.0f));
	cubeActor2->getTransform().setRotation(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));



	// Multi-Textured mesh load
	vel::Texture* stoneWall1Albedo = this->loadTexture("stoneWall1Albedo", "data/textures/stone_wall_1.png");
	vel::Texture* concreteDiffuse = this->loadTexture("concreteDiffuse", "data/textures/rough_concrete.png");
	vel::Texture* gridDiffuse = this->loadTexture("gridDiffuse", "data/textures/defaults/grid.jpg");

	vel::DiffuseMaterial* mapMaterial = this->addDiffuseMaterial("mapMaterial");
	mapMaterial->addTexture(gridDiffuse);
	mapMaterial->addTexture(concreteDiffuse);
	mapMaterial->addTexture(stoneWall1Albedo);

	this->loadMesh("data/meshes/small_test_scene.fbx");

	vel::Actor* gridActor = testStage->addActor("gridActor", this->getMesh("Grid"), mapMaterial);
	gridActor->setDynamic(false);
	gridActor->setVisible(true);
	gridActor->getTransform().setRotation(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));



	// TRANSLUCENT CUBE LOAD
	vel::DiffuseMaterial* gridMaterial = this->addDiffuseMaterial("gridMaterial", true);
	gridMaterial->addTexture(gridDiffuse);
	gridMaterial->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));
	//vel::RGBAMaterial* gridMaterial = this->addRGBAMaterial("redRGBAMaterial");
	//gridMaterial->setColor(glm::vec4(1.0f, 0.25f, 0.25f, 0.25f));

	this->loadMesh("data/meshes/cube.fbx");

	vel::Actor* cubeActor = testStage->addActor("cubeActor", this->getMesh("Cube"), gridMaterial);
	cubeActor->getTransform().setTranslation(glm::vec3(-0.5f, 0.0f, 0.0f));
	cubeActor->setDynamic(false);
	cubeActor->setVisible(true);


	//// CUBE WITH CAUSTIC MATERIAL
	//// License of these textures does not allow sharing, so commenting this block out so it will still run for users who do not have them
	//vel::Texture* causticTexture = this->loadTexture("causticTexture", "data/textures/water_caustics_grayscale");

	//vel::DiffuseCausticMaterial* causticMaterial1 = this->addDiffuseCausticMaterial("causticMaterial1");
	//causticMaterial1->addAnimatedTexture(causticTexture, 9.0f);
	//causticMaterial1->setSurfaceColor(glm::vec4(0.0f, 0.8f, 0.0f, 1.0f));

	//causticMaterial1->setCausticStrength(3.0f);
	//causticMaterial1->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//this->loadMesh("data/meshes/cube_1024_uv.fbx");

	//vel::Actor* causticCubeActor = testStage->addActor("causticCubeActor", this->getMesh("Cube1024"), causticMaterial1);
	//causticCubeActor->setDynamic(false);
	//causticCubeActor->getTransform().setTranslation(glm::vec3(0.0f, 1.0f, 3.0f));
	//causticCubeActor->getTransform().setScale(glm::vec3(2.0f, 2.0f, 2.0f));




	// SKINNED ACTOR LOAD
	vel::Texture* lpaDiff = this->loadTexture("lpaDiff", "data/textures/low_poly_animated.jpg");

	vel::DiffuseSkinnedMaterial* lpaMat = this->addDiffuseSkinnedMaterial("lpaMat");
	lpaMat->addTexture(lpaDiff);

	this->loadMesh("data/meshes/low_poly_animated.fbx");

	vel::Actor* lpaActor = testStage->addActor("lpaActor", this->getMesh("character"), lpaMat);
	lpaActor->setDynamic(true);
	lpaActor->setVisible(true);


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

	vel::DiffuseMaterial* fpFriendScreenMaterial = this->addDiffuseMaterial("fpFriendScreenMaterial");
	fpFriendScreenMaterial->addTexture(&secondTestStageCamera->getRenderTarget()->opaqueTexture);

	this->loadMesh("data/meshes/plane_16x9_inverted_uv_v_value.fbx");

	vel::Actor* plane16x9Actor = fpTestStage->addActor("plane16x9Actor", this->getMesh("plane_16x9"), fpFriendScreenMaterial);
	plane16x9Actor->setDynamic(false);
	plane16x9Actor->setVisible(true);
	plane16x9Actor->getTransform().setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	plane16x9Actor->getTransform().setTranslation(glm::vec3(0.9f, 0.465f, 0.0f));


	// Some sample text
	vel::FontBitmap* fb = this->loadFontBitmap("Teko_bold_80", 75, "data/fonts/Teko/Teko-Bold.ttf");

	vel::TextActor* sampleTextActor = this->addTextActor(fpTestStage, "sampleTextActor", "Hello, I am some sample text...",
		fb, vel::TextActorAlignment::LEFT_ALIGN, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	sampleTextActor->actor->getTransform().setTranslation(glm::vec3(-1.15f, -0.64f, 0.0f));
	sampleTextActor->actor->getTransform().setScale(glm::vec3(0.002f, 0.002f, 0.002f));



	this->fc = std::make_unique<FlyCam>(firstTestStageCamera, this->inputState);


	// Uncomment this for sound. You must have associated files in ./data/sounds
	/*
	// Load walking sound, set position and play in logic loop
	this->audioDevice->loadSFX("data/sounds/walking.mp3");

	// Load and play bgm
	this->audioDevice->loadBGM("data/sounds/bgm1.mp3");
	this->audioDevice->playBGM("bgm1");

	// Load bark sound
	this->audioDevice->loadSFX("data/sounds/bark.mp3");
	*/

}


// fixed loop
void E1::fixedLoop(float deltaTime) {}

// immediate loop
void E1::immediateLoop(float frameTime, float renderLerpInterval)
{
	this->fc->immediateUpdate(frameTime, renderLerpInterval);
	
	// Demonstrate altering color property of a material
	// auto lightv = this->bt.update(frameTime);
	// this->getStage("testStage")->getActor("gridActor")->getMaterial()->setColor(glm::vec4(lightv, 1.0f));

	// Uncomment this for sound. You must have associated files in ./data/sounds
	/*
	this->audioDevice->setDevicePosition(this->fc->getPosition());
	this->audioDevice->setDeviceDirection(this->fc->getDirection());

	if (!this->isWalking)
	{
		this->walkingSound = this->audioDevice->play3DSFX("walking", glm::vec3(0.0f), false, true);
		this->isWalking = true;
	}

	// Background music sound volume adjustment
	if (this->inputState->keyDown && this->canDecreaseBGMVol)
	{
		this->canDecreaseBGMVol = false;
		float currentVol = this->audioDevice->getBGMVolume();
		this->audioDevice->setBGMVolume(currentVol - 0.1f);
	}
	if (!this->inputState->keyDown && !this->canDecreaseBGMVol)
		this->canDecreaseBGMVol = true;

	if (this->inputState->keyUp && this->canIncreaseBGMVol)
	{
		this->canIncreaseBGMVol = false;
		float currentVol = this->audioDevice->getBGMVolume();
		if(currentVol + 0.1f <= 1.0f)
			this->audioDevice->setBGMVolume(currentVol + 0.1f);
	}
	if (!this->inputState->keyUp && !this->canIncreaseBGMVol)
		this->canIncreaseBGMVol = true;

	if (this->inputState->keySpace && this->canBark)
	{
		this->canBark = false;
		this->audioDevice->play2DOneShotSFX("bark");
	}
	if (!this->inputState->keySpace && !this->canBark)
		this->canBark = true;
	*/
	
}