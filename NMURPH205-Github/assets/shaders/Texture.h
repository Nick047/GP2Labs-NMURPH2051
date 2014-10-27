#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <iostream>
#include <string.h>

GLuint loadTextureFromFile(const std::string& filename);	//Takes in a string filename and returns a GLuint ID of a OpenGLTexture


#endif