#include "..\..\..\include\core\win\Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/utility/log.h>



Engine::Window::Window(std::string_view title, int width, int height) :
				data(title,width,height)
{
	init();
}

Engine::Window::~Window()
{
	destroy();
}

void Engine::Window::update()
{
    glfwSwapInterval(1);
    glClearColor(1, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();    
}

std::pair<size_t, size_t> Engine::Window::getSize() const
{
	return data.sizeWindow;
}

void Engine::Window::setCallback(const EventCallBack& callbackFun)
{
    data.callbackEvent = callbackFun;
}

int Engine::Window::init()
{
    LOG_INFO("Welcome to init_Win!");
    //LOG_ERROR("Some error message with arg: {}", 1);
    //LOG_WARN("Easy padding in numbers like {:08d}", 12);
    //LOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);

    /* Initialize the library */
    if (!glfwIsInit) {
        if (!glfwInit())
            return -1;
        glfwIsInit = true;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(data.sizeWindow.first, data.sizeWindow.second, data.title.data(), nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_CRITICAL("Support glad error\n");
        return -1;
    }
    else
        LOG_INFO("Glad init!");

    glfwSetWindowUserPointer(window, &data);

    glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int w, int h) {

        auto& data = *static_cast<WinData*>(glfwGetWindowUserPointer(win));

        data.sizeWindow = { w,h };

        Engine::Event ev;
        ev.height = h; ev.width = w;

        data.callbackEvent(ev);


    });

    return 0;
}

void Engine::Window::destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
