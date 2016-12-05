// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>
# include <assert.h> 
# include <math.h>

# include "image.h"
# include "load_image.h"
# include "decoupage.h"
# include "matrice.h"
# include "reseau.h"
# include "apprentissage.h"
# include "read.h"
# include "chargement.h"

//1.5 -> 55543
int main(void)
{

/*	void init_sdl();
	SDL_Surface *img = load_image("./Lorem.bmp");
	struct image *mat = convert_image(img);
	printf("Il y a %i caractere\n",search_text(mat));
//	edge_letter(mat, img);
	display_image(img);
//	printf("Il y a %i caractere\n",search_text(mat));
		get_matrice(resize(mat, get_letter(mat)));
*/
	struct reseau *r = loading_file();
	launch_apprentissage(r, 1.5, 3300);
/*	free_reseau(r);
	
	float *x = calloc(2,sizeof(float));
	float *x1 = calloc(2,sizeof(float));
	float *x2 = calloc(2,sizeof(float));
	float *x3 = calloc(2,sizeof(float));
	*x1 = 1;
	*(x2+1)=1;
	*x3=1;
	*(x3+1)=1;
	struct teach t1;
	struct teach t2;
	struct teach t3;
	struct teach t4;
	t1.data = x;
	t1.result = 0;
	t2.data = x1;
	t2.result = 1;
	t3.data = x2;
	t3.result = 1;
	t4.data = x3;
	t4.result = 0;
	struct teach *entre = malloc(4 * sizeof(struct teach));
	*entre = t1;
	*(entre + 1) = t2;
	*(entre + 2) = t3;
	*(entre + 3) = t4;
	launch_apprentissage(r,entre,4,eta,0.001);*/
}
