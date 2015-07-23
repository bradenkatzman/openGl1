# Assign the name of our compiler to a variable, which can later be accessed by 
# wrapping its name in $()                                                       
CC = g++

# -Wall turn on most warnings, the next flag prevents the compiler from          
# complaining about the deprecated functions you'll be using.                    
# finally, the two framework flags tell our compiler to link                     
# against GLUT and OpenGL. Without these flags, our finished program             
# wouldn't know where to look for the gl and glu functions.                      
# On OS X, include GL by "#include <OpenGL/gl.h>", and GLUT                      
# by "#include <GLUT/glut.h>"                                                    
CFLAGS = -Wall -Wno-deprecated-declarations -framework GLUT -framework OpenGL

# Causes "make all" to compile both main1 and main2.                             
all: main main1 main2 

# Compiles main1.cpp into the program main1, while linking with GL and GLUT      
# Run with "make main1"                                                          
# The main1.cpp after the colon is a declaration that the command line that      
# follows depends on main1.cpp.  
main: main.cpp SimpleImage.h SimpleImage.cpp
	$(CC) $(CFLAGS) main.cpp SimpleImage.cpp -o main

main1: main1.cpp
	$(CC) $(CFLAGS) main1.cpp -o main1
# Identical to the above, except with main2 instead of main1                     
main2: main2.cpp
	$(CC) $(CFLAGS) main2.cpp -o main2
# deletes main1 and main2 when "make clean" is called                            
clean:
	rm main1 main2