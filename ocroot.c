// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>
# include <assert.h> 

# include "image.h"
# include "load_image.h"
# include "decoupage.h"
# include "reseau.h"
# include "apprentissage.h"

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
	Teach *te1 = malloc(sizeof(Teach));
	Teach *te2 = malloc(sizeof(Teach));
	Teach *te3 = malloc(sizeof(Teach));
	Teach *te4 = malloc(sizeof(Teach));
	float *arr1 = calloc(2,sizeof(float));
	float *arr2 = calloc(2,sizeof(float));
	float *arr3 = calloc(2,sizeof(float));
	float *arr4 = calloc(2,sizeof(float));
	*arr1 = 0;
	*arr2 = 1;
	*arr3 = 0;
	*arr4 = 1;
	*(arr1 + 1) = 0;
	*(arr2 + 1) = 0;
	*(arr3 + 1) = 1;
	*(arr4 + 1) = 1;
	te1->data = arr1;
	te2->data = arr2;
	te3->data = arr3;
	te4->data = arr4;
	te1->result = 0.25;
	te2->result = 0.75;
	te3->result = 0.75;
	te4->result = 0.25;
	
	Teach *tr_dt = malloc(4*sizeof(Teach));
	*tr_dt = *te1;
	*(tr_dt+1) = *te2;
	*(tr_dt+2) = *te3;
	*(tr_dt+3) = *te4;

	int size[3] = {2,1};
	Reseau *r = construct(size,2);
		
	sgd(r,tr_dt,4,10,0.3,tr_dt,4);
	
	return 0;
}
