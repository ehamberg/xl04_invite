/* $Id: Texture.cpp,v 1.8 2003/12/21 02:12:20 jantho Exp $ */

#include <GL/gl.h>
#include "Texture.h"
#include "PNGImage.h"

// Load the image and create a texture
Texture::Texture(const char *filename)
{
	// load image
	PNGImage *pngTexture = new PNGImage(filename);

	// get an unused texture id
	glGenTextures(1, &texid);

	glBindTexture(GL_TEXTURE_2D, texid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, pngTexture->getType(),
							 pngTexture->getWidth (), pngTexture->getHeight(), 0, pngTexture->getType(),
							 GL_UNSIGNED_BYTE, pngTexture->getData());

	// We don't need the pngTexture anymore
	delete pngTexture;
}

Texture::~Texture()
{
	// Return the texture id to opengl
	glDeleteTextures(1, &this->texid);
}

// Make this texture the current texture
void Texture::bind ()
{
	glBindTexture(GL_TEXTURE_2D, this->texid);
}
