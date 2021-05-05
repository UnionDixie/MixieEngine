#include "..\..\include\core\core.h"

Engine::Core::Core()
{
}

#include <iostream>
#include <GLFW/glfw3.h>

#include <core/utility/log.h>

int Engine::Core::init(ui width, ui height, std::string_view title)
{
    std::cout << "\tEngineCore\n";

    LOG_INFO("Welcome to spdlog!");
    LOG_ERROR("Some error message with arg: {}", 1);

    LOG_WARN("Easy padding in numbers like {:08d}", 12);
    LOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    LOG_INFO("Support for floats {:03.2f}", 1.23456);
    LOG_INFO("Positional args are {1} {0}..", "too", "supported");
    LOG_INFO("{:<30}", "left aligned");

    //spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    //spdlog::debug("This message should be displayed..");

    //// change log pattern
    //spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    //// Compile time log levels
    //// define SPDLOG_ACTIVE_LEVEL to desired level
    //SPDLOG_TRACE("Some trace message with param {}", 42);
    //SPDLOG_DEBUG("Some debug message");



    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        update();
    }

    glfwTerminate();
    return 0;
}

void Engine::Core::update()
{
}