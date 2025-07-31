#include <iostream>
#include <vector>



#include "vel/App.h"
//#include "vel/Material.h"
#include "vel/Materials.h"
#include "vel/Actor.h"


#include "E2.h"

void E2::load()
{
	vel::Camera* bgCam = this->addCamera("bgCam", vel::CameraType::ORTHOGRAPHIC);
	bgCam->setNearPlane(-0.1f);
	bgCam->setFarPlane(10.0f);
	bgCam->setFovOrScale(0.45f);
	bgCam->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	bgCam->setLookAt(glm::vec3(0.0f, 0.0f, -1.0f));

	vel::Stage* bgStage = this->addStage("bgStage");
	bgStage->addCamera(bgCam);

	this->loadMesh("data/meshes/plane_16x9_inverted_uv_v_value.fbx");

	vel::DiffuseMaterial* bgMaterialDefault = this->addDiffuseMaterial("bgMaterial");
	bgMaterialDefault->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

	vel::Actor* plane16x9Actor = this->getStage("bgStage")->addActor("plane16x9Actor", this->getMesh("plane_16x9"), bgMaterialDefault);
	plane16x9Actor->setDynamic(false);
	plane16x9Actor->setVisible(true);
	plane16x9Actor->getTransform().setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	plane16x9Actor->getTransform().setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	// Example of using texture from another scene's FinalRenderTarget. Prerequisite being that that
	// scene will remain in memory for the duration of this scene's lifetime (avoids full texture copy,
	// useful for something that will be swapped between frequently. I implemented it to be able to show
	// one scene in a pause screen sceen)
	vel::DiffuseMaterial* bgMaterial = this->addDiffuseMaterial("bgMaterial");
	bgMaterial->addTexture(&this->e1RenderTarget->texture);
	bgMaterial->setColor(glm::vec4(0.25f, 0.25f, 0.25f, 1.0f));
	plane16x9Actor->setMaterial(bgMaterial);

	// Used in copy texture example
	vel::DiffuseMaterial* bgMaterial2 = this->addDiffuseMaterial("bgMaterial2");
	bgMaterial2->setColor(glm::vec4(0.25f, 0.25f, 0.25f, 1.0f));

	
	
	


	vel::Camera* fpTestStageCamera = this->addCamera("fpTestStageCamera", vel::CameraType::ORTHOGRAPHIC);
	fpTestStageCamera->setNearPlane(-0.1f);
	fpTestStageCamera->setFarPlane(10.0f);
	fpTestStageCamera->setFovOrScale(0.665f);
	fpTestStageCamera->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	fpTestStageCamera->setLookAt(glm::vec3(0.0f, 0.0f, -1.0f));

	vel::Stage* fpTestStage = this->addStage("fpTestStage");
	fpTestStage->addCamera(fpTestStageCamera);

	vel::FontBitmap* fb = this->loadFontBitmap("Teko_bold_80", 75, "data/fonts/Teko/Teko-Bold.ttf");

	vel::TextActor* sampleTextActor = this->addTextActor(fpTestStage, "anotherTextActor", "This is another Scene...",
		fb, vel::TextActorAlignment::CENTER_ALIGN, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	sampleTextActor->actor->getTransform().setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));
	sampleTextActor->actor->getTransform().setScale(glm::vec3(0.002f, 0.002f, 0.002f));
}


// fixed loop
void E2::fixedLoop(float deltaTime) {}

// immediate loop
void E2::immediateLoop(float frameTime, float renderLerpInterval) {}

void E2::updateBackgroundFromCopy()
{
	// Example using texture that was coppied from E1 into an empty texture held by E2. This would be
	// useful for the situation where you want to unload the previous scene in the current scene
	// (Put this into it's own function so that it can be called when we do the scene swap since this scene
	// is already loaded into memory and the load method has already been called)
	
	if(!this->e1TextureCopy)
		this->getMaterial("bgMaterial2")->addTexture(this->e1TextureCopy.get());

	
}