#include "Engine.h"

Engine::Engine() : resManager("data/")
{
    /* Initialize the library */
    if (!glfwInit()) {
        //throw exception
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello OpenGL", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        //throw exception
    }
    //set callback func
    glfwSetWindowSizeCallback(window, callbackResize);
    //glfwSetKeyCallback(window, callbackKeyboard);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        //throw exception
    }

    glfwSetWindowPos(window, 600, 300);//~mid screen

    infoGL();


    if (auto get = resManager.loadShader("simpShader", "Shader/vertex.txt", "Shader/fragment.txt");
        get != nullptr && get->isCompiled()) {
        //shaderProg = std::move(*get.get());//hmm
    }
    else {
        std::cerr << "Can't create shader simpShader\n";
    }
    resManager.loadTexture("wall","image/wall.png");

    //VBO
    GLuint pointsVbo = 0;
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(points), points, GL_STATIC_DRAW);

    GLuint colorsVbo = 0;
    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint textureVBO = 0;
    glGenBuffers(1, &textureVBO);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    //texCoords

    //VAO
    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);//for location = 0
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, nullptr);

    //texture
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, nullptr);
    //
    resManager.getShader("simpShader")->use();
    resManager.getShader("simpShader")->setUniform("tex",0);
    //

    glfwSwapInterval(1);//fpsLimit ~60

}

void Engine::run()
{
    glClearColor(1, 1, 0, 1);//RGBA
    while (!glfwWindowShouldClose(window))
    {
        //userInput
        processInput(window); //or uses callback :)
        //render
        glClear(GL_COLOR_BUFFER_BIT);
        draw();
        //swap
        glfwSwapBuffers(window);
        //readEvents
        glfwPollEvents();
    }
    //resManager.~ResourcesManager();
    glfwTerminate();
}

void Engine::draw()
{
    resManager.getShader("simpShader")->use();
    resManager.getTexture("wall")->bind();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Engine::infoGL() const
{
    printf("Compiled against GLFW %i.%i.%i\n",
        GLFW_VERSION_MAJOR,
        GLFW_VERSION_MINOR,
        GLFW_VERSION_REVISION);
    //log
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    std::cout << glGetString(GL_VERSION) << "\n";
    std::cout << glGetString(GL_VENDOR) << "\n";
    if (auto log = glGetString(GL_RENDER); log != nullptr) {
        std::cout << log << "\n";
    }
    else {
        //throw exception
    }
}

void Engine::callbackKeyboard(GLFWwindow* win,int key,int scancode,int act,int mode) {
   
    if (key == GLFW_KEY_ESCAPE && scancode == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, true);
   }
}

void Engine::processInput(GLFWwindow* window) const
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Engine::callbackResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}