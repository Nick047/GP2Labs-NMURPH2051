#ifndef TEXTURE_H
#define TEXTURE_H

<<<<<<< HEAD
#include <GL/glew.h>

=======
>>>>>>> parent of 3765452... Bumo-Mapping and PostProcessing
/*
#ifdef __APPLE__		//Used for mac compatability
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif
*/
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_TTF.h>
//	#endif


#include <iostream>
#include <string.h>

GLuint convertSDLsurfaceToGLTexture(SDL_Surface * surface);

GLuint loadTextureFromFile(const std::string& filename);	//Takes in a string filename and returns a GLuint ID of a OpenGLTexture
//This shouldn't be used for realtime use, build on startup
GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text);



#endif