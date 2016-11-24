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
/*init_sdl();
	SDL_Surface *txt = load_image("lorem.bmp");
	struct image *img = convert_image(txt);
	search_text(img);
  edge_letter(img,txt);
	display_image(txt);
  del_image(img);
  SDL_FreeSurface(txt);
  SDL_Quit();*/
  float *data = malloc(10*sizeof(float));
  for(float i = 0; i < 10; ++i)
    *(data + (int)i) =((float) i)/10.0;
  struct teach t;
  t.data = data;
  t.result = 0.2;
  int size[3] = {10,5,1};
  struct reseau *r = construct(size,3);
  sgd(r,&t,1,1,1,0.5,NULL,0);
  free(data);
  free_reseau(r);
}
