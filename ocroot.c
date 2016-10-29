// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>
# include <assert.h> 

# include "image.h"
# include "load_image.h"
# include "decoupage.h"
# include "reseau.h"

//int main(int argc, char **argv)
int main(void)
{
/*	assert(argc==2);
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
*/
	int size[3] = {4,3,1};
	float *data=calloc(4,sizeof(float));
	*data=1.0;
	*(data+1)=1.0;
	*(data+2)=1.0;
	*(data+3)=1.0;
	Reseau *r = construct(size,3);
	data = feed_forward(r,data);
	printf("%f\n",*(data));	
	return 0;
}
