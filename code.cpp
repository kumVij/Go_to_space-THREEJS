#include <GL/glut.h>
#include <cmath>

// Room dimensions
const float WIDTH = 10.0f;
const float HEIGHT = 5.0f;
const float DEPTH = 10.0f;

// Lighting controls
float sunlight = 0.8f;
bool ceilingLight = true;
bool lampLight = true;
bool fanOn = true;
float fanAngle = 0.0f;

// Camera position
float camX = 0, camY = 1.8f, camZ = 3.0f;
float lookX = 0, lookY = 1.5f, lookZ = 0;
float angle = 0.0f;

// Colors
float wallColor[] = { 0.8f, 0.8f, 0.9f };
float floorColor[] = { 0.6f, 0.4f, 0.2f };
float sofaColor[] = { 0.5f, 0.2f, 0.2f };
float tableColor[] = { 0.4f, 0.25f, 0.1f };
float tvColor[] = { 0.1f, 0.1f, 0.1f };
float lampColor[] = { 1.0f, 1.0f, 0.8f };

void setupLights() {
    glEnable(GL_LIGHTING);

    // Sunlight
    glEnable(GL_LIGHT0);
    float sunPos[] = { -0.5f, -1.0f, -0.5f, 0.0f };
    float sunColor[] = { sunlight, sunlight, sunlight, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunColor);

    // Ceiling light
    if (ceilingLight) {
        glEnable(GL_LIGHT1);
        float lightPos[] = { 0.0f, HEIGHT - 0.1f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lampColor);
    }
    else {
        glDisable(GL_LIGHT1);
    }

    // Table lamp
    if (lampLight) {
        glEnable(GL_LIGHT2);
        float lampPos[] = { 2.5f, 1.0f, 3.5f, 1.0f };
        float lampDir[] = { 0.0f, -1.0f, 0.5f };
        glLightfv(GL_LIGHT2, GL_POSITION, lampPos);
        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lampDir);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0f);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, lampColor);
    }
    else {
        glDisable(GL_LIGHT2);
    }
}

void drawRoom() {
    // Floor
    glColor3fv(floorColor);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(-WIDTH / 2, 0, -DEPTH / 2);
    glVertex3f(WIDTH / 2, 0, -DEPTH / 2);
    glVertex3f(WIDTH / 2, 0, DEPTH / 2);
    glVertex3f(-WIDTH / 2, 0, DEPTH / 2);
    glEnd();

    // Walls
    glColor3fv(wallColor);
    // Back wall
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-WIDTH / 2, 0, -DEPTH / 2);
    glVertex3f(WIDTH / 2, 0, -DEPTH / 2);
    glVertex3f(WIDTH / 2, HEIGHT, -DEPTH / 2);
    glVertex3f(-WIDTH / 2, HEIGHT, -DEPTH / 2);
    glEnd();

    // Left wall (different color)
    float leftWallColor[] = { 0.8f, 0.7f, 0.6f };
    glColor3fv(leftWallColor);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(-WIDTH / 2, 0, -DEPTH / 2);
    glVertex3f(-WIDTH / 2, 0, DEPTH / 2);
    glVertex3f(-WIDTH / 2, HEIGHT, DEPTH / 2);
    glVertex3f(-WIDTH / 2, HEIGHT, -DEPTH / 2);
    glEnd();

    // Right wall (different color)
    float rightWallColor[] = { 0.7f, 0.8f, 0.7f };
    glColor3fv(rightWallColor);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(WIDTH / 2, 0, -DEPTH / 2);
    glVertex3f(WIDTH / 2, 0, DEPTH / 2);
    glVertex3f(WIDTH / 2, HEIGHT, DEPTH / 2);
    glVertex3f(WIDTH / 2, HEIGHT, -DEPTH / 2);
    glEnd();

    // Ceiling
    float ceilingColor[] = { 1.0f, 1.0f, 1.0f };
    glColor3fv(ceilingColor);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(-WIDTH / 2, HEIGHT, -DEPTH / 2);
    glVertex3f(WIDTH / 2, HEIGHT, -DEPTH / 2);
    glVertex3f(WIDTH / 2, HEIGHT, DEPTH / 2);
    glVertex3f(-WIDTH / 2, HEIGHT, DEPTH / 2);
    glEnd();
}

void drawWindow() {
    // Window frame
    float frameColor[] = { 0.3f, 0.25f, 0.2f };
    glColor3fv(frameColor);
    glPushMatrix();
    glTranslatef(0, 2.0f, -DEPTH / 2 + 0.01f);
    glScalef(3.2f, 2.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Window glass (transparent)
    float glassColor[] = { 0.5f, 0.8f, 1.0f, 0.7f };
    glColor4fv(glassColor);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-1.5f, 1.0f, -DEPTH / 2 + 0.02f);
    glVertex3f(1.5f, 1.0f, -DEPTH / 2 + 0.02f);
    glVertex3f(1.5f, 3.0f, -DEPTH / 2 + 0.02f);
    glVertex3f(-1.5f, 3.0f, -DEPTH / 2 + 0.02f);
    glEnd();
    glDisable(GL_BLEND);
}

void drawSofa() {
    glColor3fv(sofaColor);
    // Base
    glPushMatrix();
    glTranslatef(-3.0f, 0.5f, 2.0f);
    glScalef(2.5f, 0.5f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Back
    glPushMatrix();
    glTranslatef(-3.0f, 1.25f, 1.5f);
    glScalef(2.5f, 1.5f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawTable() {
    glColor3fv(tableColor);
    // Table top
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, 2.0f);
    glScalef(1.5f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Legs
    glPushMatrix();
    glTranslatef(-0.7f, 0.2f, 2.4f);
    glScalef(0.1f, 0.4f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, 0.2f, 2.4f);
    glScalef(0.1f, 0.4f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7f, 0.2f, 1.6f);
    glScalef(0.1f, 0.4f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, 0.2f, 1.6f);
    glScalef(0.1f, 0.4f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawTV() {
    glColor3fv(tvColor);
    // TV screen
    glPushMatrix();
    glTranslatef(3.0f, 1.5f, -4.9f);
    glScalef(2.0f, 1.2f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawLamp() {
    glColor3fv(lampColor);
    glPushMatrix();
    glTranslatef(2.5f, 1.0f, 3.5f);
    glutSolidSphere(0.2f, 20, 20);
    glPopMatrix();
}

void drawFan() {
    if (fanOn) fanAngle += 2.0f;

    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, HEIGHT - 0.3f, 0.0f);
    glutSolidSphere(0.1f, 20, 20);

    glRotatef(fanAngle, 0.0f, 1.0f, 0.0f);
    for (int i = 0; i < 4; i++) {
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
        glTranslatef(0.8f, 0.0f, 0.0f);
        glScalef(1.5f, 0.05f, 0.3f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ,
        lookX, lookY, lookZ,
        0.0f, 1.0f, 0.0f);

    setupLights();

    drawRoom();
    drawWindow();
    drawSofa();
    drawTable();
    drawTV();
    drawLamp();
    drawFan();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    float moveStep = 0.2f;

    switch (key) {
    case 'w': camZ -= moveStep; break;
    case 's': camZ += moveStep; break;
    case 'a': camX -= moveStep; break;
    case 'd': camX += moveStep; break;
    case 'q': camY += moveStep; break;
    case 'e': camY -= moveStep; break;
    case 'i': sunlight += 0.1f; if (sunlight > 1.5f) sunlight = 1.5f; break;
    case 'k': sunlight -= 0.1f; if (sunlight < 0.0f) sunlight = 0.0f; break;
    case 'o': ceilingLight = !ceilingLight; break;
    case 'l': lampLight = !lampLight; break;
    case 'f': fanOn = !fanOn; break;
    case 27: exit(0);
    }

    // Update look-at point to be in front of camera
    lookX = camX + sin(angle);
    lookZ = camZ - cos(angle);

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    float rotateStep = 0.1f;

    switch (key) {
    case GLUT_KEY_LEFT: angle -= rotateStep; break;
    case GLUT_KEY_RIGHT: angle += rotateStep; break;
    case GLUT_KEY_UP: camY += 0.1f; break;
    case GLUT_KEY_DOWN: camY -= 0.1f; break;
    }

    // Update look-at point when rotating
    lookX = camX + sin(angle);
    lookZ = camZ - cos(angle);

    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Set up lighting model
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)w / (double)h, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Living Room");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}