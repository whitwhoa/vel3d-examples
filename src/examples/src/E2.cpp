#include <iostream>
#include <vector>



#include "vel/App.h"
//#include "vel/Material.h"
#include "vel/Materials.h"
#include "vel/Actor.h"


#include "E2.h"

void E2::load()
{
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