# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "image.h"

Image* new_matrice(int w, int h, Categorie cat) 
{
	Image* img = malloc(sizeof(Image));
	img->w = w;
	img->h = h;
	img->dat = calloc(1,w*h*sizeof(unsigned char*));
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

Image* cut_image(Image* img, Categorie cat, int i_min, int i_max, int j_min, int j_max)
{
	assert(img && i_min>=0 && i_min<i_max && i_max<img->h && j_min>=0 && j_min<j_max && j_max<img->w);
	int h = i_max-i_min, w = j_max-j_min;
	Image *new_img = new_matrice(w, h, cat);	
	for(int i = 0;i<h;i++)
		for(int j = 0;j<w;j++)
		{
			set_pixel(new_img, i, j, get_pixel(img, i_min + i, j_min + j));
		}
	return new_img;
}

void del_image(Image* img)
{
	if(img)
	{
		free(img->dat);
		free(img);
	}
}
