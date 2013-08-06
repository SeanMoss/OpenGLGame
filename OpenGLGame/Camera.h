#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GLFW\glfw3.h>

class Camera;
class TargetCamera;
class FreeCamera;

//Abstract camera class
class Camera
{
public:
	static void GetBestMonitorSize(int* w, int* h);
	static const Camera* GetActiveCamera();
	static glm::vec3 ActiveCameraPosition();

private:
	int width, height;
	float fov;
	float near, far;

protected:
	glm::mat4 projection;
	glm::mat4 view;
	GLFWwindow* window;

public:
	Camera(GLFWwindow* window);
	virtual ~Camera();

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	float GetAspectRatio() const;
	void GetCurrentCameraWindowSize(int* w, int* h) const;
	void SetFOV(float newfov);
	float GetFOV() const;
	void SetDepth(float near, float far);
	void GetDepth(float* near, float* far) const;

	virtual glm::vec3 GetPosition() = 0;
	virtual void Update(float elapsedSeconds) = 0;
};

//Camera that points to a target, relative position and target not specifically designed to move, although they can
//Ex: Stationary Security Camera, Ship nosecam
class TargetCamera : public Camera
{
private:
	glm::vec3 position;
	glm::vec3 target; 

public:
	TargetCamera(GLFWwindow* window, glm::vec3 position, glm::vec3 target);
	~TargetCamera();

	void SetPosition(glm::vec3);
	glm::vec3 GetPosition();
	void SetTarget(glm::vec3);
	glm::vec3 GetTarget();

	virtual void Update(float elapsedSeconds);
};

//Camera that can be freely controlled to move any direction
class FreeCamera : public Camera
{
private:
	float yaw, pitch;
	glm::vec3 position;
	float speed;

public:
	bool useArrows; //If moving should be done by the arrows instead of WASD
	bool wheelFOV; //If scrolling the mouse wheel changes the field of view
	float mouseSpeed; //The speed at which the mouse moves the camera
	float wheelSpeed; //The speed at which the wheel changes the field of view
	
public:
	FreeCamera(GLFWwindow* window, glm::vec3 position, float pitch, float yaw);
	~FreeCamera();

	void SetPosition(glm::vec3);
	void Move(glm::vec3);
	glm::vec3 GetPosition();
	void SetPitch(float);
	float GetPitch();
	void SetYaw(float);
	float GetYaw();
	void Rotate(float, float);
	void SetSpeed(float);
	float GetSpeed();

	virtual void Update(float elapsedSeconds);
};

//A camera that points towards a position, and can be moved closer/further with the mouse wheel, and rotated around the target
class ArcBallCamera : public Camera
{

};
#endif