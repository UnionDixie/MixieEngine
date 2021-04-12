#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <memory>
#include <cassert>

#include "Input.h"

#include <vector>
#include <array>

class Engine
{
public:
	typedef unsigned int ui;
	Engine();
	void run();
	~Engine();
private:
	GLFWwindow* window = nullptr;
	void processInput(GLFWwindow*);
	static void framebuffer_size_callback(GLFWwindow*,int,int);
	void draw();
	//Input input; singlton with static
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	std::array<int, 2> shaderProgram;
	//unsigned int VBO, VAO, EBO;

	const int n = 2;
	std::array<ui, 2> trianglesVBO;
	std::array<ui, 2> trinanglesVAO;
	//std::array<ui, 2> trinanglesEBO;

};

