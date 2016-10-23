// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>
# include <assert.h> 

# include "image.h"
# include "load_image.h"
# include "decoupage.h"

int main(int argc, char **argv)
{
	assert(argc==2);
	init_sdl();
	SDL_Surface *txt = load_image(argv[1]);
	Image *img = convert_image(txt);
	search_text(img);
	search_row(img);
	search_letter(img);
	display_image(txt);
	edge_text(img,txt);
	display_image(txt);
	edge_row(img,txt);
	display_image(txt);
	edge_letter(img,txt);
	display_image(txt);
	return 0;
};
