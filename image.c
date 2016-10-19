# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "image.h"

Image* new_matrice(int w, int h, Categorie cat) 
{
	Image* img = malloc(sizeof(Image));
	assert(img);
	img->w = w;
	img->h = h;
	img->dat = calloc(w*h,sizeof(unsigned char*));
	assert(img->dat);
	img->cat = cat;
	return img;
}

void set_pixel(Image* img, int i, int j, unsigned char px)
{
	assert(img && i>=0 && i<img->h && j>=0 && j<img->w);
	*(img->dat+img->h*i+j) = px;
}

unsigned char get_pixel(Image *img, int i , int j)
{	
	assert(img && i>=0 && i<img->h && j>=0 && j<img->w);
	return *(img->dat+img->h*i+j);
}

void del_image(Image* img)
{
	if(img)
	{
		free(img->dat);
		free(img);
	}
}
