// image.h list functions about matrice treatement

# ifndef _OCROOT_IMAGE_H_
# define _OCROOT_IMAGE_H_

# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "queue.h"

struct letter
{
  int i_min,i_max,j_min,j_max;
};

struct image
{
	int w,h;
	unsigned char *dat;
  struct queue *queue;
};

//Initialize an empty matrice
struct image* new_matrix(int w, int h);

void new_letter(struct image *img, int i_min, int i_max, int j_min, int j_max);

//Set a pixel
void set_pixel(struct image* img, int i, int j, unsigned char px);

//Get a pixel
unsigned char get_pixel(struct image* img, int i, int j);

//Free an image
void del_image(struct image* img);

# endif /* _OCROOT_IMAGE_H_ */
