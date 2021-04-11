#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <cassert>

#include "Input.h"

class Engine
{
public:
	Engine();
	void run();
	~Engine();
private:
	GLFWwindow* window = nullptr;
	void processInput(GLFWwindow*);
	static void framebuffer_size_callback(GLFWwindow*,int,int);
	//Input input; singlton with static
};

