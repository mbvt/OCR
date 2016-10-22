# include "decoupage.h"

Image* cut(Image *img, Categorie cat, int i_min, int i_max, int j_min, int j_max)
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

int not_empty(Image *img, int i, int j)
{
	assert(img && (
			i == -1 && j>=0 && j<img->w ||
			j == -1 && i>=0 && i<img->h);
	int r = 0;
	if(i==-1)
		for(i=0;i<img->h && r == 0;i++)
			r = get_pixel(img,i,j);
	else
		for(j=0;j<img->w && r == 0;j++)
			r = get_pixel(img,i,j);
	return r;
}

void get_text(Image * img)
{
	int i_min = -1;
	int i_max = -1;
	int j_min = -1;
	int j_max = -1;
	for(int i=0; i<img->h && i_min == -1; ++i)
		i_min=not_empty(img,i,-1)?i:-1;
	for(int i=img->h-1; i>0 && i_max == -1; --i)
		i_max=not_empty(img,i,-1)?i:-1;
	for(int j=0; j<img->w && j_min == -1; ++j)
		j_min=not_empty(img,-1,j)?j:-1;
	for(int j=img->w-1; j>0 && j_max == -1; --j)
		j_max=not_empty(img,-1,j)?j:-1;
	set_text(img,i_min,i_max,j_min,j_max);
}