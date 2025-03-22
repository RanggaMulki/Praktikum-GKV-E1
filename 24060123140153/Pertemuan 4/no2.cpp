#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <algorithm>

GLfloat xRotated = 0.0f, yRotated = 0.0f, zRotated = 0.0f;

static int shoulder = 0;
static int elbow = 0;
static int palm = 0;
static int indexFinger = 0;
static int middleFinger = 0;
static int ringFinger = 0;
static int pinkyFinger = 0;
static int thumb = 0;

void DrawWireCube()
{
    glBegin(GL_LINES);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f( 0.5, -0.5, 0.5);
    glVertex3f( 0.5, -0.5, 0.5);
    glVertex3f( 0.5, 0.5, 0.5);
    glVertex3f( 0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, 0.5, -0.5);
    glVertex3f( 0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5, 0.5);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, 0.5, 0.5);
    glVertex3f( 0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
}

void DrawFinger()
{
    glPushMatrix();
    glScalef(0.4, 0.1, 0.1);
    DrawWireCube();
    glPopMatrix();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -7.0);
    
    glPushMatrix();
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    DrawWireCube();
    glPopMatrix();
    
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    DrawWireCube();
    glPopMatrix();
    
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)palm, 1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.5, 0.5, 0.2);
    DrawWireCube();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.25, 0.2, 0.0);
    glRotatef((GLfloat)indexFinger, 0.0, 1.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);
    DrawFinger();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.25, 0.07, 0.0);
    glRotatef((GLfloat)middleFinger, 0.0, 1.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);
    DrawFinger();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.25, -0.07, 0.0);
    glRotatef((GLfloat)ringFinger, 0.0, 1.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);
    DrawFinger();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.25, -0.2, 0.0);
    glRotatef((GLfloat)pinkyFinger, 0.0, 1.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);
    DrawFinger();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    glRotatef(-30, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)thumb, -1.0, 0.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);
    DrawFinger();
    glPopMatrix();
    
    glPopMatrix();
}

void Reshape(GLFWwindow* window, int width, int height)
{
    if (height == 0 || width == 0) return;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)width / (GLfloat)height, 0.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_E:
                elbow = std::min(elbow + 5, 90);
                break;
            case GLFW_KEY_Q:
                elbow = std::max(elbow - 5, 0);
                break;
                
            case GLFW_KEY_D:
                palm = std::min(palm + 5, 90);
                break;
            case GLFW_KEY_A:
                palm = std::max(palm - 5, -90);
                break;
                
            case GLFW_KEY_1:
                indexFinger = std::min(indexFinger + 5, 90);
                break;
            case GLFW_KEY_6:
                indexFinger = std::max(indexFinger - 5, 0);
                break;
                
            case GLFW_KEY_2:
                middleFinger = std::min(middleFinger + 5, 90);
                break;
            case GLFW_KEY_7:
                middleFinger = std::max(middleFinger - 5, 0);
                break;
                
            case GLFW_KEY_3:
                ringFinger = std::min(ringFinger + 5, 90);
                break;
            case GLFW_KEY_8:
                ringFinger = std::max(ringFinger - 5, 0);
                break;
                
            case GLFW_KEY_4:
                pinkyFinger = std::min(pinkyFinger + 5, 90);
                break;
            case GLFW_KEY_9:
                pinkyFinger = std::max(pinkyFinger - 5, 0);
                break;
                
            case GLFW_KEY_5:
                thumb = std::min(thumb + 5, 90);
                break;
            case GLFW_KEY_0:
                thumb = std::max(thumb - 5, 0);
                break;
                
            case GLFW_KEY_R:
                elbow = 0;
                palm = 0;
                indexFinger = 0;
                middleFinger = 0;
                ringFinger = 0;
                pinkyFinger = 0;
                thumb = 0;
                break;
                
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
        }
    }
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "TANGAN NYATA",
        NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(window, KeyCallback);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    Reshape(window, width, height);
    while (!glfwWindowShouldClose(window))
    {
        Display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}