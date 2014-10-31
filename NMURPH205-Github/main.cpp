//Add a header files to the project called Vertex.h
//Add a header file to the project called Shader.h
//Add a Source file to the project called Shader.cpp
//Add the shader/assets folder to the solution directory
//Add a text file to the project called simpleVS.glsl		//make sure the locations point to the shade folder
//Add a text file to the project called simpleFS.glsl

//Add an additional include directory for C:\Specialised Applications\glm

//Maths headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/* ^genertates about 60 errors
^These headers are to be used ith the above directory */
#include "Vertex.h"	//Calls the created header file
#include "Shader.h" //Calls the created header file


//Header Files
#include <iostream>
#include <GL/glew.h>		//The header for GLEW functionality

#include <SDL.h>		//The header for SDL2 functionality

#include <SDL_opengl.h>		//The header for the OpenGL headers
#include <gl\GLU.h>
#include <SDL_image.h>	//LINKS THE sdl_iMAGE HEADER


#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "./assets";
#else
const std::string ASSETS_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";

//Global varibles
//pointers to our SDL Windows
SDL_Window*window;

//SDL Gl Context
SDL_GLContext glcontext = NULL;

GLuint triangleEBO;
GLuint triangleVBO;
GLuint VAO;
GLuint shaderProgram = 0;

//Matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool running = true;
//float triangleData[] = { 0.0f, 1.0f, 0.0f, /*Top*/ -1.0f, -1.0f, 0.0f, /*Bottom Left*/ 1.0f, -1.0f, 0.0f}; /* Bottom Right*/	//Changed to the array below in Lab 2 -3D 4.2
//Vertex triangleData[] = {{0.0f, 1.0f, 0.0f, /*x,y,z*/ 1.0f, 0.0f, 1.0f}, /*r,g,b,a*/ {-1.0f, -1.0f, 0.0f, /*x,y,z*/ 0.0f, 1.0f, 0.0f, 1.0f}, /*r,g,b,a*/ {1.0f, -1.0f, 0.0f, /*x,y,z*/ 0.0f, 0.0f, 1.0f, 1.0f}}; /*r,g,b,a*/	//Creates a single triangle woth colored vertices
//^Changed to the array below in Lab 2 -3D 6.1 this format of code seems a lot more readable
//Changed the array below to contain triangle indices to be able to store the corners of a cube
Vertex triangleData[] = {
	//Front Cube Face
	{ vec3(-0.5f, 0.5f, 0.5f), vec4(1.0f, 0.0f, 1.0f, 1.0f) },// Top Left 	coord - x, y, z, color - r, g, b, a
	{ vec3(-0.5f, -0.5f, 0.5f), vec4(1.0f, 1.0f, 0.0f, 1.0f) },// Bottom Left 	coord - x, y, z, color - r, g, b, a
	{ vec3(0.5f, -0.5f, 0.5f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right 	coord - x, y, z, color - r, g, b, a
	{ vec3(0.5f, 0.5f, 0.5f), vec4(1.0f, 0.0f, 1.0f, 1.0f) },// Top Right 	coord - x, y, z, color - r, g, b, a
	//Back Cube Face
	{ vec3(-0.5f, 0.5f, -0.5f), vec4(1.0f, 0.0f, 1.0f, 1.0f) },// Top Left 	coord - x, y, z, color - r, g, b, a
	{ vec3(-0.5f, -0.5f, -0.5f), vec4(1.0f, 1.0f, 0.0f, 1.0f) },// Bottom Left 	coord - x, y, z, color - r, g, b, a
	{ vec3(0.5f, -0.5f, -0.5f), vec4(0.0f, 1.0f, 1.0f, 1.0f) }, //Bottom Right 	coord - x, y, z, color - r, g, b, a
	{ vec3(0.5f, 0.5f, -0.5f), vec4(1.0f, 0.0f, 1.0f, 1.0f) },// Top Right 	coord - x, y, z, color - r, g, b, a
};
GLuint indices[] = {
	// Front
	0, 1, 2, 0, 3, 2,

	// Left
	4, 5, 1, 4, 1, 0,

	// Right
	3, 7, 2, 7, 6, 2,

	// Bottom
	1, 5, 2, 6, 2, 1,

	// Top
	5, 0, 7, 5, 7, 3,

	// Back
	4, 5, 6, 4, 7, 6
};


GLuint shaderProgram = 0;

//Global Functions


void createShader()
{
	GLuint vertexShaderProgram = 0;
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);

	glBindAttribLocation(shaderProgram, 0, "vertexPosition");

	//Now we can delete the VS and FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

void initGeometry()
{
	//Create the buffer	//Changed from VBO to EBO in Lab 2 - 3D 7.4
	glGenBuffers(1, &triangleEBO);
	//Make the new EBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleEBO);
	//Copy the Index Data to EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//change to?//glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(int), indices, GL_STATIC_DRAW);

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
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//The function to initialise OpenGL
void initOpenGL()
{
	//Ask for version 3.2 of OpenGL to be used
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

	glewExperimental = GL_TRUE;
	//Initialise glew

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{

		/* Problem: glewInit failed, something is seriously wrong */
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

	glUseProgram(shaderProgram);	//This line and the three below might have to go below the EBO linkBuffer
	//Gets the location of the MVP, Creates a combined Model View Projection Matrix and then sends it to the shader
	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	mat4 MVP = projMatrix * viewMatrix * worldMatrix;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

	//Tells the Shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void**)sizeof(vec3));
	
	

	//Changed in Lab 2 - 3D to allow to draw both EBOs and VBOs
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//required to swap the back and front buffer
	SDL_GL_SwapWindow(window);
}

//Function to update the game state
void update()
{
	projMatrix = glm::perspective(45.0f, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
}


//Main Method - Entry Point
int main(int argc, char* args[])
{
	if ((SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;

		return -1;
	}

	//The code below initialises SDL Image for jpg and pngs
	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)& (imageInitFlags)) != imageInitFlags)
	{
		std::cout << "ERROR SDL_Image Init" << IMG_GetError() << std::endl;
		//Handles and gets Error
	}

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	//Call our InitOpenGL Function
	initOpenGL();
	//Call out InitGeometry Function
	initGeometry();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	createShader();

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




