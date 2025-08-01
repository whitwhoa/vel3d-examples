#pragma once

#include "vel/App.h"


class ExampleBrowser : public vel::App
{
private:
	bool canSwap;
	std::string swapSceneName;

public:
	ExampleBrowser(vel::Config conf, vel::Window* w, vel::GPU* gpu, vel::AssetManager* am);
	~ExampleBrowser();

	void update();
};