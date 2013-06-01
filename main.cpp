#include "body.h"
#include <GL/glut.h>
#include <vector>

std::vector<Body> solarSystem;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (auto &i: solarSystem)
    {
        glVertex2f(i.coord.x, i.coord.y);
    }
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    //                     Name       Mass        Radius     Coord                   Velocity 
    solarSystem.push_back({"Sun",     1.9891E+30, 6.96342E+8, { 0, 0, 0 },             {0,  0, 0}});
    solarSystem.push_back({"Mercury", 3.3022E+23, 2439.7E+3,  {  69816900E+3,  0, 0 }, {47.87E+3, 0, 0}});
    solarSystem.push_back({"Venus",   4.8685E+24, 6051.8E+3,  { 108939000E+3,  0, 0 }, {35.02E+3, 0, 0}});
    solarSystem.push_back({"Earth",   5.9736E+24, 6371.0E+3,  { 152098232E+3,  0, 0 }, {29.78E+3, 0, 0}});
    solarSystem.push_back({"Mars",    6.4185E+23, 3396.2E+3,  { 249209300E+3,  0, 0 }, {24.08E+3, 0, 0}});
    solarSystem.push_back({"Jupiter", 1.8986E+27, 71492E+3,   { 816520800E+3,  0, 0 }, {13.07E+3, 0, 0}});
    solarSystem.push_back({"Saturn",  5.6846E+26, 60268E+3,   { 1513325783E+3, 0, 0 }, {9.69E+3,  0, 0}});
    solarSystem.push_back({"Uranus",  8.6810E+25, 25559E+3,   { 3004419704E+3, 0, 0 }, {6.81E+3,  0, 0}});
    solarSystem.push_back({"Neptune", 1.0243E+26, 24764E+3,   { 4553946490E+3, 0, 0 }, {5.43E+3,  0, 0}});
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 700); 
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Solar System");
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4553946490E+3, 4553946490E+3, 4553946490E+3, -4553946490E+3, -1.0, 1.0);
    glutDisplayFunc(display);

    glutMainLoop();
}

