/* $Id: PNGImage.cpp,v 1.11 2003/12/20 23:15:29 jantho Exp $ */

#include <iostream>
#include <string>
#include <GL/gl.h>
#include <png.h>
#include <stdlib.h>
#include <assert.h>
#include "PNGImage.h"

using std::cerr;
using std::endl;

// load a png file into memory
PNGImage::PNGImage (const char *filename)
{
	double screenGamma, image_gamma;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_uint_32 width, height;
	int bit_depth, color_type;
	png_bytep *volatile row_pointers = NULL;
	FILE *fp;

	screenGamma = 1.0;

	// open file for reading and check for errors
	if ((fp = fopen(filename, "rb")) == NULL) {
		cerr << "PNG: Failed to open " << filename << " for reading\n";
	}

	assert(fp);

	// create the png loading context structure
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (void*)NULL, NULL,
			NULL);

	if (png_ptr == NULL) {
		// Error, clean up
		if (fp)
			fclose(fp);
		cerr << "PNG: png_create_read_struct() failed\n";
	}

	// allocate/initialize the memory for image information
	info_ptr = png_create_info_struct(png_ptr);

	if (info_ptr == NULL) {
		// Error, clean up
		if (fp)
			fclose(fp);
		if (png_ptr)
			png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		cerr << "PNG: png_create_info_struct() failed\n";
	}

	// use libpngs default error handling
	if (setjmp(png_ptr->jmpbuf))
		cerr << "PNG: setjmp() failed\n";

	png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);

	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
			NULL, NULL, NULL);

	if (color_type == PNG_COLOR_TYPE_PALETTE||bit_depth<8)
		png_set_expand(png_ptr);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_expand(png_ptr);

	if (png_get_gAMA(png_ptr, info_ptr, &image_gamma))
		png_set_gamma(png_ptr, screenGamma, image_gamma);
	else
		png_set_gamma(png_ptr, screenGamma, 1.0);

	png_read_update_info(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	row_pointers = (png_bytep *)calloc(height, sizeof(png_bytep));

	switch(color_type) {
		case PNG_COLOR_TYPE_GRAY:
			this->type = GL_LUMINANCE;
			break;
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			this->type = GL_LUMINANCE_ALPHA;
			break;
		case PNG_COLOR_TYPE_PALETTE:
		case PNG_COLOR_TYPE_RGB:
			this->type = GL_RGB;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			this->type = GL_RGBA;
			break;
	}

	this->height = height;
	this->width = width;
	this->data = (png_byte*)calloc(height, png_get_rowbytes(png_ptr, info_ptr));

	for(png_uint_32 row = 0; row < height; row++)
		row_pointers[row] = this->data+row*png_get_rowbytes(png_ptr, info_ptr);

	png_read_image(png_ptr, row_pointers);
	png_read_end(png_ptr, info_ptr);
	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

	if (row_pointers){
		if (row_pointers)
			free(row_pointers);
	}

	fclose(fp);
}

// free memory occupied by the png image
PNGImage::~PNGImage()
{
	if (this->data)
		free(this->data);
}
