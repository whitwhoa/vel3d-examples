
#include "ExampleBrowser.h"


ExampleBrowser::ExampleBrowser(vel::Config conf, vel::Window* w, vel::GPU* gpu, vel::AssetManager* am) :
	vel::App(conf, w, gpu, am)
{}

ExampleBrowser::~ExampleBrowser(){}

void ExampleBrowser::update()
{	
	const vel::InputState* is = this->getInputState();



	if (is->keyEscape)
		this->close();
}