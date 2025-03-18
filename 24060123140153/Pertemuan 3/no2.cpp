#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>

#define M_PI 3.14159265358979323846

float carX = 0.0f;  
float carY = -5.0f;
float carRotation = 0.0f;
float wheelRotation = 0.0f;


typedef struct {
    float x;
    float width;
    float height;
    int colorIndex;
    int windowPattern[8][3]; 
} Building;

#define NUM_BUILDINGS 10
Building buildings[NUM_BUILDINGS];


typedef struct {
    float r, g, b;
} Color;

Color skyBlue = {0.4f, 0.7f, 1.0f};
Color roadGray = {0.0f, 0.0f, 0.0f};
Color buildingColors[] = {
    {0.7f, 0.7f, 0.8f},
    {0.8f, 0.8f, 0.7f},
    {0.6f, 0.6f, 0.7f},
    {0.7f, 0.8f, 0.7f}
};
Color carColor = {0.9f, 0.2f, 0.2f};
Color windowColor = {0.7f, 0.9f, 1.0f};
Color wheelColor = {0.2f, 0.2f, 0.2f};
Color rimColor = {0.8f, 0.8f, 0.8f};
Color detailColor = {0.1f, 0.1f, 0.1f};
Color grassColor = {0.1f, 0.7f, 0.1f};


void initBuildings() {
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        buildings[i].x = -90.0f + i * 20.0f;
        buildings[i].width = 15.0f + (rand() % 5);
        buildings[i].height = 30.0f + (rand() % 50);
        buildings[i].colorIndex = i % 4;
        
       
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 3; col++) {
                buildings[i].windowPattern[row][col] = (rand() % 4 > 0) ? 1 : 0; 
            }
        }
    }
}


void drawCircle(float cx, float cy, float r, int segments, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void drawWheel(float x, float y, float radius) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
    
   
    drawCircle(0, 0, radius, 30, wheelColor);
    
    
    drawCircle(0, 0, radius * 0.7f, 30, rimColor);
    
    
    glColor3f(wheelColor.r, wheelColor.g, wheelColor.b);
    for (int i = 0; i < 5; i++) {
        glRotatef(72.0f, 0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(radius * 0.6f, radius * 0.2f);
        glVertex2f(radius * 0.6f, -radius * 0.2f);
        glEnd();
    }
    
    glPopMatrix();
}


void drawBuilding(Building* building) {
    float x = building->x;
    float width = building->width;
    float height = building->height;
    Color color = buildingColors[building->colorIndex];
    
    
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_QUADS);
    glVertex2f(x, 0.0f);
    glVertex2f(x + width, 0.0f);
    glVertex2f(x + width, height);
    glVertex2f(x, height);
    glEnd();
    
    
    glColor3f(0.9f, 0.9f, 0.4f);  
    
    float windowSize = width / 8;
    float margin = width / 10;
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 3; col++) {
            if (building->windowPattern[row][col]) {  
                glBegin(GL_QUADS);
                glVertex2f(x + margin + col * (windowSize + margin), margin + row * (windowSize + margin));
                glVertex2f(x + margin + windowSize + col * (windowSize + margin), margin + row * (windowSize + margin));
                glVertex2f(x + margin + windowSize + col * (windowSize + margin), margin + windowSize + row * (windowSize + margin));
                glVertex2f(x + margin + col * (windowSize + margin), margin + windowSize + row * (windowSize + margin));
                glEnd();
            }
        }
    }
}


void drawCityBackground() {
    
    glColor3f(skyBlue.r, skyBlue.g, skyBlue.b);
    glBegin(GL_QUADS);
    glVertex2f(-100.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(100.0f, 100.0f);
    glVertex2f(-100.0f, 100.0f);
    glEnd();
    
    
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        drawBuilding(&buildings[i]);
    }
    
    
    glColor3f(roadGray.r, roadGray.g, roadGray.b);
    glBegin(GL_QUADS);
    glVertex2f(-100.0f, -20.0f);
    glVertex2f(100.0f, -20.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(-100.0f, 0.0f);
    glEnd();
    
    
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = -5; i < 5; i++) {
        glBegin(GL_QUADS);
        glVertex2f(i * 20.0f, -10.5f);
        glVertex2f(i * 20.0f + 10.0f, -10.5f);
        glVertex2f(i * 20.0f + 10.0f, -9.5f);
        glVertex2f(i * 20.0f, -9.5f);
        glEnd();
    }
    
    
    glColor3f(grassColor.r, grassColor.g, grassColor.b);
    glBegin(GL_QUADS);
    glVertex2f(-100.0f, -50.0f);
    glVertex2f(100.0f, -50.0f);
    glVertex2f(100.0f, -20.0f);
    glVertex2f(-100.0f, -20.0f);
    glEnd();
}


void drawCar() {
    glPushMatrix();
    
    
    glTranslatef(carX, carY, 0.0f);
    
    
    glRotatef(carRotation, 0.0f, 0.0f, 1.0f);
    
    
    glColor3f(carColor.r, carColor.g, carColor.b);
    glBegin(GL_POLYGON);
    glVertex2f(-15.0f, 0.0f);
    glVertex2f(15.0f, 0.0f);
    glVertex2f(15.0f, 5.0f);
    glVertex2f(10.0f, 5.0f);
    glVertex2f(8.0f, 10.0f);
    glVertex2f(-8.0f, 10.0f);
    glVertex2f(-10.0f, 5.0f);
    glVertex2f(-15.0f, 5.0f);
    glEnd();
    
    
    glColor3f(windowColor.r, windowColor.g, windowColor.b);
    glBegin(GL_QUADS);
    glVertex2f(-7.0f, 5.0f);
    glVertex2f(7.0f, 5.0f);
    glVertex2f(5.0f, 9.0f);
    glVertex2f(-5.0f, 9.0f);
    glEnd();
    
    
    glBegin(GL_QUADS);
    glVertex2f(-9.5f, 5.0f);
    glVertex2f(-7.0f, 5.0f);
    glVertex2f(-7.0f, 9.0f);
    glVertex2f(-8.0f, 9.0f);
    glEnd();
    
    
    glBegin(GL_QUADS);
    glVertex2f(7.0f, 5.0f);
    glVertex2f(9.5f, 5.0f);
    glVertex2f(8.0f, 9.0f);
    glVertex2f(7.0f, 9.0f);
    glEnd();
    
    
    glColor3f(detailColor.r, detailColor.g, detailColor.b);
    glBegin(GL_LINES);
    glVertex2f(-9.0f, 1.0f);
    glVertex2f(-9.0f, 4.0f);
    
   
    glVertex2f(9.0f, 1.0f);
    glVertex2f(9.0f, 4.0f);
    glEnd();
    
    
    glColor3f(1.0f, 1.0f, 0.8f);
    drawCircle(13.0f, 3.0f, 1.5f, 20, (Color){1.0f, 1.0f, 0.8f});
    
    
    drawCircle(-13.0f, 3.0f, 1.5f, 20, (Color){1.0f, 0.2f, 0.2f});
    
    
    drawWheel(-9.0f, -1.0f, 3.0f);
    drawWheel(9.0f, -1.0f, 3.0f);
    
    glPopMatrix();
}

void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT);
    
   
    drawCityBackground();
    
    
    drawCar();
    
    glfwSwapBuffers(window);
}

void reshape(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    
    glOrtho(-100.0, 100.0, -50.0, 100.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Mobil", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    
    srand(40); 
    initBuildings();

    glfwSetFramebufferSizeCallback(window, reshape);

    while (!glfwWindowShouldClose(window)) {
        display(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
