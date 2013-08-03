#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Ship.h"
#include "Controls.h"
#include "TextureLoader.h"
#include <glm\gtx\vector_angle.hpp>

int main()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	GLFWwindow* window;
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(1024, 768, "Ship Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	SetActiveWindow(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetCursorPos(window, 1024/2, 768/2);
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	ShaderProgram* shader = new ShaderProgram("Basic3D.vert", "Basic3D.frag");
	GLuint uvmapId = LoadSOILTexture("uvmap.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y, true);
	ShipInfo sinfo;
	sinfo.maxSpeed = 0.01f;
	sinfo.maxAcceleration = 0.0005f;
	sinfo.maxTurnRate = 0.1f;
	sinfo.maxTurnAcceleration = 0.001f;
	Ship* ship = new Ship(sinfo);
	ship->UseTexture(uvmapId);
	ship->UseModel(new Model("suzanne.obj"));

	float oldVelocity = 0;
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ComputeMatricesFromInputs();

		ship->Update();
		ship->Render(shader);

		if(glfwGetKey(window, GLFW_KEY_1))
		{
			ship->SetDestination(vec3(10, 0, 10));
		}
		else if(glfwGetKey(window, GLFW_KEY_2))
		{
			ship->SetDestination(vec3(5, 11, 7));
		}
		else if(glfwGetKey(window, GLFW_KEY_3))
		{
			ship->SetDestination(vec3(-3, -1, 14));
		}
		else if(glfwGetKey(window, GLFW_KEY_ENTER))
		{
			ship->SetDestination(vec3(0, 0, 0));
		}

		std::cout << "Yaw: " << ship->GetYaw() << "\tPitch: " << ship->GetPitch() << "\tVelocity: " << ship->GetVelocity() << "\tAcceleration: " << ship->GetVelocity() - oldVelocity << std::endl;
		std::cout << "Position: " << ship->GetPosition().x << "\t" << ship->GetPosition().y << "\t" << ship->GetPosition().z << std::endl;
		oldVelocity = ship->GetVelocity();

		if(glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GL_TRUE);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	delete shader;

	return 0;
}