#include <GLFW/glfw3.h>

#include <cmath>

#define M_PI           3.14159265358979323846 

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    float theta = 0.0f;

    auto drawTri = []() {
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.5f, 0.f);
        glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(0.5f, 0.5f);
        glEnd();
    };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        
        //Kernel------------------------------------------------------------------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //------------------------------------------------------------------------
        //glPushMatrix();
        //glRotatef(theta, 0.0f, 1.0f, 0.0f);//angle x y z
        //glBegin(GL_TRIANGLES);
        auto time = glfwGetTime();
        for (size_t i = 1; i <= 8; i++)
        {
            glLoadIdentity();
            glRotatef(time * i * 45, 0, 0, 1.0f);
            drawTri();
        }
        

        //glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f, 0.0f);
        //glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.0f, 1.f);
        //glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(1.f, 1.f);

        //glEnd();
        //glPopMatrix();
        //------------------------------------------------------------------------
        /*float x = 0, y = 0, cnt = 40, l = 0.5f, a = M_PI * 2 / cnt;
        glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 0.0f, 1.0f);
            glVertex2f(0.0f, 0.0f);
            for (int i = -1; i < cnt; i++)
            {
                x = std::sin(a * i) * l;
                y = std::cos(a * i) * l;
                glVertex2f(x, y);
            }
        glEnd();*/
        //------------------------------------------------------------------------


        //glPushMatrix();
        //glRotatef(theta, 1.0f, 0.0f, 0.0f);//angle x y z
        //glPointSize(10);
        //glBegin(GL_POINTS);
        //glColor3d(0,1 , 0);
        //glVertex3d(0.0f, 0.5f, 0); // первая точка
        //glEnd();
        //glPopMatrix();

        //glPushMatrix();
        //glRotatef(theta, 0.0f, 1.0f, 0.0f);//angle x y z
        //glPointSize(10);
        //glBegin(GL_POINTS);
        //glColor3d(1, 0, 0);
        //glVertex3d(0.5f, 0.0f, 0); //  точка
        //glEnd();
        //glPopMatrix();

        //glPushMatrix();
        //glRotatef(theta, 0.0f, 0.0f, 1.0f);//angle x y z
        //glPointSize(10);
        //glBegin(GL_POINTS);
        //glColor3d(0, 0, 1);
        //glVertex3d(0.5f, 0.0f, 0.0f); //  точка
        //glEnd();
        //glPopMatrix();



        //theta += 1.0f;

        //------------------------------------------------------------------------
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}