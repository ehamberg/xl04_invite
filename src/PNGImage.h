/* $Id: PNGImage.h,v 1.4 2003/07/23 18:27:36 jantho Exp $ */

#ifndef PNGIMAGE_H_INCLUDED
#define PNGIMAGE_H_INCLUDED

// Load a png image
class PNGImage
{
	public:
		PNGImage (const char *filename);
		~PNGImage ();

		unsigned int getWidth(void) { return (this->width); }
		unsigned int getHeight(void) { return (this->height); }
		unsigned short getBpp(void) { return (this->bpp); }
		int getType(void) { return (this->type); }
		unsigned char *getData (void) { return (this->data); }

	private:
		unsigned int width, height;
		unsigned short bpp;
		int type;

		unsigned char *data;
};

#endif
