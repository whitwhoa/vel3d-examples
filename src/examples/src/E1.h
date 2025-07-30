#pragma once


#include "vel/Scene.h"
#include "vel/BounceTweener.h"

#include "FlyCam.h"

struct ma_sound;

class E1 : public vel::Scene
{
private:
	bool isWalking;
	ma_sound* walkingSound;
	ma_sound* bgm;
	bool canDecreaseBGMVol;
	bool canIncreaseBGMVol;
	bool canBark;

public:
	E1(const std::string& dataDir, vel::GPU* gpu);
	
	void    load();
	void	fixedLoop(float deltaTime);
	void	immediateLoop(float frameTime, float renderLerpInterval);


	vel::BounceTweener bt = vel::BounceTweener(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.15f, 0.15f, 0.15f), 1.0f);
	std::unique_ptr<FlyCam> fc;

};