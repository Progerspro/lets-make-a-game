#include "body.h"
#include <GL/glut.h>
#include <vector>
#include <mutex>
#include <cmath>
#include <thread>

std::vector<Body> solarSystem;
std::mutex mutex;
const auto G = 6.67384E-11; // m^3 kg^-1 s^-2
const auto DT = 50.0; // s
auto viewRadius = 4553946490E+3;

double sqr(double x)
{
    return x * x;
}

void physics()
{
    // vector form of Newton's law of universal gravitation
    // F_12 = -G * (m_1 * m_2) / (r_12)^2 * r^12
    for (;;)
    {
        std::lock_guard<std::mutex> l(mutex);
        for (auto &i: solarSystem)
        {
            Vector3 a = { 0, 0, 0 };
            for (auto &j: solarSystem)
            {
                if (&i == &j)
                    continue;
                double D2 = (sqr(i.coord.x - j.coord.x) + sqr(i.coord.y - j.coord.y) + sqr(i.coord.z - j.coord.z));
                if (D2 < 0.01)
                    continue;
                double D = sqrt(D2);
                auto tmpA = G * j.mass / D2;
                double uvx = (j.coord.x - i.coord.x) / D;
                double uvy = (j.coord.y - i.coord.y) / D;
                double uvz = (j.coord.z - i.coord.z) / D;
                a.x += tmpA * uvx;
                a.y += tmpA * uvy;
                a.z += tmpA * uvz;
            }
            i.velocity.x += a.x * DT;
            i.velocity.y += a.y * DT;
            i.velocity.z += a.z * DT;
            i.coord.x += i.velocity.x * DT;
            i.coord.y += i.velocity.y * DT;
            i.coord.z += i.velocity.z * DT;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    std::lock_guard<std::mutex> l(mutex);
    for (auto &i: solarSystem)
        glVertex2f(i.coord.x, i.coord.y);
    glEnd();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
   if ((button == 3) || (button == 4)) // It's a wheel event
   {
       if (state == GLUT_UP) 
           return; 
       
       switch (button)
       {
       case 3:
           viewRadius /= 1.1;
           break;
       case 4:
           viewRadius *= 1.1;
           break;
       }
       glLoadIdentity();
       glOrtho(-viewRadius, viewRadius, viewRadius, -viewRadius, -1.0, 1.0);
   }
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    //                     Name       Mass        Radius     Coord                   Velocity 
    solarSystem.push_back({"Sun",     1.9891E+30, 6.96342E+8, { 0, 0, 0 },             {0,  0, 0}});
    solarSystem.push_back({"Mercury", 3.3022E+23, 2439.7E+3,  {  69816900E+3,  0, 0 }, {0, -47.87E+3, 0}});
    solarSystem.push_back({"Venus",   4.8685E+24, 6051.8E+3,  { 0,  108939000E+3, 0 }, {35.02E+3, 0, 0}});
    solarSystem.push_back({"Earth",   5.9736E+24, 6371.0E+3,  { -152098232E+3,  0, 0 }, {0, 29.78E+3, 0}});
    solarSystem.push_back({"Mars",    6.4185E+23, 3396.2E+3,  { 0,  -249209300E+3, 0 }, {-24.08E+3, 0, 0}});
    solarSystem.push_back({"Jupiter", 1.8986E+27, 71492E+3,   { 816520800E+3,  0, 0 }, {0, -13.07E+3, 0}});
    solarSystem.push_back({"Saturn",  5.6846E+26, 60268E+3,   { 0, 1513325783E+3, 0 }, {9.69E+3, 0,  0}});
    solarSystem.push_back({"Uranus",  8.6810E+25, 25559E+3,   { -3004419704E+3, 0, 0 }, {0, 6.81E+3,  0}});
    solarSystem.push_back({"Neptune", 1.0243E+26, 24764E+3,   { 0, -4553946490E+3, 0 }, {-5.43E+3, 0,  0}});
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 700); 
    glutInitWindowPosition(100, 200);
    glutCreateWindow("Solar System");
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-viewRadius, viewRadius, viewRadius, -viewRadius, -1.0, 1.0);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);

    std::thread t(physics);

    glutMainLoop();
}

