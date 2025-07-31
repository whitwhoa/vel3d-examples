#pragma once


#include "vel/Scene.h"


class E2 : public vel::Scene
{
public:
	E2(const std::string& dataDir, vel::GPU* gpu) : 
		e1RenderTarget(nullptr),
		e1TextureCopy(nullptr),
		vel::Scene(dataDir, gpu) {};

	void    load();
	void	fixedLoop(float deltaTime);
	void	immediateLoop(float frameTime, float renderLerpInterval);

	vel::FinalRenderTarget* e1RenderTarget; // demo usage of another scene's render target texture
	std::unique_ptr<vel::Texture> e1TextureCopy; // demo copying of another scene's rener target texture

	void updateBackgroundFromCopy();

};