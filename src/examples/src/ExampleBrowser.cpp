
#include "E1.h"
#include "E2.h"

#include "ExampleBrowser.h"


ExampleBrowser::ExampleBrowser(vel::Config conf, vel::Window* w, vel::GPU* gpu, vel::AssetManager* am) :
	canSwap(true),
	swapSceneName(""),
	vel::App(conf, w, gpu, am)
{}

ExampleBrowser::~ExampleBrowser(){}

void ExampleBrowser::update()
{	
	const vel::InputState* is = this->getInputState();

	if (is->keyEscape)
		this->close();

	if (!this->canSwap && !is->key1  && !is->key2 && !is->key3
		&& this->swapSceneName == this->activeScene->getName())
	{
		this->canSwap = true;
		this->swapSceneName = "";
	}

	if (this->canSwap && is->key1)
	{
		this->canSwap = false;
		this->swapSceneName = "E1";
		this->swapScene(this->swapSceneName);
	}

	if (this->canSwap && is->key2)
	{
		this->canSwap = false;
		this->swapSceneName = "E2";
		this->swapScene(this->swapSceneName);
	}

	if (this->canSwap && is->key3)
	{
		this->canSwap = false;
		this->swapSceneName = "E2";

		unsigned int width = this->activeScene->getResolution().x;
		unsigned int height = this->activeScene->getResolution().y;

		E1* e1 = (E1*)this->getScene("E1");
		E2* e2 = (E2*)this->getScene("E2");

		this->gpu->copyGPUTexture(e1->getSceneRenderTarget()->texture.frames.at(0).id, e2->e1TextureCopy->frames.at(0).id, width, height);

		e2->updateBackgroundFromCopy();

		this->swapScene(this->swapSceneName);
	}



}