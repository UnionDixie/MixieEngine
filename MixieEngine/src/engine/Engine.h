#pragma once

#include <GLAD/include/glad/glad.h>
#include <GLFW/include/GLFW/glfw3.h>
#include <glm/glm.hpp>

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
//#include "../Engine/Render/sprite/square/square.h"

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
	ResourcesManager resManager;
	Render::Sprite triangle1, triangle2,
		           triangle3, triangle4;
	
	std::list<Render::VBO> vboList;
	std::list<Render::VAO> vaoList;
private:
	Render::Sprite square;
	std::list<Render::VBO> vboList2;
	std::list<Render::VAO> vaoList2;
private:
	void processInput(GLFWwindow*);
	static void callbackResize(GLFWwindow*, int, int);
	void draw();
	void infoGL() const;
	void update();
	void mainInit();
	void loadData();
};

