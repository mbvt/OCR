# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "image.h"

Image* new_matrice(int w, int h) 
{
	Image* img = malloc(sizeof(Image));
	assert(img);
	img->w = w;
	img->h = h;
	img->dat = calloc(w*h,sizeof(unsigned char*));
	assert(img->dat);
	img->te = NULL;
	return img;
}

void set_pixel(Image* img, int i, int j, unsigned char px)
{
	assert(img && i>=0 && i<img->h && j>=0 && j<img->w);
	*(img->dat+img->h*i+j) = px;
}

void set_text(Image *img, int i_min, int i_max, int j_min, int j_max)
{
	Text* te = malloc(sizeof(Text));
	assert(te);
	te->i_min = i_min;
	te->i_max = i_max;
	te->j_min = j_min;
	te->j_max = j_max;
	te->nb_li = 0;
	te->li = NULL;
	img->te = te;
}

void add_ligne(Text *te, int i_min, int i_max)
{
	Ligne *li = malloc(sizeof(Ligne));
	assert(li);
	li->i_min = i_min;
	li->i_max = i_max;
	li->nb_le++;
	li->le = null;
	te->nb_li++;
	te->li = realloc(te->li,te->nb_li);
	*(te->li + te->nb_li -1)=li;
}

void add_lettre(Ligne *li, int j_min, int j_max)
{
	Lettre *le = malloc(sizeof(Lettre));
	assert(le);
	le->j_min = j_min;
	le->j_max = j_max;
	li->nb_le++;
	li->le = realloc(li->le, li->nb_le);
	*(li->le + li->nb_le - 1) = le;
}

unsigned char get_pixel(Image *img, int i , int j)
{	
	assert(img && i>=0 && i<img->h && j>=0 && j<img->w);
	return *(img->dat+img->h*i+j);
}

Text* get_text(Image *img)
{
	return img->te;
}

Ligne* get_ligne(Text* te, int i)
{
	assert(i < te->nb_li);
	return *(te->li + i);
}

Lettre* get_lettre(Ligne* li, int i)
{
	assert(i < li->nb_le);
	return *(li->le + i);
}

void del_image(Image* img)
{
	if(img)
	{
		Text* te = img->te;
		for(int i = 0; i<img->nb_li;i++)
		{
			Ligne *li = *(te->li + i);
			for(int j = 0; j<li->nb_le;j++)
			{
				free(li->le + i);
			}
			free(li);
		}
		free(te);
		free(img->dat);
		free(img);
	}
}
