#include "Engine.h"

Engine::Engine() : resManager("data/"), windowSize(640,480), windowPos(600,300)
{
    //Init glfw and glad
    mainInit();
    //ver openGl    
    infoGL();
    //Load Data:shaders,texture and other..
    loadData();
}

void Engine::mainInit()
{
    /* Initialize the library */
    if (!glfwInit()) {
        //throw exception
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(windowSize.x, windowSize.y, "Hello OpenGL", nullptr, nullptr);
    glfwSetWindowPos(window, windowPos.x, windowPos.y);//~mid screen
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
    glfwSwapInterval(1);//fpsLimit ~60
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

#include "../Engine/shapes/shapes.h"

void Engine::loadData()
{
    if (auto get = resManager.loadShader("simpShader", "Shader/vertex.txt", "Shader/fragment.txt");
        get != nullptr && get->isCompiled()) {
        //shaderProg = std::move(*get.get());//hmm
    }
    else {
        std::cerr << "Can't create shader simpShader\n";
    }
    //
    auto simpShader = resManager.getShader("simpShader");
    auto texturePtr = resManager.loadTexture("fun", "image/fun.png");

    //VBO   
    vboList.emplace_back(Shapes::points, 9);
    const auto pointsVBO = vboList.back().getID();

    vboList.emplace_back(Shapes::colors, 9);
    const auto colorsVbo = vboList.back().getID();

    vboList.emplace_back(Shapes::texCoords, 6);
    const auto textureVBO = vboList.back().getID();

    //VAO
    //packet id,attrib,points
    Render::VAO::vboPacket packetPoints = { pointsVBO,0,3 },
                           packetColors = { colorsVbo,1,3 },
                           packetTexture = { textureVBO,2,2 };
    std::initializer_list<Render::VAO::vboPacket> packets{ packetPoints,
                                                           packetColors,
                                                           packetTexture };
    vaoList.emplace_back(packets);
    //Sprite
    triangle.setParam(vboList, vaoList, simpShader, texturePtr);

}

void Engine::run()
{
    glClearColor(1, 1, 0, 1);//RGBA
    while (!glfwWindowShouldClose(window))
    {
        update();
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
    vboList.clear();
    vaoList.clear();
    glfwTerminate();
}

void Engine::update()
{
    ////Transform object
    glm::mat4 transformTan = glm::mat4(1.0f); //
    //transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transformTan = glm::rotate(transformTan, (1.0f/std::tan((float)glfwGetTime())), glm::vec3(1.0f, 1.0f, 1.0f));
    auto scales = std::sin((float)glfwGetTime());
    transformTan = glm::scale(transformTan, glm::vec3(scales, scales, 1));

    triangle.setMat4("transform", transformTan);

    // —оздаем преобразование
    glm::mat4 model = glm::mat4(1.0f); // сначала инициализируем единичную матрицу
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);


    glm::mat4 transform = glm::mat4(1.0f);

    glm::mat4 model1 = glm::mat4(1.0f);
    model1 = glm::rotate(model1, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    transform = projection * view * model;

    // ѕолучаем местоположение uniform-матриц...
    //unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
    //unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
    // ...передаем их в шейдеры (разными способами)
    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    //glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    // ѕримечание: ¬ насто€щее врем€ мы устанавливаем матрицу проекции дл€
    //каждого кадра, но поскольку матрица проекции редко мен€етс€, 
    //то рекомендуетс€ устанавливать еЄ (единожды) вне основного цикла

    //triangle.setMat4("transform", transform);

}

void Engine::draw() 
{
    triangle.draw();
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