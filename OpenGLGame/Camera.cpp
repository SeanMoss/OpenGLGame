#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <iostream>
#include "Camera.h"

//================================================CAMERA=================================================
static Camera* playerCamera;

const Camera* Camera::GetActiveCamera()
{
	return playerCamera;
}

glm::vec3 Camera::ActiveCameraPosition()
{
	return playerCamera->GetPosition();
}

void Camera::GetBestMonitorSize(int* w, int* h)
{
	int count;
	const GLFWvidmode* mode = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
	
	int tw = 0, th = 0;
	//std::cout << "Found " << count << " video modes available on this monitor." << std::endl;
	for (int i = 0; i < count; i++)
	{
		//std::cout << "Width: " << mode[i].width << "\tHeight: " << mode[i].height << std::endl;
		if (mode[i].width > tw)
			tw = mode[i].width;
		if (mode[i].height > th)
			th = mode[i].height;
	}

	*w = tw;
	*h = th;

	//std::cout << "Using a resolution of " << *w << "," << *h << std::endl;
}

Camera::Camera(GLFWwindow* window)
{
	this->window = window;
	GetBestMonitorSize(&width, &height);

	near = 0.1f;
	far = 50000.0f;

	fov = 45;

	projection = glm::perspective(fov, GetAspectRatio(), near, far);

	playerCamera = this;
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix() const
{
	return view;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return projection;
}

float Camera::GetAspectRatio() const
{
	return float(width)/float(height);
}

void Camera::GetCurrentCameraWindowSize(int* w, int* h) const
{
	*w = width;
	*h = height;
}

void Camera::SetFOV(float newfov)
{
	fov = newfov;
	projection = glm::perspective(fov, GetAspectRatio(), near, far);
}

float Camera::GetFOV() const
{
	return fov;
}

void Camera::SetDepth(float near, float far)
{
	this->near = near;
	this->far = far;
	projection = glm::perspective(fov, GetAspectRatio(), near, far);
}

void Camera::GetDepth(float* near, float* far) const
{
	*near = this->near;
	*far = this->far;
}
//=======================================================================================================

//================================================TARGET CAMERA==========================================
TargetCamera::TargetCamera(GLFWwindow* window, glm::vec3 position, glm::vec3 target) 
	: Camera(window)
{
	this->position = position;
	this->target = target;
}

TargetCamera::~TargetCamera()
{

}

void TargetCamera::SetPosition(glm::vec3 newPos)
{
	position = newPos;
}

glm::vec3 TargetCamera::GetPosition()
{
	return position;
}

void TargetCamera::SetTarget(glm::vec3 newTarg)
{
	target = newTarg;
}

glm::vec3 TargetCamera::GetTarget()
{
	return target;
}

void TargetCamera::Update(float elapsedSeconds)
{
	using namespace glm;

	vec3 forward = target - position;
	vec3 side = cross(normalize(forward), vec3(0, 1, 0));
	vec3 up = cross(forward, side);
	view = lookAt(position, target, up);
}
//=======================================================================================================

//================================================FREE CAMERA============================================
void scrollCallback(GLFWwindow*, double, double);

FreeCamera::FreeCamera(GLFWwindow* window, glm::vec3 position, float pitch, float yaw) 
	: Camera(window)
{
	this->position = position;
	this->pitch = pitch;
	this->yaw = yaw;
	speed = 5.0f;
	useArrows = false;
	wheelFOV = false;
	mouseSpeed = 0.005f;
	wheelSpeed = 0.5f;

	glfwSetScrollCallback(window, scrollCallback);
}

FreeCamera::~FreeCamera()
{

}

void FreeCamera::SetPosition(glm::vec3 newPos)
{
	position = newPos;
}

void FreeCamera::Move(glm::vec3 move)
{
	position += move;
}

glm::vec3 FreeCamera::GetPosition()
{
	return position;
}

void FreeCamera::SetPitch(float newP)
{
	pitch = newP;
}

float FreeCamera::GetPitch()
{
	return pitch;
}

void FreeCamera::SetYaw(float newY)
{
	yaw = newY;
}

float FreeCamera::GetYaw()
{
	return yaw;
}

void FreeCamera::Rotate(float p, float y)
{
	pitch += p;
	yaw += y;
}

void FreeCamera::SetSpeed(float newS)
{
	speed = newS;
}

float FreeCamera::GetSpeed()
{
	return speed;
}

float lastScroll = 0;
void FreeCamera::Update(float elapsedSeconds)
{
	using namespace glm;

	int monx, mony;
	glfwGetWindowSize(window, &monx, &mony);
	double mx, my;
	glfwGetCursorPos(window, &mx, &my);
	glfwSetCursorPos(window, monx/2, mony/2);

	yaw += mouseSpeed * float(monx/2 - mx);
	pitch += mouseSpeed * float(mony/2 - my);

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	if (yaw > 360.0f)
		yaw -= 360.0f;
	else if (yaw < -360.0f)
		yaw += 360.0f;

	if (wheelFOV)
	{
		SetFOV(GetFOV() + -wheelSpeed * lastScroll);
		lastScroll = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		speed = 400.0f;
	else
		speed = 5.0f;

	vec3 forward(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
	vec3 right(sin(yaw - 3.14f/2.0f), 0, cos(yaw - 3.14f/2.0f));
	vec3 up = cross(right, forward);

	if (useArrows)
	{
		if (glfwGetKey(window, GLFW_KEY_UP))
			position += forward * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_DOWN))
			position -= forward * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
			position += right * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_LEFT))
			position -= right * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_PERIOD))
			position += up * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_COMMA))
			position -= up * speed * elapsedSeconds;
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_W))
			position += forward * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_S))
			position -= forward * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_D))
			position += right * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_A))
			position -= right * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_Q))
			position += up * speed * elapsedSeconds;
		if (glfwGetKey(window, GLFW_KEY_Z))
			position -= up * speed * elapsedSeconds;
	}

	view = lookAt(position, position + forward, up);
}

void scrollCallback(GLFWwindow* window, double x, double y)
{
	lastScroll = (float)y;
}
//=======================================================================================================

//==============================================ARC-BALL CAMERA==========================================
void arcBallScrollCallback(GLFWwindow*, double, double);

ArcBallCamera* activeArcBall;
ArcBallCamera::ArcBallCamera(GLFWwindow* window, glm::vec3 target, float yaw, float pitch, float pMin, float pMax, float distance, float dMin, float dMax)
	: Camera(window)
{
	this->target = target;
	this->targetLast = target;
	
	this->yaw = yaw;
	this->pitch = glm::clamp(pitch, pMin, pMax);
	this->pitchMax = pMax;
	this->pitchMin = pMin;

	this->distance = glm::clamp(distance, dMin, dMax);
	this->distanceMax = dMax;
	this->distanceMin = dMin;

	useArrows = false;
	keyRotate = false;
	mouseSpeed = 0.1f;
	wheelSpeed = 1.5f;
	moveSpeed = 0.5f;

	glfwSetScrollCallback(window, arcBallScrollCallback);

	activeArcBall = this;
}

ArcBallCamera::~ArcBallCamera()
{

}

glm::vec3 ArcBallCamera::GetTarget()
{
	return target;
}

glm::vec3 ArcBallCamera::GetPosition()
{
	return position;
}

void ArcBallCamera::ChangeDistance(float dist)
{
	this->distance += dist * wheelSpeed;
	this->distance = glm::clamp(this->distance, distanceMin, distanceMax);
}

float ArcBallCamera::GetDistance()
{
	return distance;
}

void ArcBallCamera::Rotate(float dPitch, float dYaw)
{
	this->yaw += dYaw;
	this->pitch += dPitch;
	this->pitch = glm::clamp(this->pitch, pitchMin, pitchMax);
}

float ArcBallCamera::GetPitch()
{
	return pitch;
}

float ArcBallCamera::GetYaw()
{
	return yaw;
}

float lastMouseX = 0, lastMouseY = 0;
float mouseHoldX = 0, mouseHoldY = 0;
bool pressed = false;
float wheelX = 0, wheelY = 0;
bool moved = false; //If this camera has been moved by the arrows (used for compat. with ObjectCamera) 
void ArcBallCamera::Update(float elapsedSeconds)
{
	using namespace glm;

	if (keyRotate)
	{
		if (useArrows)
		{
			if (glfwGetKey(window, GLFW_KEY_UP))
				this->Rotate(mouseSpeed, 0.0f);
			if (glfwGetKey(window, GLFW_KEY_DOWN))
				this->Rotate(-mouseSpeed, 0.0f);
			if (glfwGetKey(window, GLFW_KEY_RIGHT))
				this->Rotate(0.0f, mouseSpeed);
			if (glfwGetKey(window, GLFW_KEY_LEFT))
				this->Rotate(0.0f, -mouseSpeed);
		}
		else
		{
			if (glfwGetKey(window, GLFW_KEY_W))
				this->Rotate(mouseSpeed, 0.0f);
			if (glfwGetKey(window, GLFW_KEY_S))
				this->Rotate(-mouseSpeed, 0.0f);
			if (glfwGetKey(window, GLFW_KEY_D))
				this->Rotate(0.0f, mouseSpeed);
			if (glfwGetKey(window, GLFW_KEY_A))
				this->Rotate(0.0f, -mouseSpeed);
		} 
	}
	else //Start moving the target around accordingly
	{
		mat4 yawMat = rotate(mat4(1.0), yaw, vec3(0, 1, 0));
		vec3 forward = vec3(yawMat * vec4(0, 0, 1, 1));
		vec3 right = cross(forward, vec3(0, 1, 0));
		float tSpeed = moveSpeed * (distance/50.0f);
		if (useArrows)
		{
			if (glfwGetKey(window, GLFW_KEY_UP))
			{
				target += -forward * tSpeed;
				moved = true;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN))
			{
				target += forward * tSpeed;
				moved = true;
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT))
			{
				target += -right * tSpeed;
				moved = true;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT))
			{
				target += right * tSpeed;
				moved = true;
			}
		}
		else
		{
			if (glfwGetKey(window, GLFW_KEY_W))
			{
				target += -forward * tSpeed;
				moved = true;
			}
			if (glfwGetKey(window, GLFW_KEY_S))
			{
				target += forward * tSpeed;
				moved = true;
			}
			if (glfwGetKey(window, GLFW_KEY_D))
			{
				target += -right * tSpeed;
				moved = true;
			}
			if (glfwGetKey(window, GLFW_KEY_A))
			{
				target += right * tSpeed;
				moved = true;
			}
		}
	}

	double mX = 0, mY = 0;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		glfwGetCursorPos(window, &mX, &mY);
		if (!pressed)
		{
			mouseHoldX = mX;
			mouseHoldY = mY;
			pressed = true;
		}

		float dX, dY;
		dX = mouseHoldX - (float)mX;
		dY = mouseHoldY - (float)mY;

		pitch += dY * mouseSpeed;
		yaw += dX * mouseSpeed;

		glfwSetCursorPos(window, mouseHoldX, mouseHoldY);
	}
	else
	{
		pressed = false;
	}

	mat4 rotation = rotate(mat4(1.0), yaw, vec3(0, 1, 0));
	rotation = rotate(rotation, pitch, vec3(1, 0, 0));
	vec3 rotateVec = vec3(rotation * vec4(0, 0, 1, 1));

	position = target + rotateVec * distance;

	if (target != targetLast)
		position += targetLast - target;

	vec3 upVec = vec3(rotation * vec4(0, 1, 0, 1));

	view = lookAt(position, target, upVec);

	targetLast = target;
	lastMouseX = mX;
	lastMouseY = mY;
}

void arcBallScrollCallback(GLFWwindow* window, double x, double y)
{
	activeArcBall->ChangeDistance(-y);
}
//=======================================================================================================

//==============================================OBJECT CAMERA============================================
ObjectCamera::ObjectCamera(GLFWwindow* window, SpaceObject* target, float yaw, float pitch, float pMin, float pMax, float distance, float dMin, float dMax)
	: ArcBallCamera(window, target == NULL ? vec3(0) : vec3(target->GetPosition().x, 0, target->GetPosition().y), yaw, pitch, pMin, pMax, distance, dMin, dMax)
{
	this->targetObject = target;
}

ObjectCamera::~ObjectCamera()
{

}

void ObjectCamera::SetTargetObject(SpaceObject* newTarg)
{
	this->targetObject = newTarg;
	moved = false;
}

const SpaceObject* ObjectCamera::GetTargetObject()
{
	return targetObject;
}

void ObjectCamera::Update(float elapsedSeconds)
{
	if (targetObject != NULL)
		this->target = vec3(targetObject->GetPosition().x, 0, targetObject->GetPosition().y); 

	ArcBallCamera::Update(elapsedSeconds);

	if (moved)
		targetObject = NULL;
}
//=======================================================================================================