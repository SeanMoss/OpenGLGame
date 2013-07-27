#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include <GLFW\glfw3.h>

void SetActiveWindow(GLFWwindow* newWindow);
void ComputeMatricesFromInputs();
glm::mat4 getProjectionMatrix();
glm::mat4 getViewMatrix();

#endif