#pragma once


#include "vel/Scene.h"
#include "vel/BounceTweener.h"

#include "FlyCam.h"


class E1 : public vel::Scene
{
public:
	E1() : vel::Scene() {};
	
	void    load();
	void	fixedLoop(float deltaTime);
	void	immediateLoop(float frameTime, float renderLerpInterval);


	vel::BounceTweener bt = vel::BounceTweener(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.15f, 0.15f, 0.15f), 1.0f);
	std::unique_ptr<FlyCam> fc;

};