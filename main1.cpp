//
//  main.cpp
//  a4
//
//  Created by Braden Katzman on 7/18/15.
//  Copyright (c) 2015 Braden Katzman. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>

void initOpenGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //sets the near plane at 1 and a far plane at 5
    glFrustum(-1,1,-1,1,1,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //sets the camera center at (0, 0, 0), looking down at (0, 0, -1) --> negative z-axis
    gluLookAt(0,0,0,0,0,-1,0,1,0);
}
void display() {
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    //set line width
    glLineWidth(8.0);
    
    //points must have z coordinates within the interval [-1 - -5] to be visible
    glBegin(GL_LINES);
    //set color of lines to red
    glColor3f(1.0f, 0.0f, 0.0f);
    
    //parameter order: (x1, y1, z1)
    //                 (x2, y2, z2)
    
    //top horizontal bar of S
    glVertex3f(-0.5, 0.5, -2);
    glVertex3f(0.5, 0.5, -2);
    
    //top left vertical bar of S
    glVertex3f(-0.48, 0.5, -2);
    glVertex3f(-0.48, 0.1, -2);
    
    //middle horizontal bar of S
    glVertex3f(-0.5, 0.1, -2);
    glVertex3f(0.5, 0.1, -2);
    
    //lower right vertical bar of S
    glVertex3f(0.48, 0.1, -2);
    glVertex3f(0.48, -0.3, -2);
    
    //bottom vertical bar of S
    glVertex3f(0.5, -0.3, -2);
    glVertex3f(-0.5, -0.3, -2);
    glEnd();
    
    
    glBegin(GL_TRIANGLES);
    //set color of middle triangle to green
    glColor3f(0.0f, 1.0f, 0.0f);
    
    //TREE VERTICES
    //bottom left vertex
    glVertex3f(-.2, -.18, -2);
    
    //bottom right vertex
    glVertex3f(0.2, -.18, -2);
    
    //top vertex
    glVertex3f(0, .6, -2);
    
    //STUMP #1 VERTICES
    //set color to brown
    glColor3f(0.545098f, 0.270588f, 0.0745098f);
    
    //bottom left vertex
    
    glVertex3f(-.1, -.35, -2);
    
    //bottom right vetex
    glVertex3f(.1, -.35, -2);
    
    //top right vertex
    glVertex3f(.1, -.18, -2);
    
    //STUMP #2 VERTICES
    //set color to brown
    glColor3f(0.545098f, 0.270588f, 0.0745098f);
    
    //top right vertex
    glVertex3f(.1, -.18, -2);
    
    //top left vertex
    glVertex3f(-.1, -.18, -2);
    
    //bottom left vertex
    glVertex3f(-.1, -.35, -2);
    
    glEnd();
    
    
    
    glFlush(); //forces execution, clears buffer
}
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Stanford Logo with OpenGL");
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
