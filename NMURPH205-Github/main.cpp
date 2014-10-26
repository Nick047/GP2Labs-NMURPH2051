//Header Files
#include <iostream>
#include <GL/glew.h> //The header for GLEW functionality
#include <SDL.h> //The header for SDL2 functionality
#include <SDL_opengl.h> //The header for the OpenGL headers
#include <gl\GLU.h>
//#include "Vertex.h"	//Links the local creted Vertex header	//including this seems to create errors around SDL_Window

//Global varibles




//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
bool running = true;
GLuint triangleVBO;
float triangleData[] = { 0.0f, 1.0f, 0.0f, /*Top*/ -1.0f, -1.0f, 0.0f, /*Bottom Left*/ 1.0f, -1.0f, 0.0f }; /* Bottom Right*/
//Global Functions

//pointers to our SDL Windows
SDL_Window*window = NULL;
//SDL Gl Context
SDL_GLContext glcontext = NULL;

void initGeometry()
{
	//Create the buffer
	glGenBuffers(1, &triangleVBO);
	//Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//Copy the Vetrex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);
}


void InitWindow(int width, int height, bool fullscreen)
{
	//Creates a window
	window = SDL_CreateWindow(
		"Lab 1",	//Window Title
		SDL_WINDOWPOS_CENTERED, //x position, centered
		SDL_WINDOWPOS_CENTERED, //y position, centered
		width,	//Width, in pixels
		height,	//Height, in pixels
		SDL_WINDOW_OPENGL//flags
		);
}

SDL_Event event;

void CleanUp()
{
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//The function to initialise OpenGL

void initOpenGL()
{
	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);
	//If this is NULL then there is an error in creating the context
	if (!glcontext)
	{
		std::cout << "Error Creating OpenGL Context" << SDL_GetError() <<
			std::endl;
	}
	//Smooth Shading
	glShadeModel(GL_SMOOTH);

	//Clear the Background to Black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//Enable Depth TEsting
	glEnable(GL_DEPTH_TEST);

	//The depth test to use
	glDepthFunc(GL_LEQUAL);

	//Turn on the best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Initialise glew
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wronh */
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
}

//The Function to set and reset the viewport

void setViewport(int width, int height)
{
	//Screen Ratio
	GLfloat ratio;
	//Make sure the height is always above 0
	if (height == 0)
	{
		height = 1;
	}
	//Calculates the screen's ratio
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//Change to project matrix mode
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	//Calculate perspective matrix, using glu library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);

	//Reset using the Identity Matrix / mutiple matrix by 1
	glLoadIdentity();
}

//Function to draw

void render()
{
	//Set the clear color(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Make the new VBO active. Repeat here as a sanity check( may have changed since initialisation)
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	//Establish it's 3 coordinates per vertex with zero stride(space between elements) in an array and contains floating point numbers
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//Establish array contains vertices (not normals, colors, texture coordinates etc)
	glEnableClientState(GL_VERTEX_ARRAY);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);

	//Reset using the Identity Matrix
	glLoadIdentity();

	//Translate to -5.0f on z-axis
	glTranslated(0.0f, 0.0f, -5.0f);

	//Begin drawing Triangles
	glBegin(GL_TRIANGLES);
	//
	glColor3f(1.0f, 0.0f, 0.0f);	//This colours the vertices
	glVertex3f(0.0f, 1.0f, 0.0f);	//The Top Vertice
	glVertex3f(-1.0f, -1.0f, 0.0f);	//Bottom Left
	glVertex3f(1.0f, -1.0f, 0.0f);	//Bottom Right
	glEnd();
	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
	//Reset using the Identity Matrix
	glLoadIdentity();
	//Translate
	glTranslatef(0.0f, 0.0f, -6.0f);
	//Actually draws the triangle, giving the number of vertices provided
	glDrawArrays(GL_TRIANGLES, 0, sizeof(triangleData) / (3 * sizeof(float)));
	//required to swap the back and front buffer
	SDL_GL_SwapWindow(window);
}

//Function to update the game state

void update()
{
}

//Main Method - Entry Point

int main(int argc, char* args[])
{
	if ((SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
		return -1;
	}
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);
	//Call our InitOpenGL Function
	initOpenGL();
	//Call out InitGeometry Function
	initGeometry();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			//Get event Type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set out boolean value, which controls the game loop to false
				running = false;
			}
		}
		update();
		render();
	}
	CleanUp();
	return 0;
}

