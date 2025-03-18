#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath> 

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void gambarLingkaran() {
    const int jumlahTitik = 100; 
    const float jariJari = 0.5f; 

    glColor3f(0.0f, 0.0f, 1.0f); 

    glBegin(GL_LINE_LOOP); 
    for (int i = 0; i < jumlahTitik; i++) {
        float sudut = 2.0f * M_PI * i / jumlahTitik; 
        glVertex2f(jariJari * cos(sudut), jariJari * sin(sudut)); 
    }
    glEnd(); 
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Lingkaran Biru Besar", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); 

        
        glLoadIdentity(); 
        glTranslatef(0.0f, 0.0f, 0.0f); 
        gambarLingkaran(); 

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
