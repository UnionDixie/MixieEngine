#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
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
	~Engine();
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
	//const char* vertexShader =
	//	"#version 330 core\n"
	//	"layout (location = 0) in vec3 vertexPos;"
	//	"layout (location = 1) in vec3 vertexColor;"
	//	"out vec3 color;"//<---
	//	"void main() {"
	//	"color = vertexColor;"
	//	"gl_Position = vec4(vertexPos,1.0);"//interpolation?
	//	"}";
	//const char* fragmentShader =
	//	"#version 330 core\n"
	//	"in vec3 color;"//<---
	//	"out vec4 fragColor;"
	//	"void main() {"
	//	"fragColor = vec4(color,1.0);"
	//	"}";
	Render::Shader shaderProg;//only args or moveConstructor
	ResourcesManager resManager;
	GLuint vao;
private:
	void processInput(GLFWwindow*);
	static void callbackResize(GLFWwindow*, int, int);
	static void callbackKeyboard(GLFWwindow*, int, int, int, int);
	void draw();
};

