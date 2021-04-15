#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

class Engine
{
public:
	typedef unsigned int ui;
	Engine();
	void run();
	~Engine() = default;
private:
	GLFWwindow* window = nullptr;
	const ui SCR_WIDTH = 640;
	const ui SCR_HEIGHT = 480;
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
	ResourcesManager resManager;
	GLuint vao;
private:
	void processInput(GLFWwindow*) const;
	static void callbackResize(GLFWwindow*, int, int);
	static void callbackKeyboard(GLFWwindow*, int, int, int, int);
	void draw();
	void infoGL() const;
};

