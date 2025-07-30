#pragma once


#include "vel/Scene.h"


class E2 : public vel::Scene
{
public:
	E2(const std::string& dataDir, vel::GPU* gpu) : 
		e1RenderTarget(nullptr),
		vel::Scene(dataDir, gpu) {};

	void    load();
	void	fixedLoop(float deltaTime);
	void	immediateLoop(float frameTime, float renderLerpInterval);

	vel::FinalRenderTarget* e1RenderTarget;

};