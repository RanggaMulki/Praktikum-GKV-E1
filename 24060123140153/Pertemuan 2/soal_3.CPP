#include <GL/glew.h>
#include <GLFW/glfw3.h>

void drawCube(float x, float y, float size, float r, float g, float b) {
    glBegin(GL_QUADS);
    glColor3f(r, g, b);
    glVertex2f(x - size, y + size);
    glVertex2f(x + size, y + size);
    glVertex2f(x + size, y - size);
    glVertex2f(x - size, y - size);
    glEnd();
}

void drawCreativeStackedCubes() {
    float startX = 0.0f;
    float startY = -0.5f;
    float size = 0.1f;
    float colors[5][3] = {
        {1.0f, 0.0f, 0.0f},  // Red
        {0.0f, 1.0f, 0.0f},  // Green
        {0.0f, 0.0f, 1.0f},  // Blue
        {1.0f, 1.0f, 0.0f},  // Yellow
        {1.0f, 0.0f, 1.0f}   // Magenta
    };
    
    for (int i = 0; i < 5; i++) {
        float offsetX = (i % 2 == 0) ? -0.05f : 0.05f;
        drawCube(startX + offsetX, startY + (i * 2.2f * size), size, colors[i][0], colors[i][1], colors[i][2]);
    }
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(640, 480, "Creative Stacked Cubes", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) return -1;
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawCreativeStackedCubes();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}