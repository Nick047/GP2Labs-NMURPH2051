//Header Files
#include <iostream>
#include <SDL.h>		//The header for SDL2 functionality

//Global varibles
//pointers to our SDL Windows
SDL_Window*window;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

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

void CleanUp()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}


//Main Method - Entry Point
int main(int argc, char* args[])
{
	if ((SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;

		return -1;
	}
	CleanUp();
	return 0;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);
}