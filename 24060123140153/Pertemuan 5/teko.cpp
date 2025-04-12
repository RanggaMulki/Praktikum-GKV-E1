#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>

double rotAngle = 10; 
double rotAngle1 = 10; 

void drawTeapot(float size) {
    glColor3f(1.0, 0.0, 0.0);
    
    const int segments = 20;
    const float PI = 3.14159265359f;
    float halfSize = size/2.0f;
    
    glPushMatrix();
    glTranslatef(0.0f, -0.1f*size, 0.0f);
    glScalef(1.0f, 0.7f, 1.0f);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, -halfSize, 0.0f);  
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex3f(halfSize * cosf(angle), -halfSize * 0.8f, halfSize * sinf(angle));
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = cosf(angle) * halfSize;
        float z = sinf(angle) * halfSize;
        glVertex3f(x, -halfSize * 0.8f, z);  
        glVertex3f(x * 1.1f, halfSize * 0.5f, z * 1.1f);  
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.25f*size, 0.0f);
    glScalef(1.1f, 0.3f, 1.1f);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, halfSize*0.5f, 0.0f); 
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex3f(halfSize * cosf(angle), 0.0f, halfSize * sinf(angle));
    }
    glEnd();
    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex3f(halfSize * cosf(angle), 0.0f, halfSize * sinf(angle));
        glVertex3f(halfSize * 0.8f * cosf(angle), -halfSize, halfSize * 0.8f * sinf(angle));
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.7f*halfSize, 0.0f, 0.0f);
    glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.2f, 0.8f);
    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        glVertex3f(halfSize * cosf(angle), halfSize * sinf(angle), 0.0f);
        glVertex3f(halfSize * 0.6f * cosf(angle), halfSize * 0.6f * sinf(angle), halfSize * 2.0f);
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.7f*halfSize, 0.0f, 0.0f);
    glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments/2; i++) {
        float angle = PI * i / (segments/2);
        float x = halfSize * 1.5f * cosf(angle);  
        float y = halfSize * 1.4f * sinf(angle);  
        
        glVertex3f(x * 0.3f, y, -halfSize * 0.5f);  
        glVertex3f(x * 0.3f, y, -halfSize * 0.1f);  
    }
    glEnd();
    glPopMatrix();
}

void init(int width, int height) {
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    glFrustum(-aspect, aspect, -1.0, 1.0, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glRotated(rotAngle, 0, 1, 0);
    glRotated(rotAngle1, 1, 0, 0);

    glEnable(GL_COLOR_MATERIAL);
    drawTeapot(0.8f);

    glPopMatrix();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_A:
                rotAngle += 5;
                break;
            case GLFW_KEY_Y:
                rotAngle1 += 5;
                break;
            case GLFW_KEY_B:
                rotAngle1 -= 5;
                break;
            case GLFW_KEY_L:
                rotAngle -= 5;
                break;
            case GLFW_KEY_Q:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    init(width, height);
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    
    GLFWwindow* window = glfwCreateWindow(800, 800, "TEKO", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    init(width, height);
    
    while (!glfwWindowShouldClose(window)) {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}