/* load_image.h list function use to load images */

# ifndef _OCR_LOAD_IMAGE_H_
# define _OCR_LOAD_IMAGE_H_

# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "image.h"

//Initialize SDL
void init_sdl(void);
//Function who load an image
SDL_Surface* load_image(char *path);
//Getteur for an image's pixel
Uint32 getpixel(SDL_Surface *surface, unsigned x,  unsigned y);
//Function who return a black and white matrice
Image* convert_image(char *path);

# endif /* _OCR_LOAD_IMAGE_H_ */
