# include "decoupage.h"

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