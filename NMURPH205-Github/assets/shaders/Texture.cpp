

#include "Texture.h"

GLuint loadTextureFromFile(const std::string& filename)
{
	GLuint textureID = 0;	//Initialises the texture ID

	GLuint loadTextureFromFont(const std::string& fontFilename, int pointSize, const std::string& text)
	{
		GLuint textureID = 0;

		TTF_Font * font = TTF_OpenFont(fontFilename.c_str(), pointSize);
		if (!font)
		{
			std::cout << "Unable to load font " << fontFilename << " " << TTF_GetError();
			return textureID;
		}

		SDL_Surface * textSurface = TTF_RenderText_Blended(font, text.c_str(), { 255, 255, 255 });
		
		return textureID;
	}

	GLuint convertSDLsurfaceToGLTexture(SDL_Surface * surface)
	{
		GLuint textureID = 0;
		return 0;

	}

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