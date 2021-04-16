#include "Engine.h"

Engine::Engine() : resManager("data/"), windowSize(640,480)
{
    /* Initialize the library */
    if (!glfwInit()) {
        //throw exception
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(windowSize.x, windowSize.y, "Hello OpenGL", nullptr, nullptr);
    
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
    //resManager.loadTexture("wall", "image/wall.png");
    resManager.loadTexture("wall", "image/fun.png");

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
    auto simpShader = resManager.getShader("simpShader");
    simpShader->use();
    simpShader->setUniform("tex", 0);
    //

    glfwSwapInterval(1);//fpsLimit ~60

}

void Engine::run()
{
    glClearColor(1, 1, 0, 1);//RGBA
    while (!glfwWindowShouldClose(window))
    {
        logic();
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

void Engine::logic()
{
    //Transform object
    // create matrix
    glm::mat4 transform = glm::mat4(1.0f); // E
    //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (1.0f/std::tan((float)glfwGetTime())), glm::vec3(1.0f, 1.0f, 1.0f));
    auto scales = std::sin((float)glfwGetTime());
    transform = glm::scale(transform, glm::vec3(scales, scales, 1));


    // set uniform mat4
    auto shader = resManager.getShader("simpShader");
    shader->use();
    unsigned int transformLoc = glGetUniformLocation(shader->idShader, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void Engine::draw()
{
    resManager.getShader("simpShader")->use();
    resManager.getTexture("wall")->bind();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    auto logc = [=]() {
        // create matrix
        glm::mat4 transform = glm::mat4(1.0f); // E
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        auto scales = std::sin((float)glfwGetTime());
        transform = glm::scale(transform, glm::vec3(scales, scales, 1));
        // set uniform mat4
        auto shader = resManager.getShader("simpShader");
        shader->use();
        unsigned int transformLoc = glGetUniformLocation(shader->idShader, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    };
    logc();

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