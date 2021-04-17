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
    triangle1.setParam(vboList, vaoList, simpShader, texturePtr);
    triangle2.setParam(vboList, vaoList, simpShader, texturePtr);
    //triangle3.setParam(vboList, vaoList, simpShader, texturePtr);
    //triangle4.setParam(vboList, vaoList, simpShader, texturePtr);


    triangle2.setPos(glm::vec3(0.4f, 0.4f, 0.0f));
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
    vboList.clear();
    vaoList.clear();
    glfwTerminate();
}

void Engine::update()
{
    //Transform objects
    triangle1.rotate((1.0f / std::tan((float)glfwGetTime())));
    auto scales = std::sin((float)glfwGetTime());
    triangle1.scale(glm::vec3(scales, scales, 1));

    //triangle2.scale(glm::vec3(scales, scales, 1));
    //auto move = std::cos(glfwGetTime()) * -0.001f;
    //triangle2.move(glm::vec3(move, move, 0.f));
}

void Engine::draw() 
{
    update();
    triangle1.draw();
    triangle2.draw();
}

void Engine::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    int state1 = glfwGetKey(window, GLFW_KEY_W);
    int state2 = glfwGetKey(window, GLFW_KEY_S);
    int state3 = glfwGetKey(window, GLFW_KEY_A);
    int state4 = glfwGetKey(window, GLFW_KEY_D);
    int state5 = glfwGetKey(window, GLFW_KEY_Q);
    int state6 = glfwGetKey(window, GLFW_KEY_E);
    int state7 = glfwGetKey(window, GLFW_KEY_T);
    int state8 = glfwGetKey(window, GLFW_KEY_G);
    //int state9 = glfwGetKey(window, GLFW_KEY_R);
    if (state1 == GLFW_PRESS)
    {
        triangle2.move(glm::vec3(0.f, 0.01f, 0.f));
    }
    if (state2 == GLFW_PRESS)
    {
        triangle2.move(glm::vec3(0.f, -0.01f, 0.f));
    }
    if (state3 == GLFW_PRESS)
    {
        triangle2.move(glm::vec3(-0.01f, 0.0f, 0.f));
    }
    if (state4 == GLFW_PRESS)
    { 
        triangle2.move(glm::vec3(0.01f, 0.0f, 0.f));
    }
    if (state5 == GLFW_PRESS)
    {
        triangle2.rotate(0.1f);
    }
    if (state6 == GLFW_PRESS)
    {
        triangle2.rotate(-0.1f);
    }
    if (state7 == GLFW_PRESS)
    {
        triangle2.scale(glm::vec3(0.1f, 0.1f, 1),false);
    }
    if (state8 == GLFW_PRESS)
    {
        triangle2.scale(glm::vec3(-0.1f, -0.1f, 1),false);
    }



}

void Engine::callbackResize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}