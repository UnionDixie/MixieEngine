#include "Engine.h"

Engine::Engine()
{
    printf("Compiled against GLFW %i.%i.%i\n",
        GLFW_VERSION_MAJOR,
        GLFW_VERSION_MINOR,
        GLFW_VERSION_REVISION);
    //int major, minor, revision;
    //glfwGetVersion(&major, &minor, &revision);
    //printf("Running against GLFW %i.%i.%i\n", major, minor, revision);
   
    if (!glfwInit()) {
        assert(0 && "Error Init GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, " GLFW", NULL, NULL);

    if (!window)//NULL
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        assert(0 && "Error GLFW window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        assert(0 && "Error Init GLAD");
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Engine::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

void Engine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Engine::~Engine()
{
}