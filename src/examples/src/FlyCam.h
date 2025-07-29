
#include "glm/glm.hpp"

#include "vel/InputState.h"
#include "vel/Stage.h"
#include "vel/Camera.h"
#include "vel/Actor.h"


class FlyCam
{
private:
	const vel::InputState*			inputState;
	float							mouseSensitivity;
	vel::Camera*					worldCamera;
	glm::vec3						lookDirection;
	bool							firstMouseInput;
	glm::vec2						lastMousePosition;
	glm::vec2						currentMousePosition;
	glm::vec2						mouseDelta;
	float							yaw;
	float							pitch;
	float							speed;
	void							updateMouseDelta();
	void							updateRotation(float frameTime, float renderLerpInterval);
	void							updatePitchYaw();
	
public:
									FlyCam(vel::Camera* worldCamera, const vel::InputState* is);
	void							fixedUpdate(float deltaTime);
	void							immediateUpdate(float frameTime, float renderLerpTime);
	void							postPhysics(float deltaTime);

	glm::vec3						getPosition();
	glm::vec3						getDirection();
};