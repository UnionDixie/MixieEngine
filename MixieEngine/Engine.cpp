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


   // glfw: ������������� � ����������������
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw: �������� ����
   window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL);
   if (window == NULL)
   {
       std::cout << "Failed to create GLFW window" << std::endl;
       glfwTerminate();
       //
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // glad: �������� ���� ���������� �� OpenGL-�������
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
       std::cout << "Failed to initialize GLAD" << std::endl;
   }

   // �������������� ����� ��������� ���������

   // ��������� ������
   int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);

   // �������� �� ������� ������ �������������� ���������� �������
   int success;
   char infoLog[512];
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
       glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
       std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
   }

   // ����������� ������
   int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);

   // �������� �� ������� ������ �������������� ������������ �������
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
       glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
       std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
   }

   // ����������� ������2
   int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
   glCompileShader(fragmentShader2);

   // �������� �� ������� ������ �������������� ������������ �������
   glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
   if (!success)
   {
       glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
       std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
   }


   // ���������� ��������
   //int shaderProgram = glCreateProgram();
   shaderProgram[0] = glCreateProgram();
   glAttachShader(shaderProgram[0], vertexShader);
   glAttachShader(shaderProgram[0], fragmentShader);
   glLinkProgram(shaderProgram[0]);

   // �������� �� ������� ������ �������������� ���������� ��������
   glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
   if (!success) {
       glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
   }

   // ���������� ��������2
   //int shaderProgram = glCreateProgram();
   shaderProgram[1] = glCreateProgram();
   glAttachShader(shaderProgram[1], vertexShader);
   glAttachShader(shaderProgram[1], fragmentShader2);
   glLinkProgram(shaderProgram[1]);

   // �������� �� ������� ������ �������������� ���������� ��������
   glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
   if (!success) {
       glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
       std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
   }



   //
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);





   // ���������� ������ (� �������) � ��������� ��������� ���������
   //float vertices[] = {
   //      0.5f,  0.5f, 0.0f,  // ������� ������
   //      0.5f, -0.5f, 0.0f,  // ������ ������
   //     -0.5f, -0.5f, 0.0f,  // ������ �����
   //     -0.5f,  0.5f, 0.0f   // ������� �����
   //};
   //unsigned int indices[] = {  // �������, ��� �� �������� � 0!
   //    0, 1, 3,  // ������ �����������
   //    1, 2, 3   // ������ �����������
   //};

   ////unsigned int VBO, VAO;
   //glGenVertexArrays(1, &VAO);
   //glGenBuffers(1, &VBO);
   //glGenBuffers(1, &EBO);

   //// ������� ��������� ������ ���������� �������, 
   ////����� ��������� � ������������� ��������� �����(�), 
   ////� ����� ������������� ��������� �������(�)
   //glBindVertexArray(VAO);

   //glBindBuffer(GL_ARRAY_BUFFER, VBO);
   //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   //glEnableVertexAttribArray(0);

   //// �������� ��������, ��� ������ �������� ���������, 
   ////����� glVertexAttribPointer() ��������������� VBO 
   ////��� ����������� ��������� �������� ������ ��� ���������� ��������,
   ////��� ��� ����� ����� �� ����� �������� ��������� �������
   //glBindBuffer(GL_ARRAY_BUFFER, 0);

   //// �������: �� ����������� EBO, ���� V�� �������, ��������� 
   //// ���������� ������ ������ �������� �������� � V��; ���������� �������� EBO.
   // //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   //// �� ������ �������� �������� V�� ����� �����, ����� ������
   //// ������ V�� �������� �� �������� ���� VAO (�� �������� �������� ����� ���������).
   //// ����������� ������ VAO ������� ����� glBindVertexArray(),
   ////������� �� ������ �� ������� �������� VAO (��� VBO), ����� ��� �� ��������� ��������
   //glBindVertexArray(0);

   const std::vector<std::vector<float>> tria = {
        //������ �����������
       { 0.8f, 0.5f, 0.0f,
         0.2f, 0.2f, 0.0f,
         0.8f,  0.2f, 0.0f}, 
         // ������ �����������
       {0.5f, -0.5f, 0.0f,  // ������ ������
        -0.5f, -0.5f, 0.0f,  // ������ �����
     -  0.5f,  0.5f, 0.0f}   // ������� �����
   };

   for (size_t i = 0; i < n; i++)
   {
       unsigned int VBO, VAO;
       glGenVertexArrays(1, &VAO);
       glGenBuffers(1, &VBO);

       // ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�)
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

       // �������� ��������, ��� ������ �������� ���������, ����� glVertexAttribPointer() ��������������� VBO ��� ����������� ��������� �������� ������ ��� ���������� ��������, ��� ��� ����� ����� �� ����� �������� ��������� �������
       glBindBuffer(GL_ARRAY_BUFFER, 0);

       // �� ������ �������� �������� V�� ����� �����, ����� ������ ������ V�� �������� �� �������� ���� VAO (�� �������� �������� ����� ���������).
       // ����������� ������ VAO ������� ����� glBindVertexArray(), ������� �� ������ �� ������� �������� VAO (��� VBO), ����� ��� �� ��������� ��������
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

   // ���������������� ��������� ������ ��� ��������� ��������� � ������ �������
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void Engine::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // ���������
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ������ ��� ������ �����������
        for (size_t i = 0; i < n; i++)
        {
            glUseProgram(shaderProgram[i]);
            glBindVertexArray(trinanglesVAO[i]); // ��������� � ��� ���� ������ ���� V��, �� ��� ������������� ��������� ��� ������ ��� (�� �� ������� ���, ����� �� ���� ������� ��������������)
            glDrawArrays(GL_TRIANGLES, 0, 3);
            //glBindVertexArray(0);
        }
        
        // glBindVertexArray(0); // �� ����� ������ ��� ��� ����������

        //!glBindVertexArray(VAO); // ��������� � ��� ���� ������ ���� V��, 
        //�� ��� ������������� ��������� ��� ������ ���
        //(�� �� ������� ���, ����� �� ���� ������� ��������������)
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //!glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // �� ����� ������ ��� ��� ����������

        //for (size_t i = 0; i < n; i++)
        //{
        //    ui tmp = trinanglesVAO[i];
        //    glBindVertexArray(tmp);
        //    //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        //    glDrawArrays(GL_TRIANGLES, 0, 3);
        //    glBindVertexArray(0);
        //}


        // glfw: ����� ���������� front- � back- �������. 
        //������������ ������� �����\������ 
        //(���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �����������: ����������� ��� �������, ��� ������ ��� ��������� ���� ��������������
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