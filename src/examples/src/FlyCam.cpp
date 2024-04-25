#include <iostream>

#include "glm/gtx/string_cast.hpp"

#include "vel/App.h"


#include "FlyCam.h"


FlyCam::FlyCam(vel::Camera* worldCamera, const vel::InputState* is) :
	inputState(is),
	mouseSensitivity(is->mouseSensitivity),
	worldCamera(worldCamera), // wrong, needs camera parameter passed
	lookDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
	firstMouseInput(true),
	mouseDelta(glm::vec2(0.0f, 0.0f)),
	yaw(270.0f),
	pitch(0.0f),
	speed(5.0f){}
	

void FlyCam::immediateUpdate(float frameTime, float renderLerpTime)
{
	this->updateMouseDelta();
	this->updatePitchYaw();


	this->lookDirection.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->lookDirection.y = sin(glm::radians(this->pitch));
	this->lookDirection.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->lookDirection = glm::normalize(this->lookDirection);


	//Get normalized movement direction vectors
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::normalize(glm::cross(this->lookDirection, up));
	glm::vec3 forward = this->lookDirection;

	
	if (!this->inputState->keyLeftShift)
		this->speed = 5.0f;
	else
		this->speed = 0.5f;

	glm::vec3 tmpPos = this->worldCamera->getPosition();
	float tmpSpeed = this->speed * frameTime;

	if (this->inputState->keyW)
		tmpPos += tmpSpeed * forward;
	if (this->inputState->keyS)
		tmpPos -= tmpSpeed * forward;
	if (this->inputState->keyA)
		tmpPos -= tmpSpeed * glm::normalize(glm::cross(forward, up));
	if (this->inputState->keyD)
		tmpPos += tmpSpeed * glm::normalize(glm::cross(forward, up));

	//if (this->input.keyUp)
	//	tmpPos += tmpSpeed * forward;
	//if (this->input.keyDown)
	//	tmpPos -= tmpSpeed * forward;
	//if (this->input.keyLeft)
	//	tmpPos -= tmpSpeed * glm::normalize(glm::cross(forward, up));
	//if (this->input.keyRight)
	//	tmpPos += tmpSpeed * glm::normalize(glm::cross(forward, up));



	auto cameraPosition = tmpPos;


	this->worldCamera->setPosition(cameraPosition);
	this->worldCamera->setLookAt(cameraPosition + this->lookDirection);



	if (this->inputState->keyEnter)
	{
		std::cout << "----------------------------------------------------------------" << std::endl <<
			"Position: " << glm::to_string(cameraPosition) << std::endl <<
			"LookAt:   " << glm::to_string(cameraPosition + this->lookDirection) << std::endl;
	}
		

}

void FlyCam::fixedUpdate(float deltaTime)
{
	
}
	
void FlyCam::postPhysics(float deltaTime)
{
	
}

void FlyCam::updateMouseDelta()
{
	this->currentMousePosition.x = this->inputState->mouseXPos;
	this->currentMousePosition.y = this->inputState->mouseYPos;

	if (this->firstMouseInput)
	{
		this->lastMousePosition = this->currentMousePosition;
		this->firstMouseInput = false;
	}

	this->mouseDelta.x = this->currentMousePosition.x - this->lastMousePosition.x;
	this->mouseDelta.y = this->lastMousePosition.y - this->currentMousePosition.y;

	this->lastMousePosition = this->currentMousePosition;
}

void FlyCam::updatePitchYaw()
{
	this->yaw += this->mouseDelta.x * this->mouseSensitivity;
	this->pitch += this->mouseDelta.y * this->mouseSensitivity;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;
}