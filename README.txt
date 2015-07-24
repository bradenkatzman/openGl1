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

Resources Used:
zoom resource: https://www.opengl.org/archives/resources/faq/technical/viewing.htm

orbit resource: https://www.opengl.org/discussion_boards/showthread.php/173157-Glut-Mouse-Func