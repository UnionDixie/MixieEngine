#include <glad/glad.h>//glad first!!!
#include <GLFW/glfw3.h>

#include <string_view>
#include <spdlog/spdlog.h>

#include <iostream>

using ui = unsigned int;
constexpr ui WIDTH = 800;
constexpr ui HEIGHT = 600;

void resizeCallback(GLFWwindow* win, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window);

int main(void)
{
    spdlog::info("Start...");
    glfwInit();//
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    std::string_view title("OpenGL");
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, title.data(), nullptr, nullptr);

    if (!window) {
        spdlog::error("Error create window: {}", 1);
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
   

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::error("Error load GLAD: {}", 1);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

     //Data
    float vertices[] = {
        -0.5f,-0.5f,0.0f,
         0.5f,-0.5f,0.0f,
         0.0f, 0.5f,0.0f
    };

    float rectangle[] = {
        // Первый треугольник
         0.5f,  0.5f, 0.0f,  // верхняя правая
         0.5f, -0.5f, 0.0f,  // нижняя правая
        -0.5f,  0.5f, 0.0f,  // верхняя левая 

        // Второй треугольник
         0.5f, -0.5f, 0.0f,  // нижняя правая
        -0.5f, -0.5f, 0.0f,  // нижняя левая
        -0.5f,  0.5f, 0.0f   // верхняя левая
    };
    
    ui VBO,VAO;//vertex buffer objects,ver array objs
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//layout location,vec3,float,normise?,
    glEnableVertexAttribArray(0);                                                //stride-step - 3*4(12) or 0!!!, offset

    glBindBuffer(GL_ARRAY_BUFFER, 0);//detach vbo
    glBindVertexArray(0);//detach vao
    //------
    float twoTriangle1[] = {
        -0.5f,  0.0f, 0.0f,
        -0.25f, 0.5f, 0.0f,
         0.0f,  0.0f, 0.0f,
         //
         0.5f,  0.0f, 0.0f,
         0.25f, 0.5f, 0.0f,
         0.0f,  0.0f, 0.0f
         
    };
    ui VBO3, VAO3;//vertex buffer objects,ver array objs
    glGenVertexArrays(1, &VAO3);
    glGenBuffers(1, &VBO3);

    glBindVertexArray(VAO3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(twoTriangle1), twoTriangle1, GL_STATIC_DRAW);// /=2?

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//layout location,vec3,float,normise?,
    glEnableVertexAttribArray(0);                                                //stride-step - 3*4(12) or 0!!!, offset

    glBindBuffer(GL_ARRAY_BUFFER, 0);//detach vbo
    glBindVertexArray(0);//detach vao
    //------
    float twoTriangle2[] = {
         0.5f,  0.0f, 0.0f,
         0.25f, 0.5f, 0.0f,
         0.0f,  0.0f, 0.0f

    };
    ui VBO4, VAO4;//vertex buffer objects,ver array objs
    glGenVertexArrays(1, &VAO4);
    glGenBuffers(1, &VBO4);

    glBindVertexArray(VAO4);

    glBindBuffer(GL_ARRAY_BUFFER, VBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(twoTriangle2), twoTriangle2, GL_STATIC_DRAW);// /=2?

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);                                                

    glBindBuffer(GL_ARRAY_BUFFER, 0);//detach vbo
    glBindVertexArray(0);//detach vao

    //--
    ui VBO1, VAO1;//vertex buffer objects,ver array objs
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//layout location,vec3,float,normise?,
    glEnableVertexAttribArray(0);                                                //stride-step - 3*4(12) or 0!!!, offset

    glBindBuffer(GL_ARRAY_BUFFER, 0);//detach vbo
    glBindVertexArray(0);//detach vao
    //
    float rect[] = {
     0.5f,  0.5f, 0.0f,  // верхняя правая
     0.5f, -0.5f, 0.0f,  // нижняя правая
    -0.5f, -0.5f, 0.0f,  // нижняя левая
    -0.5f,  0.5f, 0.0f   // верхняя левая 
    };
    unsigned int indices[] = {  // помните, что мы начинаем с 0!
        //0, 1, 3, // первый треугольник
        //1, 2, 3  // второй треугольник
        0, 1, 2, // первый треугольник
        0, 2, 3  // второй треугольник
    };
    ui VBO2, VAO2,EBO;//vertex buffer objects,ver array objs
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//layout location,vec3,float,normise?,
    glEnableVertexAttribArray(0);                                                //stride-step - 3*4(12) or 0!!!, offset

    glBindBuffer(GL_ARRAY_BUFFER, 0);//detach vbo
    glBindVertexArray(0);//detach vao

    //shaders
    // Компилирование нашей шейдерной программы
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    const char* fragmentShaderSource2 = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        "}\n\0";
    // Вершинный шейдер
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Проверка на наличие ошибок компилирования вершинного шейдера
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Фрагментный шейдер
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Проверка на наличие ошибок компилирования фрагментного шейдера
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Фрагментный шейдер2
    int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    // Проверка на наличие ошибок компилирования фрагментного шейдера
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Связывание шейдеров
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Проверка на наличие ошибок компилирования связывания шейдеров
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Связывание шейдеров
    int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // Проверка на наличие ошибок компилирования связывания шейдеров
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader2);



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1);//rectangle
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO3);//rectangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO4);//rectangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO2);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}