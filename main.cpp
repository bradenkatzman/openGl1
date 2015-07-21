//
//  main.cpp
//  a4
//
//  Created by Braden Katzman on 7/18/15.
//  Copyright (c) 2015 Braden Katzman. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>

using namespace std;

static double zoomFactor = 1.0;

void initOpenGL(float zoomFactor) {
    //these commands ensure that drawing commands affect the projection matrix, rather than the model view matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //sets the near plane at 1 and a far plane at 5
    //parameters (left, right, bottom, top, near, far)
    glFrustum(-2.0,2.0,-2.0,2.0,1.0,5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
    //sets the camera center at (0, 0, 0), looking down at (0, 0, -1) --> negative z-axis
    gluLookAt(0,0,0,0,0,-1,0,1,0);
}
void display() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    //set line width
    glLineWidth(8.0f);
    
    //points must have z coordinates within the interval [-1 - -5] to be visible
    glBegin(GL_LINES);
        //set color of lines to red
        glColor3f(1.0f, 0.0f, 0.0f);
    
        //parameter order: (x1, y1, z1)
        //                 (x2, y2, z2)
    
        //top horizontal bar of S
        glVertex3f(-0.5f, 0.5f, -2.0f);
        glVertex3f(0.5f, 0.5f, -2.0f);
    
        //top left vertical bar of S
        glVertex3f(-0.48f, 0.5f, -2.0f);
        glVertex3f(-0.48f, 0.1f, -2.0f);
    
        //middle horizontal bar of S
        glVertex3f(-0.5f, 0.1f, -2.0f);
        glVertex3f(0.5f, 0.1f, -2.0f);
    
        //lower right vertical bar of S
        glVertex3f(0.48f, 0.1f, -2.0f);
        glVertex3f(0.48f, -0.3f, -2.0f);
    
        //bottom vertical bar of S
        glVertex3f(0.5f, -0.3f, -2.0f);
        glVertex3f(-0.5f, -0.3f, -2.0f);
    glEnd();
    
    
    glBegin(GL_TRIANGLES);
        //set color of middle triangle to green
        glColor3f(0.0f, 1.0f, 0.0f);
    
    //TREE VERTICES
        //bottom left vertex
        glVertex3f(-.2f, -.18f, -2.0f);
    
        //bottom right vertex
        glVertex3f(0.2f, -.18f, -2.0f);
    
        //top vertex
        glVertex3f(0.0f, .6f, -2.0f);
    
    //STUMP #1 VERTICES
        //set color to brown
        glColor3f(0.545098f, 0.270588f, 0.0745098f);
    
        //bottom left vertex
    
        glVertex3f(-.1f, -.35f, -2.0f);
    
        //bottom right vetex
        glVertex3f(.1f, -.35f, -2.0f);
    
        //top right vertex
        glVertex3f(.1f, -.18f, -2.0f);
    
    //STUMP #2 VERTICES
        //set color to brown
        glColor3f(0.545098f, 0.270588f, 0.0745098f);
    
        //top right vertex
        glVertex3f(.1f, -.18f, -2.0f);
    
        //top left vertex
        glVertex3f(-.1f, -.18f, -2.0f);
    
        //bottom left vertex
        glVertex3f(-.1f, -.35f, -2.0f);
    
    glEnd();
    
    
    
    glFlush(); //forces execution, clears buffer
}

//zoom resource: https://www.opengl.org/archives/resources/faq/technical/viewing.htm
void key(unsigned char key, int x, int y) {
    switch (key) {
            //0 is zoom in
            case 'o':
                zoomFactor = 2.0;
                cout << 2.0*zoomFactor << endl;
                glFrustum(-2.0*zoomFactor,2.0*zoomFactor,-2.0*zoomFactor,2.0*zoomFactor,1.0*zoomFactor,5.0*zoomFactor);
                glutPostRedisplay();
            break;
            
            //i is zoom out
            case 'i':
                zoomFactor = 1.0/2.0;
                cout << -2.0*zoomFactor << endl;
                glFrustum(-2.0*zoomFactor,2.0*zoomFactor,-2.0*zoomFactor,2.0*zoomFactor,1.0*zoomFactor,5.0*zoomFactor);
                glutPostRedisplay();
            break;
            
            //r is reset
            case 'r':
            cout << "reset" << endl;
                glFrustum(-2.0,2.0,-2.0,2.0,1.0,5.0);
                glutPostRedisplay();
            break;
    }
}

//adapted from: https://www.opengl.org/discussion_boards/showthread.php/173157-Glut-Mouse-Func
void rotate(int button, int state, int x, int y){
    //right quadrant
    if (x < 256){
        glRotated(5.0, 0.0, 0.0, 10.0);
    }
    
    //left quadrant
    if (x > 256){
        glRotated(-5.0, 0.0, 0.0, 10.0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    
    //window initialization
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Stanford Logo with OpenGL");
   
    //initialize state
    initOpenGL(zoomFactor);
    glutDisplayFunc(display);
    
    //callbacks
    glutKeyboardFunc(key);
    glutMouseFunc(rotate);
    
    glutMainLoop();
    return 0;
}

//example: http://graphics.stanford.edu/courses/cs248-00/helpsession/opengl/code_example.html
