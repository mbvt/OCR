# include "image.h"

struct image* new_matrix(int w, int h) 
{
	struct image* img = malloc(sizeof(struct image));
	assert(img);
	img->w = w;
	img->h = h;
	img->dat = calloc(w*h,sizeof(unsigned char*));
	assert(img->dat);
	img->queue = malloc(sizeof(struct queue));
  queue_init(img->queue);
	return img;
}

void new_letter(struct image *img, int i_min, int i_max, int j_min, int j_max)
{
  struct letter *l = malloc(sizeof(struct letter));
  l->i_min = i_min;
  l->i_max = i_max;
  l->j_min = j_min;
  l->j_max = j_max;
  queue_push(img->queue,l);
}

struct letter* get_letter(struct image *img)
{
  return (struct letter*) queue_pop(img->queue);
}

void set_pixel(struct image* img, int i, int j, unsigned char px)
{
	assert(img && i>=0 && i<img->h && j>=0 && j<img->w);
	*(img->dat+img->w*j+i) = px;
}

unsigned char get_pixel(struct image *img, int i , int j)
{	
	assert(img && i>=0 && i<img->h && j>=0 && j<img->w);
	return *(img->dat+img->w*j+i);
}

void del_image(struct image* img)
{
	if(img)
	{
		while(!queue_is_empty(img->queue))
    {
      free(queue_pop(img->queue));
    }
    free(img->queue);
		free(img->dat);
		free(img);
	}
}
