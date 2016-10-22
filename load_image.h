/* load_image.h list function use to load images */


# ifndef _OCROOT_LOAD_IMAGE_H_
# define _OCROOT_LOAD_IMAGE_H_

# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "image.h"

//Initialize SDL
void init_sdl(void);
//Function who load an image
SDL_Surface* load_image(char *path);
//Get a pixel
Uint32 getpixel(SDL_Surface *surface, unsigned x,  unsigned y);
//Set a pixel
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
//Function who return a black and white matrice
Image* convert_image(SDL_Surface* img);
//Wait for keydown event
void wait_for_keypressed(void);
//Display an image
SDL_Surface* display_image(SDL_Surface *img);
//Draw edge of text
void contour_text(Image *img, SDL_Surface *surf);

# endif /* _OCROOT_LOAD_IMAGE_H_ */
