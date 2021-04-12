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
	int run2();
	~Engine();
private:
	GLFWwindow* windowMain = nullptr;
	void processInput(GLFWwindow*);
	static void framebuffer_size_callback(GLFWwindow*,int,int);
	void draw();
	//Input input; singlton with static
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	int shaderProgram;
	unsigned int VBO, VAO, EBO;

	const int n = 1;
	std::array<ui, 1> trianglesVBO;
	std::array<ui, 1> trinanglesVAO;
	std::array<ui, 1> trinangleseEBO;

};

