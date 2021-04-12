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
        "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n\0";


   // glfw: инициализация и конфигурирование
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: создание окна
   window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
   if (window == NULL)
   {
       std::cout << "Failed to create GLFW window" << std::endl;
       glfwTerminate();
       //
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // glad: загрузка всех указателей на OpenGL-функции
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
       std::cout << "Failed to initialize GLAD" << std::endl;
   }

   // Компилирование нашей шейдерной программы

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
   //int shaderProgram = glCreateProgram();
   shaderProgram[0] = glCreateProgram();
   glAttachShader(shaderProgram[0], vertexShader);
   glAttachShader(shaderProgram[0], fragmentShader);
   glLinkProgram(shaderProgram[0]);

   // Проверка на наличие ошибок компилирования связывания шейдеров
   glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
   if (!success) {
       glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
   }

   // Связывание шейдеров2
   //int shaderProgram = glCreateProgram();
   shaderProgram[1] = glCreateProgram();
   glAttachShader(shaderProgram[1], vertexShader);
   glAttachShader(shaderProgram[1], fragmentShader2);
   glLinkProgram(shaderProgram[1]);

   // Проверка на наличие ошибок компилирования связывания шейдеров
   glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
   if (!success) {
       glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
       std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
   }



   //
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);





   // Указывание вершин (и буферов) и настройка вершинных атрибутов
   //float vertices[] = {
   //      0.5f,  0.5f, 0.0f,  // верхняя правая
   //      0.5f, -0.5f, 0.0f,  // нижняя правая
   //     -0.5f, -0.5f, 0.0f,  // нижняя левая
   //     -0.5f,  0.5f, 0.0f   // верхняя левая
   //};
   //unsigned int indices[] = {  // помните, что мы начинаем с 0!
   //    0, 1, 3,  // первый треугольник
   //    1, 2, 3   // второй треугольник
   //};

   ////unsigned int VBO, VAO;
   //glGenVertexArrays(1, &VAO);
   //glGenBuffers(1, &VBO);
   //glGenBuffers(1, &EBO);

   //// Сначала связываем объект вершинного массива, 
   ////затем связываем и устанавливаем вершинный буфер(ы), 
   ////и затем конфигурируем вершинный атрибут(ы)
   //glBindVertexArray(VAO);

   //glBindBuffer(GL_ARRAY_BUFFER, VBO);
   //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   //glEnableVertexAttribArray(0);

   //// Обратите внимание, что данное действие разрешено, 
   ////вызов glVertexAttribPointer() зарегистрировал VBO 
   ////как привязанный вершинный буферный объект для вершинного атрибута,
   ////так что после этого мы можем спокойно выполнить отвязку
   //glBindBuffer(GL_ARRAY_BUFFER, 0);

   //// помните: не отвязывайте EBO, пока VАО активен, поскольку 
   //// связанного объект буфера элемента хранится в VАО; сохраняйте привязку EBO.
   // //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   //// Вы можете отменить привязку VАО после этого, чтобы другие
   //// вызовы VАО случайно не изменили этот VAO (но подобное довольно редко случается).
   //// Модификация других VAO требует вызов glBindVertexArray(),
   ////поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
   //glBindVertexArray(0);

   const std::vector<std::vector<float>> tria = {
        //Первый треугольник
       { 0.8f, 0.5f, 0.0f,
         0.2f, 0.2f, 0.0f,
         0.8f,  0.2f, 0.0f}, 
         // Второй треугольник
       {0.5f, -0.5f, 0.0f,  // нижняя правая
        -0.5f, -0.5f, 0.0f,  // нижняя левая
     -  0.5f,  0.5f, 0.0f}   // верхняя левая
   };

   for (size_t i = 0; i < n; i++)
   {
       unsigned int VBO, VAO;
       glGenVertexArrays(1, &VAO);
       glGenBuffers(1, &VBO);

       // Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
       glBindVertexArray(VAO);

       glBindBuffer(GL_ARRAY_BUFFER, VBO);

       float tmps[9];
       for (size_t j = 0; j < 9; j++)
       {
           tmps[j] = tria[i][j];
       }

       glBufferData(GL_ARRAY_BUFFER, sizeof(tmps), tmps, GL_STATIC_DRAW);

       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
       glEnableVertexAttribArray(0);

       // Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно выполнить отвязку
       glBindBuffer(GL_ARRAY_BUFFER, 0);

       // Вы можете отменить привязку VАО после этого, чтобы другие вызовы VАО случайно не изменили этот VAO (но подобное довольно редко случается).
       // Модификация других VAO требует вызов glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
       glBindVertexArray(0);

       trianglesVBO[i] = VBO;
       trinanglesVAO[i] = VAO;
   }

   //for (size_t i = 0; i < n; i++)
   //{
   //    glGenVertexArrays(1, &trinanglesVAO[i]);
   //    glGenBuffers(1, &trianglesVBO[i]);
   //    //glGenBuffers(1, &trinanglesEBO[i]);
   //    glBindVertexArray(trinanglesVAO[i]);
   //    glBindBuffer(GL_ARRAY_BUFFER, trianglesVBO[i]);

   //    

   //    glBufferData(GL_ARRAY_BUFFER, sizeof(float), tmps, GL_STATIC_DRAW);

   //    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trinangleseEBO[i]);
   //    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

   //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(tmps), (void*)0);
   //    glEnableVertexAttribArray(0);
   //    glBindBuffer(GL_ARRAY_BUFFER, 0);
   //    glBindVertexArray(0);
   //}

   // Раскомментируйте следующую строку для отрисовки полигонов в режиме каркаса
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void Engine::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Рисуем наш первый треугольник
        for (size_t i = 0; i < n; i++)
        {
            glUseProgram(shaderProgram[i]);
            glBindVertexArray(trinanglesVAO[i]); // поскольку у нас есть только один VАО, то нет необходимости связывать его каждый раз (но мы сделаем это, чтобы всё было немного организованнее)
            glDrawArrays(GL_TRIANGLES, 0, 3);
            //glBindVertexArray(0);
        }
        
        // glBindVertexArray(0); // не нужно каждый раз его отвязывать

        //!glBindVertexArray(VAO); // поскольку у нас есть только один VАО, 
        //то нет необходимости связывать его каждый раз
        //(но мы сделаем это, чтобы всё было немного организованнее)
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //!glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // не нужно каждый раз его отвязывать

        //for (size_t i = 0; i < n; i++)
        //{
        //    ui tmp = trinanglesVAO[i];
        //    glBindVertexArray(tmp);
        //    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        //    glDrawArrays(GL_TRIANGLES, 0, 3);
        //    glBindVertexArray(0);
        //}


        // glfw: обмен содержимым front- и back- буферов. 
        //Отслеживание событий ввода\вывода 
        //(была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Опционально: освобождаем все ресурсы, как только они выполнили свое предназначение
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

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

void Engine::draw()
{

   
}

Engine::~Engine()
{
}