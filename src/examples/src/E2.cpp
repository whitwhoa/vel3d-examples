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


	//vel::RGBAMaterial* bgMaterial = this->addRGBAMaterial("bgMaterial");
	//bgMaterial->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vel::DiffuseMaterial* bgMaterial = this->addDiffuseMaterial("bgMaterial");
	bgMaterial->addTexture(&this->e1RenderTarget->texture);
	//bgMaterial->setColor(glm::vec4(0.25f, 0.25f, 0.25f, 1.0f));

	this->loadMesh("data/meshes/plane_16x9_inverted_uv_v_value.fbx");

	vel::Actor* plane16x9Actor = bgStage->addActor("plane16x9Actor", this->getMesh("plane_16x9"), bgMaterial);
	plane16x9Actor->setDynamic(false);
	plane16x9Actor->setVisible(true);
	plane16x9Actor->getTransform().setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	plane16x9Actor->getTransform().setTranslation(glm::vec3(0.0f, 0.0f, 0.0f));





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