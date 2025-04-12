#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846


float fanPosX = 0.0f, fanPosY = 1.6f, fanPosZ = 0.0f; 
float bladeAngle = 0.0f; /
float camAngle = 0.0f; 
float camDistance = 5.0f; 
float camHeight = 1.6f;


const GLfloat light0_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
const GLfloat light0_diffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
const GLfloat light0_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light0_position[] = {2.5f, 2.5f, 2.5f, 1.0f};
const GLfloat light1_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f}; 
const GLfloat light1_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat light1_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat light1_position[] = {-2.0f, 1.5f, -2.0f, 1.0f};
const GLfloat light2_ambient[] = {0.05f, 0.05f, 0.05f, 1.0f}; 
const GLfloat light2_diffuse[] = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat light2_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
const GLfloat light2_position[] = {0.0f, 2.0f, -3.0f, 1.0f};
const GLfloat fan_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f}; 
const GLfloat fan_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat fan_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat fan_shininess[] = {100.0f};
const GLfloat stand_ambient[] = {0.0f, 0.0f, 0.8f, 1.0f}; 
const GLfloat stand_diffuse[] = {0.0f, 0.0f, 1.0f, 1.0f};

void setupCamera(int width, int height) {
    if (height == 0) height = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, (float)width / height, 0.1f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float camX = fanPosX + sin(camAngle) * camDistance;
    float camZ = fanPosZ + cos(camAngle) * camDistance;
    float camY = fanPosY + camHeight;
    gluLookAt(camX, camY, camZ, fanPosX, fanPosY, fanPosZ, 0.0f, 1.0f, 0.0f);
}

void drawGrid() {
    const float size = 15.0f;
    const float gap = 0.5f;
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (float i = -size; i <= size; i += gap) {
        glVertex3f(-size, 0.0f, i);
        glVertex3f(size, 0.0f, i);
        glVertex3f(i, 0.0f, -size);
        glVertex3f(i, 0.0f, size);
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void drawStand() {
    const float base_radius = 0.7f;
    const float base_height = 0.15f;
    const float pole_width = 0.08f;
    const float pole_height = 1.45f;
    const float panel_width = 0.2f;
    const float panel_height = 0.1f;
    const float panel_depth = 0.05f;
    const int segments = 24;
    glPushMatrix();
    glTranslatef(fanPosX, 0.0f, fanPosZ);
    glMaterialfv(GL_FRONT, GL_AMBIENT, stand_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, stand_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, fan_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, fan_shininess);

    
    for (int i = 0; i < segments; i++) {
        float theta1 = (float)i / segments * 2.0f * M_PI;
        float theta2 = (float)(i + 1) / segments * 2.0f * M_PI;
        float x1 = base_radius * cos(theta1);
        float z1 = base_radius * sin(theta1);
        float x2 = base_radius * cos(theta2);
        float z2 = base_radius * sin(theta2);

        glBegin(GL_QUADS);
        glNormal3f(cos((theta1 + theta2) / 2), 0.0f, sin((theta1 + theta2) / 2));
        glVertex3f(x1, base_height, z1);
        glVertex3f(x2, base_height, z2);
        glVertex3f(x2, 0.0f, z2);
        glVertex3f(x1, 0.0f, z1);
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, base_height, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float theta = (float)i / segments * 2.0f * M_PI;
        glVertex3f(base_radius * cos(theta), base_height, base_radius * sin(theta));
    }
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-pole_width / 2, base_height, pole_width / 2);
    glVertex3f(-pole_width / 2, base_height + pole_height, pole_width / 2);
    glVertex3f(pole_width / 2, base_height + pole_height, pole_width / 2);
    glVertex3f(pole_width / 2, base_height, pole_width / 2);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-pole_width / 2, base_height, -pole_width / 2);
    glVertex3f(pole_width / 2, base_height, -pole_width / 2);
    glVertex3f(pole_width / 2, base_height + pole_height, -pole_width / 2);
    glVertex3f(-pole_width / 2, base_height + pole_height, -pole_width / 2);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-pole_width / 2, base_height, -pole_width / 2);
    glVertex3f(-pole_width / 2, base_height + pole_height, -pole_width / 2);
    glVertex3f(-pole_width / 2, base_height + pole_height, pole_width / 2);
    glVertex3f(-pole_width / 2, base_height, pole_width / 2);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(pole_width / 2, base_height, -pole_width / 2);
    glVertex3f(pole_width / 2, base_height, pole_width / 2);
    glVertex3f(pole_width / 2, base_height + pole_height, pole_width / 2);
    glVertex3f(pole_width / 2, base_height + pole_height, -pole_width / 2);
    glEnd();

    glTranslatef(0.0f, base_height + pole_height / 2, pole_width / 2 + 0.01f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-panel_width / 2, -panel_height / 2, panel_depth / 2);
    glVertex3f(-panel_width / 2, panel_height / 2, panel_depth / 2);
    glVertex3f(panel_width / 2, panel_height / 2, panel_depth / 2);
    glVertex3f(panel_width / 2, -panel_height / 2, panel_depth / 2);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-panel_width / 2, -panel_height / 2, -panel_depth / 2);
    glVertex3f(panel_width / 2, -panel_height / 2, -panel_depth / 2);
    glVertex3f(panel_width / 2, panel_height / 2, -panel_depth / 2);
    glVertex3f(-panel_width / 2, panel_height / 2, -panel_depth / 2);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-panel_width / 2, -panel_height / 2, -panel_depth / 2);
    glVertex3f(-panel_width / 2, panel_height / 2, -panel_depth / 2);
    glVertex3f(-panel_width / 2, panel_height / 2, panel_depth / 2);
    glVertex3f(-panel_width / 2, -panel_height / 2, panel_depth / 2);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(panel_width / 2, -panel_height / 2, -panel_depth / 2);
    glVertex3f(panel_width / 2, -panel_height / 2, panel_depth / 2);
    glVertex3f(panel_width / 2, panel_height / 2, panel_depth / 2);
    glVertex3f(panel_width / 2, panel_height / 2, -panel_depth / 2);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-panel_width / 2, -panel_height / 2, -panel_depth / 2);
    glVertex3f(-panel_width / 2, -panel_height / 2, panel_depth / 2);
    glVertex3f(panel_width / 2, -panel_height / 2, panel_depth / 2);
    glVertex3f(panel_width / 2, -panel_height / 2, -panel_depth / 2);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-panel_width / 2, panel_height / 2, -panel_depth / 2);
    glVertex3f(panel_width / 2, panel_height / 2, -panel_depth / 2);
    glVertex3f(panel_width / 2, panel_height / 2, panel_depth / 2);
    glVertex3f(-panel_width / 2, panel_height / 2, panel_depth / 2);
    glEnd();
    glPopMatrix();
}

void drawFanHub() {
    const float radius = 0.2f;
    const float height = 0.2f;
    const int segments = 24;
    glPushMatrix();
    glTranslatef(fanPosX, fanPosY, fanPosZ);
    glMaterialfv(GL_FRONT, GL_AMBIENT, fan_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, fan_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, fan_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, fan_shininess);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < segments; i++) {
        float theta1 = (float)i / segments * 2.0f * M_PI;
        float theta2 = (float)(i + 1) / segments * 2.0f * M_PI;
        float x1 = radius * cos(theta1);
        float z1 = radius * sin(theta1);
        float x2 = radius * cos(theta2);
        float z2 = radius * sin(theta2);

        glBegin(GL_QUADS);
        glNormal3f(cos((theta1 + theta2) / 2), 0.0f, sin((theta1 + theta2) / 2));
        glVertex3f(x1, height / 2, z1);
        glVertex3f(x2, height / 2, z2);
        glVertex3f(x2, -height / 2, z2);
        glVertex3f(x1, -height / 2, z1);
        glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, height / 2);
    for (int i = 0; i <= segments; i++) {
        float theta = (float)i / segments * 2.0f * M_PI;
        glVertex3f(radius * cos(theta), radius * sin(theta), height / 2);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -height / 2);
    for (int i = 0; i <= segments; i++) {
        float theta = (float)(segments - i) / segments * 2.0f * M_PI;
        glVertex3f(radius * cos(theta), radius * sin(theta), -height / 2);
    }
    glEnd();
    glPopMatrix();
}

void drawFanBlade() {
    const float length = 1.0f;
    const float width_base = 0.25f;
    const float width_tip = 0.15f;
    const float thickness = 0.02f;
    const float curve = 0.08f;
    const float tilt = 10.0f;
    glPushMatrix();
    glRotatef(tilt, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, fan_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, fan_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, fan_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, fan_shininess);
    glBegin(GL_QUADS);
    
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, -width_base / 2, thickness / 2);
    glVertex3f(0.0f, width_base / 2, thickness / 2);
    glVertex3f(length, width_tip / 2, thickness / 2 + curve);
    glVertex3f(length, -width_tip / 2, thickness / 2 + curve);
    
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -width_base / 2, -thickness / 2);
    glVertex3f(length, -width_tip / 2, -thickness / 2 - curve);
    glVertex3f(length, width_tip / 2, -thickness / 2 - curve);
    glVertex3f(0.0f, width_base / 2, -thickness / 2);
    
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -width_base / 2, thickness / 2);
    glVertex3f(length, -width_tip / 2, thickness / 2 + curve);
    glVertex3f(length, -width_tip / 2, -thickness / 2 - curve);
    glVertex3f(0.0f, -width_base / 2, -thickness / 2);
    
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, width_base / 2, thickness / 2);
    glVertex3f(0.0f, width_base / 2, -thickness / 2);
    glVertex3f(length, width_tip / 2, -thickness / 2 - curve);
    glVertex3f(length, width_tip / 2, thickness / 2 + curve);
    
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -width_base / 2, thickness / 2);
    glVertex3f(0.0f, -width_base / 2, -thickness / 2);
    glVertex3f(0.0f, width_base / 2, -thickness / 2);
    glVertex3f(0.0f, width_base / 2, thickness / 2);
    
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(length, -width_tip / 2, thickness / 2 + curve);
    glVertex3f(length, width_tip / 2, thickness / 2 + curve);
    glVertex3f(length, width_tip / 2, -thickness / 2 - curve);
    glVertex3f(length, -width_tip / 2, -thickness / 2 - curve);
    glEnd();

    
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(length / 2, -width_tip / 4, thickness / 2 + 0.002f);
    glVertex3f(length / 2, width_tip / 4, thickness / 2 + 0.002f);
    glVertex3f(length, width_tip / 4, thickness / 2 + curve);
    glVertex3f(length, -width_tip / 4, thickness / 2 + curve);
    glEnd();
    glPopMatrix();
}

void drawFan() {
    drawStand();
    drawFanHub();
    glPushMatrix();
    glTranslatef(fanPosX, fanPosY, fanPosZ);
    glRotatef(bladeAngle, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.2f, 0.0f, 0.0f);
        drawFanBlade();
        glPopMatrix();
    }
    glPopMatrix();
}

void lighting() {
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_NORMALIZE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    setupCamera(width, height);
}

void processInput(GLFWwindow* window, float deltaTime) {
    const float moveSpeed = 2.0f; 
    const float rotateSpeed = 1.0f; 

    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        fanPosZ -= moveSpeed * deltaTime; 
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        fanPosZ += moveSpeed * deltaTime; 
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        fanPosX -= moveSpeed * deltaTime; 
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        fanPosX += moveSpeed * deltaTime; 

    // Camera rotation with arrow keys
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camAngle -= rotateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camAngle += rotateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camDistance = fmax(2.5f, camDistance - moveSpeed * deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camDistance = fmin(10.0f, camDistance + moveSpeed * deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    GLFWwindow* window = glfwCreateWindow(800, 600, "KIPAS", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    init();
    lighting();

    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        float deltaTime = (float)(currentTime - lastTime);
        lastTime = currentTime;

        processInput(window, deltaTime);
        bladeAngle += 540.0f * deltaTime; // ~1.5 rotations/second
        if (bladeAngle >= 360.0f) bladeAngle -= 360.0f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        setupCamera(width, height);
        drawGrid();
        drawFan();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}