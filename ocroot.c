// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>
# include <assert.h> 

# include "image.h"
# include "load_image.h"
# include "decoupage.h"
# include "reseau.h"
# include "apprentissage.h"
# include "read.h"

//int main(int argc, char **argv)
int main(void)
{
/*  init_sdl();
	SDL_Surface *txt = load_image("lorem.bmp");
	struct image *img = convert_image(txt);
	search_text(img);
//  edge_letter(img,txt);
//	display_image(txt);
  unsigned char *mat = get_matrice(img, get_letter(img));
  for (int i = 0; i < TAILLE_I; ++i)
  {
    for (int j = 0; j < TAILLE_J; ++j)
    {
      printf(" %u", (unsigned) *(mat + i * TAILLE_J + j));   
    }
    printf("\n");
  }
  free(mat);
  del_image(img);
  SDL_FreeSurface(txt);
  SDL_Quit();*/
  float dat[10] = {1,0,1};
  float *deb = dat;
  struct teach t;
  t.data = deb;
  t.result = 0.2;
  int size[3] = {3,5,1};
  struct reseau *r = construct(size,3);
  sgd(r,&t,1,1,1,0.5,NULL,0);
//  printf("res : %d\n",feed_forward(r,deb));
  free_reseau(r);

}
