#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>
#include <SDL_TTF.h>
//^ Should this be <SDL_ttf.h> instead

GLuint loadTextureFromFile(const std::string& filename);	//Takes in a string filename and returns a GLuint ID of a OpenGLTexture

GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text);

GLuint convertSDLsurfaceToGLTexture(SDL_Surface * surface);

#endif