#ifndef Shader_h
#define Shader_h

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <string>
#include <fstream>


enum SHADER_TYPE
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

GLuint loadShaderFromFile(const std::string&filename, SHADER_TYPE shaderType);
GLuint loadShaderFromMemory(const char * pMem, SHADER_TYPE shaderType);	//If this function fails then the value returned will be 0



#endif

//Should this go befor #endif?

bool checkForLinkErrors(GLuint program);
bool checkForCompileErrors(GLuint shaderProgram);

