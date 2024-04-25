#include "InputStateGenerator.h"

#include "vel/App.h"

#include <iostream>

InputStateGenerator::InputStateGenerator(const vel::InputState* vis) :
	input(vis),
	mouseSensitivity(vis->mouseSensitivity),
	inputState(InputState()),
	firstMouseInput(true),
	mouseDelta(glm::vec2(0.0f, 0.0f)),
	yaw(0.0f),
	pitch(0.0f)
{
	
}

void InputStateGenerator::setYaw(float y)
{
	this->yaw = y;
}

void InputStateGenerator::setPitch(float p)
{
	this->pitch = p;
}

void InputStateGenerator::updatePitchYaw()
{
	this->yaw += this->mouseDelta.x * this->mouseSensitivity;
	this->pitch += this->mouseDelta.y * this->mouseSensitivity;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;
}

void InputStateGenerator::updateMouseDelta()
{
	this->currentMousePosition.x = this->input->mouseXPos;
	this->currentMousePosition.y = this->input->mouseYPos;

	if (this->firstMouseInput)
	{
		this->lastMousePosition = this->currentMousePosition;
		this->firstMouseInput = false;
	}

	this->mouseDelta.x = this->currentMousePosition.x - this->lastMousePosition.x;
	this->mouseDelta.y = this->lastMousePosition.y - this->currentMousePosition.y;

	this->lastMousePosition = this->currentMousePosition;
}

void InputStateGenerator::updateMouse()
{
	this->updateMouseDelta();
	this->updatePitchYaw();

	this->inputState.mousePitch = this->pitch;
	this->inputState.mouseYaw = this->yaw;
}

void InputStateGenerator::updateKeys()
{
	this->inputState.moveUp = this->input->keyW;
	this->inputState.moveLeft = this->input->keyA;
	this->inputState.moveDown = this->input->keyS;
	this->inputState.moveRight = this->input->keyD;
	this->inputState.jump = this->input->keySpace;
	this->inputState.walk = this->input->keyLeftControl;
	this->inputState.action = this->input->keyE;
	this->inputState.fireWeapon = this->input->mouseLeftButton;
}

void InputStateGenerator::immediateUpdate(float frameTime, float renderLerpTime)
{
	this->updateMouse();

}

void InputStateGenerator::fixedUpdate(float deltaTime)
{
	this->inputState.tick += 1;

	this->updateKeys();
}

InputState InputStateGenerator::getInputState()
{
	return this->inputState;
}