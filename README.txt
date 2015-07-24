Assignment A4:

An introduction to the OpenGL API learning the basics of rendiner in OpenGl including: rasterizing basic primitives, loading and rendering of 3d geometry using simple wireframes, texture mapping, calculating and using normals for lighting effects

Here are the instructions for the user input I implemented:

	Keys:
	i, o --> zoom In and Out, respectively

	r --> rotate the image

	w,a,z,s --> these keys form a north, west, south, east directional pad

	Click: click anywhere on the screen to orbit arond the object

Any issue I had in implementing this input was that all of the changes are in relation to the origin of the image, so when a change is applied, the origin changes and therefore the response of the input changes as well. I couldn't figure out how to change this, but was able to do everything I needed with the images by playing around with the different transformations.

I worked with classmate Xinyu Liang on the texture mapping section (mostly got help from this in office hours) and on the flat shading section.

I included a Makefile which should compile all of my programs. I had trouble getting it to work at times, receiving the error
"Undefined symbols for architecture x86_64:"
	I also ran into this problem when working on the project XCode, and it took me a while to fix it by changing settings but I'm not sure how to fix this when working with a Makefile. However, the Makefile does show each program and the files it depends on. Sorry I couldn't get it working!


Resources Used:
zoom resource: https://www.opengl.org/archives/resources/faq/technical/viewing.htm

orbit resource: https://www.opengl.org/discussion_boards/showthread.php/173157-Glut-Mouse-Func

load resource: /adapted from: https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ

full program resource: //example: http://graphics.stanford.edu/courses/cs248-00/helpsession/opengl/code_example.html
//texture mapping reference: http://www.nullterminator.net/gltexture.html