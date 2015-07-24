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
#include <string.h>
#include <GLUT/glut.h>
#include "SimpleImage.h"

using namespace std;

struct Vertex {
    float x, y, z;
    
    Vertex(float x_, float y_, float z_) {
        x = x_;
        y = y_;
        z = z_;
    }
    
    void operator=(const Vertex& v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
};

struct textureCoordinate {
    float x, y;
    
    textureCoordinate(float x_, float y_) {
        x = x_;
        y = y_;
    }
};

struct face {
    int v1, v2, v3, tc1, tc2, tc3, vn1, vn2, vn3;
    
    //just vertices face
    face(int v1_, int v2_, int v3_) {
        v1 = v1_;
        v2 = v2_;
        v3 = v3_;
    }
    
    //vertices, texture coordinates, and vertex normal face
    face(int v1_, int v2_, int v3_, int tc1_, int tc2_, int tc3_,
         int vn1_,int vn2_, int vn3_) {
        v1 = v1_;
        v2 = v2_;
        v3 = v3_;
        
        tc1 = tc1_;
        tc2 = tc2_;
        tc3 = tc3_;
        
        vn1 = vn1_;
        vn2 = vn2_;
        vn3 = vn3_;
    }
};

//create static data vectors
static vector<Vertex> vertexData; //vertices
static vector<textureCoordinate> textureData; //texture coordindates
static vector<face> faceData; //faces

//texture variables
static GLuint textureID;

//create static orbit variables
static int oldX, oldY;
static float theta =0.0f, phi=0.0f;

Vertex& findNormal(int v1, int v2, int v3) {
    //v2-v1 x v3-v1
    float a,b,c;
    
    //first expression
    a = vertexData[v2].x - vertexData[v1].x;
    b = vertexData[v2].y - vertexData[v1].y;
    c = vertexData[v2].z - vertexData[v1].z;
    Vertex e1(a, b, c);
    
    //second expression
    float d,e,f;
    d = vertexData[v3].x - vertexData[v1].x;
    e = vertexData[v3].y - vertexData[v1].y;
    f = vertexData[v3].z - vertexData[v1].z;
    Vertex e2(d, e, f);
    
    //calculate cross product
    float x, y, z;
    x = e1.y*e2.z - e1.z*e2.y;
    y = e1.z*e2.x - e1.x*e2.z;
    z = e1.x*e2.y - e1.y*e2.x;
    
    float length = sqrtf(x*x + y*y + z*z);
    Vertex result(x/length, y/length, z/length);
    
    return result;
    
}

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
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    //discards inivisible polygons during rendering
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    //set light source
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    
    //light position looks down z axis at z=-0.5
    GLfloat light_ambient[] = { 0.0, 0.0, -.5, 1.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    
    //set material property
    GLfloat cyan[] = {0.862745f, 0.0784314f, 0.235294f, 1.f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, cyan);
    
    //set front faces to counterclockwise orientation i.e. front facing
    glFrontFace(GL_CCW);
    
    
    //points must have z coordinates within the interval [-1 - -5] to be visible
    glBegin(GL_TRIANGLES);
    
    //render faces
    for (int i = 0; i < faceData.size(); ++i) {
        
        face face = faceData[i];
        
        //vertices
        int v1 = face.v1-1;
        float x1, y1, z1;
        x1 = vertexData[v1].x;
        y1 = vertexData[v1].y;
        z1 = vertexData[v1].z;
        
        int v2 = face.v2-1;
        float x2, y2, z2;
        x2 = vertexData[v2].x;
        y2 = vertexData[v2].y;
        z2 = vertexData[v2].z;
        
        int v3 = face.v3-1;
        float x3, y3, z3;
        x3 = vertexData[v3].x;
        y3 = vertexData[v3].y;
        z3 = vertexData[v3].z;
        
        //compute normal
        Vertex n = findNormal(v1, v2, v3);
        glNormal3f(n.x, n.y, n.z);
        
        
        //render first vertex
        //plot vertex
        glVertex3f(x1, y1, z1-2.0);
        
        //render second vertex
        
        //plot vertex
        glVertex3f(x2, y2, z2-2.0);
        
        //render third vertex
        
        //plot vertex
        glVertex3f(x3, y3, z3-2.0);
    }
    glEnd();
    
    glFlush(); //forces execution, clears buffer
    glDisable(GL_TEXTURE_2D);
}

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
            float a, b;
            
            is >> a;
            is >> b;
            
            textureCoordinate tC(a,b);
            
            textureData.push_back(tC);
        }
        //else if this is a face information line
        else if (line.substr(0, 2) == "f ") {
            istringstream is(line.substr(2));
            
            //parse face info and push on faceData vector
            int v1, v2, v3, tc1, tc2, tc3, vn1, vn2, vn3;
            char c1, d1, c2, d2, c3, d3;
            
            is >> v1;
            
            //check if next character is /
            if (is.peek() == '/') {
                //FIRST VERTEX INFO
                //discard /
                is >> c1;
                
                //store texture coordinate
                is >> tc1;
                
                //discard /
                is >> d1;
                
                //store vertex normal
                is >> vn1;
                
                //SECOND VERTEX INFO
                //store second vertex
                is >> v2;
                
                //discard /
                is >> c2;
                
                //store texture coordinate
                is >> tc2;
                
                //discard /
                is >> d2;
                
                //store vertex normal
                is >> vn2;
                
                //THIRD VERTEX INFO
                //store third vertex
                is >> v3;
                
                //discard /
                is >> c3;
                
                //store texture coordinate
                is >> tc3;
                
                //discard /
                is >> d3;
                
                //store vertex normal
                is >> vn3;
                
                face face(v1, v2, v3, tc1, tc2, tc3, vn1, vn2, vn3);
                faceData.push_back(face);
                
            }
            else {
                is >> v2;
                is >> v3;
                face face(v1, v2, v3);
                faceData.push_back(face);
            }
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
    const char* title = argv[1];
    glutCreateWindow(title);
    
    
    
    //initialize state
    initOpenGL();
    
    //load geometry from obj files
    load(argv[1]);
    
    //display
    glutDisplayFunc(display);
    
    //callbacks
    glutKeyboardFunc(key);
    glutMouseFunc(orbit);
    
    glutMainLoop();
    return 0;
}