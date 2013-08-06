#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Camera.h"
#include <iostream>

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
TargetCamera::TargetCamera(GLFWwindow* window, glm::vec3 position, glm::vec3 target) : Camera(window)
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

FreeCamera::FreeCamera(GLFWwindow* window, glm::vec3 position, float pitch, float yaw) : Camera(window)
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