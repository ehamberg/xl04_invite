/* $Id: Texture.h,v 1.4 2003/07/23 18:27:36 jantho Exp $ */

#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

/* Class to load and use one texture */
class Texture
{
	public:
		Texture (const char *filename);
		~Texture ();

		// Make this texture the current texture
		void bind ();

	private:
		unsigned int texid;
};

#endif
