#pragma once



struct InputState
{
	// Logical input state for gameplay. Nothing should be in this that is not absolutely required to process a simulation tick
	unsigned int tick = 0;

	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;
	bool jump = true;
	bool walk = true;
	bool fireWeapon = false;
	bool action = false;
	
	float mousePitch = 0.0f;
	float mouseYaw = 0.0f;
};