#pragma once

#include "glm/glm.hpp"

#include "vel/InputState.h"

#include "InputState.h"

/*
This class is responsible for generating an Input State object, based off of user input gathered
from vellocet library's vel::InputState (which in turn uses glfw to obtain keyboard/mouse inputs)

TODO: In the future this is where we will implement a crosswalk between keys a user has designated for the
various inputstate actions (for example moveUp is hardcoded to be "w" key, but a user might want to change
it to something else)
*/

class InputStateGenerator
{
private:
	const vel::InputState* input;
	float			mouseSensitivity;

	InputState		inputState;

	

	void			updatePitchYaw();
	void			updateMouseDelta();
	void			updateMouse();
	void			updateKeys();
	
	bool			firstMouseInput;
	glm::vec2		lastMousePosition;
	glm::vec2		currentMousePosition;
	glm::vec2		mouseDelta;
	float			yaw;
	float			pitch;

public:
					InputStateGenerator(const vel::InputState* vis);
	
	void			fixedUpdate(float deltaTime);
	void			immediateUpdate(float frameTime, float renderLerpTime);

	void			setPitch(float p);
	void			setYaw(float y);

	InputState		getInputState();

};