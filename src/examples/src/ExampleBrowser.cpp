
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

	if (!this->canSwap && !is->key1  && !is->key2
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



}