//Header Files
#include <iostream>
#include <SDL.h>		//The header for SDL2 functionality

#include <SDL_opengl.h>		//The header for the OpenGL headers
#include <gl\GLU.h>

//Global varibles
//pointers to our SDL Windows
SDL_Window*window;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool running = true;


//Global Functions
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
	}	
	
	CleanUp();
	return 0;
}