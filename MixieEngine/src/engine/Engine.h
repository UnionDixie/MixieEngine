#pragma once

#include <GLAD/include/glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

//#include <stdio.h>
#include <iostream>
//#include <stdexcept>
//#include <functional>
//#include <memory>
//#include <cassert>
//#include <vector>
//#include <array>

#include "../Engine/Render/Shader/Shader.h"
#include "Resources/ResourcesManager.h"
#include "../Engine/Render/Texture/Texture.h"

class Engine
{
public:
	typedef unsigned int ui;
	Engine();
	void run();
	~Engine() = default;
private:
	GLFWwindow* window = nullptr;
	//const ui SCR_WIDTH = 640;
	//const ui SCR_HEIGHT = 480;

	glm::ivec2 windowSize;
	GLfloat points[9] = {
		0.0f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
	};
	GLfloat colors[9] = {
		1.0f,0.f,0.f,
		0.0f,1.f,0.f,
		0.0f,0.f,1.f
	}; 
	float texCoords[6] = {
		0.0f, 0.0f,  // lower-left corner  
		1.0f, 0.0f,  // lower-right corner
		0.5f, 1.0f   // top-center corner
	};

	ResourcesManager resManager;
	GLuint vao;
private:
	void processInput(GLFWwindow*) const;
	static void callbackResize(GLFWwindow*, int, int);
	static void callbackKeyboard(GLFWwindow*, int, int, int, int);
	void draw();
	void infoGL() const;
	void logic();
};

