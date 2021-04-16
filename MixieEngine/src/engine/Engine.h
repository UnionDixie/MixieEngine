#pragma once

#include <GLAD/include/glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include <iostream>
#include <list>
//#include <stdio.h>
//#include <stdexcept>
//#include <functional>
//#include <memory>
//#include <cassert>
//#include <array>

#include "../Engine/Render/Shader/Shader.h"
#include "Resources/ResourcesManager.h"
#include "../Engine/Render/Texture/Texture.h"
#include "../Engine/Render/vbo/vbo.h"
#include "../Engine/Render/vao/vao.h"
#include "../Engine/Render/sprite/sprite.h"

class Engine
{
public:
	//typedef unsigned int ui;
	Engine();
	void run();
	~Engine() = default;
private:
	GLFWwindow* window = nullptr;

	glm::ivec2 windowSize, windowPos;
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
	Render::Sprite triangle;
	std::list<Render::VBO> vboList;
	std::list<Render::VAO> vaoList;

private:
	void processInput(GLFWwindow*) const;
	static void callbackResize(GLFWwindow*, int, int);
	void draw();
	void infoGL() const;
	void update();
	void mainInit();
	void loadData();
};

