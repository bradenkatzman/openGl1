//
//  main.cpp
//  a4
//
//  Created by Braden Katzman on 7/18/15.
//  Copyright (c) 2015 Braden Katzman. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <GLUT/glut.h>

using namespace std;


void initOpenGL() {
    //these commands ensure that drawing commands affect the projection matrix, rather than the model view matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //sets the near plane at 1 and a far plane at 5
    //parameters (left, right, bottom, top, near, far)
    glFrustum(-2.0,2.0,-2.0,2.0,1.0,50.0);
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
            //i is zoom in
            case 'i':
                glTranslated(0.0, 0.0, 0.1);
                glutPostRedisplay();
            break;
            
            //o is zoom out
            case 'o':
                glTranslated(0.0, 0.0, -.1);
                glutPostRedisplay();
                break;
            
            //W, A, Z, S make arrow pad
            case 'w':
                glTranslated(0.0, 1.0, 0.0);
                glutPostRedisplay();
                break;
            
            case 'a':
                glTranslated(-1.0, 0.0, 0.0);
                glutPostRedisplay();
                break;
            
            case 'z':
                glTranslated(0.0, -1.0, 0.0);
                glutPostRedisplay();
                break;
        
            case 's':
                glTranslated(1.0, 0.0, 0.0);
                glutPostRedisplay();
                break;
    }
}

//adapted from: https://www.opengl.org/discussion_boards/showthread.php/173157-Glut-Mouse-Func
void rotate(int button, int state, int x, int y){
    //right quadrant
    if (x < glutGet(GLUT_WINDOW_WIDTH)/2) {
        glRotated(5.0, 0.0, 0.0, 10.0);
    }
    
    //left quadrant
    if (x > glutGet(GLUT_WINDOW_WIDTH)/2){
        glRotated(-5.0, 0.0, 0.0, 10.0);
    }
    glutPostRedisplay();
}


//adapted from: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
void load(const char* fileName, vector<float>& vertexData, vector<float>& textureData,
          vector<float>& faceData) {
    ifstream input;
    input.open(fileName);
    
    if(!input) {
        cout << fileName << " cannot be opened" << endl;
        exit(0);
    }
    
    string line;
    while(getline(input, line)) {
        //if this is a vertex line
        if (line.substr(0, 2) == "v ") {
            //WRITE WHAT THIS DOES
            istringstream is(line.substr(2));
            
            //parse 3 vertices, push onto vertexData vector
            float a, b, c;
            
            is >> a;
            is >> b;
            is >> c;
            
            //instead of adding 4th w vertex, set conditions to include w = 1.0f after every 3 vertices
            vertexData.push_back(a);
            vertexData.push_back(b);
            vertexData.push_back(c);
        }
        //else if this is a texture coordinate line
        else if(line.substr(0,3) == "vt ") {
            istringstream is(line.substr(3));
            
            //parse coordinates and push on textureData vector
            float a, b, c;
            
            //**********would need to check if there is third number before copying to c********
            is >> a;
            is >> b;
            is >> c;
            
            textureData.push_back(a);
            textureData.push_back(b);
            textureData.push_back(c);
            
            cout << c << endl;
        }
        //else if this is a face information line
        else if (line.substr(0, 2) == "f ") {
            istringstream is(line.substr(2));
            
            //parse face info and push on faceData vector
            int a, b, c;
            
            is >> a;
            is >> b;
            is >> c;
            
            faceData.push_back(a);
            faceData.push_back(b);
            faceData.push_back(c);
        }
        //ignore all other lines including comments and vertex normal data
        else { }
    }
    
    cout << vertexData.size() << endl;
    cout << textureData.size() << endl;
    cout << faceData.size();
}

int main(int argc, char **argv) {
    
    //window initialization
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Stanford Logo with OpenGL");
    
    //create data vectors and load geometry from obj files
    vector<float> vertexData; //vertices
    vector<float> textureData; //texture coordindates
    vector<float> faceData; //faces
    load(argv[1], vertexData, textureData, faceData);
    
    //initialize state
    initOpenGL();
    glutDisplayFunc(display);
    
    //callbacks
    glutKeyboardFunc(key);
    glutMouseFunc(rotate);
    
    glutMainLoop();
    return 0;
}

//example: http://graphics.stanford.edu/courses/cs248-00/helpsession/opengl/code_example.html
