

#include "Texture.h"

GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID = 0;	//Initialises the texture ID

	SDL_Surface * imageSurface = IMG_Load(filename.c_str());

	if (!imageSurface)
	{
		std::cout << "Can' Load image" << filename << " " << IMG_GetError();
		return textureID;

	}

	GLint nOfColors = imageSurface->format->BytesPerPixel;
	GLenum textureFormat = GL_RGB;
	if (nOfColors == 4) // This is 4 to inlucde the alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGBA;
		else
			textureFormat = GL_BGRA;
	}
	else if (nOfColors == 3)	//No alpha channel
	{
		if (imageSurface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGB;
		else
			textureFormat = GL_BGR;
	}
	else
	{
		std::cout << "Warning: The image is not trueclor... this will probably break";
		//^This error should not go unhandled
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, imageSurface->w, imageSurface->h, 0, textureFormat, GL_UNSIGNED_BYTE, imageSurface->pixels);

	//The code below might be in the worng location
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return textureID;	
}