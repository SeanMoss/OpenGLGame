#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Controls.h"

glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;

GLFWwindow* window;

glm::mat4 getProjectionMatrix()
{
	return projectionMatrix;
}

glm::mat4 getViewMatrix()
{
	return viewMatrix;
}

glm::vec3 position(0, 0, 5);

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;

float speed = 3.0f;
float mouseSpeed = 0.005f;

float lastMouseWheel = 0.0f;

void ComputeMatricesFromInputs()
{
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = (float)(currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP)){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN)){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT)){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT)){
		position -= right * deltaTime * speed;
	}

	float FoV = initialFoV - 5 * lastMouseWheel;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(
					position,           // Camera is here
					position+direction, // and looks here : at the same position, plus "direction"
					up                  // Head is up (set to 0,-1,0 to look upside-down)
				);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void ScrollCallback(GLFWwindow* window, double x, double y)
{
	lastMouseWheel = (float)x;
}

void SetActiveWindow(GLFWwindow* newWindow)
{
	window = newWindow;
	glfwSetScrollCallback(window, ScrollCallback);
}