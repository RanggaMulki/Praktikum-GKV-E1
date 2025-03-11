#include <GL/glew.h>
#include <GLFW/glfw3.h>

void gambarBadanRumah() {
    glColor3f(0.8f, 0.5f, 0.2f);  
    glBegin(GL_QUADS);  
    glVertex2f(-0.5f, -0.5f); 
    glVertex2f(0.5f, -0.5f);  
    glVertex2f(0.5f, 0.5f);   
    glVertex2f(-0.5f, 0.5f);  
    glEnd();
}

void gambarAtap() {
    glColor3f(0.9f, 0.1f, 0.1f);  
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7f, 0.5f);  
    glVertex2f(0.7f, 0.5f);   
    glVertex2f(0.0f, 1.0f);   
    glEnd();
}

void gambarPintu() {
    glColor3f(0.4f, 0.2f, 0.0f);  
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.5f);  
    glVertex2f(0.15f, -0.5f);   
    glVertex2f(0.15f, 0.0f);    
    glVertex2f(-0.15f, 0.0f);   
    glEnd();
}

void gambarJendela() {
    glColor3f(0.0f, 0.0f, 1.0f);  
    glBegin(GL_QUADS);
    glVertex2f(-0.35f, 0.0f);   
    glVertex2f(-0.05f, 0.0f);   
    glVertex2f(-0.05f, 0.3f);   
    glVertex2f(-0.35f, 0.3f);   
    glEnd();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Rumah Sederhana", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        gambarBadanRumah();   
        gambarAtap();   
        gambarPintu();   
        gambarJendela();   

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
