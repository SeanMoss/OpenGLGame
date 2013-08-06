#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Ship.h"
#include "Camera.h"
#include "TextureLoader.h"
#include "Skybox.h"

int monitorWidth, monitorHeight;
bool fullScreen = true;
Camera* camera;

int main()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	GLFWwindow* window;
	glfwWindowHint(GLFW_SAMPLES, 4);
	Camera::GetBestMonitorSize(&monitorWidth, &monitorHeight);
	window = glfwCreateWindow(monitorWidth, monitorHeight, "Ship Game", fullScreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetCursorPos(window, monitorWidth/2, monitorHeight/2);
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	camera = new FreeCamera(window, vec3(0, 0, 10), 0, 180);

	ShaderProgram* shader = new ShaderProgram("TextureOnly.vert", "TextureOnly.frag");
	GLuint uvmapId = LoadSOILTexture("uvmap.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y, true);
	GLuint pMap = LoadSOILTexture("flatearth.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y, true);
	ShipInfo sinfo;
	sinfo.maxSpeed = 0.5f;
	sinfo.maxAcceleration = 0.1f;
	sinfo.maxTurnRate = 3.0f;
	sinfo.maxTurnAcceleration = 1.5f;
	Ship* ship = new Ship(sinfo);
	ship->UseModel(new Model("suzanne.obj"));
	ship->UseTexture(uvmapId);
	Ship* ship2 = new Ship(sinfo);
	ship2->UseModel(new Model("suzanne.obj"));
	ship2->UseTexture(uvmapId);
	ship2->SetPosition(-5.0f, 0.0f);
	ship->Stop();
	ship2->Stop();

	ShipInfo pinfo;
	pinfo.maxSpeed = 0;
	pinfo.maxAcceleration = 0;
	pinfo.maxTurnAcceleration = 0;
	pinfo.maxTurnRate = 0;
	Ship* planet = new Ship(pinfo);
	planet->UseModel(new Model("sphere.obj"));
	planet->UseTexture(pMap);
	planet->SetPosition(6500, 0);//R:6367.5 d:12735
	planet->SetScale(6367.5f);
	planet->Stop();

	Skybox* sky = new Skybox("SkyMaps\\basic_space_left2.png", "SkyMaps\\basic_space_right1.png", "SkyMaps\\basic_space_top3.png", 
		"SkyMaps\\basic_space_bottom4.png", "SkyMaps\\basic_space_back6.png", "SkyMaps\\basic_space_front5.png");

	double lastTime = 0.0;
	while(!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera->Update((float)(currentTime - lastTime));
		
		sky->Render();

		ship->Update((float)(currentTime - lastTime));
		ship->Render(shader);
		ship2->Update((float)(currentTime - lastTime));
		ship2->Render(shader);
		planet->Render(shader);

		if(glfwGetKey(window, GLFW_KEY_1))
		{
			ship->SetDestination(vec2(10, 10));
			ship2->SetDestination(vec2(10, 10));
		}
		else if(glfwGetKey(window, GLFW_KEY_2))
		{
			ship->SetDestination(vec2(5, 7));
			ship2->SetDestination(vec2(5, 7));
		}
		else if(glfwGetKey(window, GLFW_KEY_3))
		{
			ship->SetDestination(vec2(-3, 14));
			ship2->SetDestination(vec2(-3, 14));
		}
		else if(glfwGetKey(window, GLFW_KEY_ENTER))
		{
			ship->SetDestination(vec2(0, 0));
			ship2->SetDestination(vec2(-5, 0));
		}

		if(glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GL_TRUE);

		cout << "FPS: " << (1.0f/(currentTime - lastTime)) << endl;

		glfwPollEvents();
		glfwSwapBuffers(window);
		lastTime = currentTime;
	}

	glfwTerminate();
	delete shader;

	return 0;
}