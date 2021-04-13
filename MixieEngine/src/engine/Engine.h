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

class Engine
{
public:
	typedef unsigned int ui;
	Engine();
	void run();
	~Engine();
private:
	GLFWwindow* window = nullptr;
	const ui SCR_WIDTH = 800;
	const ui SCR_HEIGHT = 600;
private:
	void processInput(GLFWwindow*);
	static void callbackResize(GLFWwindow*, int, int);
	static void callbackKeyboard(GLFWwindow*, int, int, int, int);
	void draw();
};

