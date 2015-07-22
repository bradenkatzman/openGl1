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
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <GLUT/glut.h>

using namespace std;

struct Vertex {
    float x, y, z;
    
    Vertex(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
};

//create static data vectors
static vector<Vertex> vertexData; //vertices
static vector<float> textureData; //texture coordindates
static vector<float> faceData; //faces

//create static orbit variables
static int oldX, oldY;
static bool rotateCheck = false;
static float theta =0.0f, phi=0.0f;

void initOpenGL() {
    //these commands ensure that drawing commands affect the projection matrix, rather than the model view matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //sets the near plane at 1 and a far plane at 5
    //parameters (left, right, bottom, top, near, far)
    glFrustum(-1.0,1.0,-1.0,1.0,1.0,50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   
    //sets the camera center at (0, 0, 0), looking down at (0, 0, -1) --> negative z-axis
    gluLookAt(0,0,0,0,0,-1,0,1,0);
}
void display() {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    
    //discards inivisible polygons during rendering
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    //set wire color to red
    glColor3f(1.0, 0.0, 0.0);
    
    //set front faces to counterclockwise orientation i.e. front facing
    glFrontFace(GL_CCW);
    
    //instruct OpenGL to draw only the outline of the polygon
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //points must have z coordinates within the interval [-1 - -5] to be visible
    glBegin(GL_TRIANGLES);
    
        //render faces
        for (int i = 0; i < faceData.size(); ++i) {
            
            int triangleIndex = faceData[i]-1;
            
            float x, y, z;
            
            x = vertexData[triangleIndex].x;
            y = vertexData[triangleIndex].y;
            z = vertexData[triangleIndex].z;
            
            glVertex3f(x, y, z-2.0);
        }
    glEnd();
    
    glFlush(); //forces execution, clears buffer
}

//zoom resource: https://www.opengl.org/archives/resources/faq/technical/viewing.htm
void key(unsigned char key, int x, int y) {
    switch (key) {
            //i is zoom in
            case 'i':
                glTranslated(0.0, 0.0, 0.1);
            break;
            
            //o is zoom out
            case 'o':
                glTranslated(0.0, 0.0, -.1);
                break;
            
            //W, A, Z, S make arrow pad
            case 'w':
                glTranslated(0.0, 1.0, 0.0);
                break;
            
            case 'a':
                glTranslated(-1.0, 0.0, 0.0);
                break;
            
            case 'z':
                glTranslated(0.0, -1.0, 0.0);
                break;
        
            case 's':
                glTranslated(1.0, 0.0, 0.0);
                break;
            
            //r for rotate right
            case 'r':
                glRotated(5.0, 0.0, 0.0, 10.0);
                break;
            
            //l for rotate left
            case 'l':
                glRotated(-5.0, 0.0, 0.0, 10.0);
                break;
    }
     glutPostRedisplay();
}

//adapted from: https://www.opengl.org/discussion_boards/showthread.php/173157-Glut-Mouse-Func
void orbit(int button, int state, int x, int y) {

    theta += (x-oldX)*0.0001f;
    phi   += (y-oldY)*0.0001f;
    
    oldX = x;
    oldY = y;
    
    float eyeX = cos(phi)*sin(theta);
    float eyeY = sin(phi)*sin(theta);
    float eyeZ = -1 + cos(theta);
    
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, -1, 0,1,0);
    
    glutPostRedisplay();
}


//adapted from: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
void load(const char* fileName) {
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
            
            Vertex v(a, b, c);
            
            //instead of adding 4th w vertex, set conditions to include w = 1.0f after every 3 vertices
            vertexData.push_back(v);
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
            
            //if (
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
}

int main(int argc, char **argv) {
    
    //window initialization
    glutInit(&argc, argv);
    glutInitWindowSize(512, 512);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Stanford Logo with OpenGL");
    
    //load geometry from obj files
    load(argv[1]);
    
    //initialize state
    initOpenGL();
    glutDisplayFunc(display);
    
    //callbacks
    glutKeyboardFunc(key);
    glutMouseFunc(orbit);
    
    glutMainLoop();
    return 0;
}

//example: http://graphics.stanford.edu/courses/cs248-00/helpsession/opengl/code_example.html
