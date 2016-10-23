# include "decoupage.h"
# include <stdio.h>

int not_empty(Image *img, int i, int j, int min, int max)
{
	assert(img && (
			i == -1 && j>=0 && j<img->w ||
			j == -1 && i>=0 && i<img->h));
	int r = 0;
	if(i==-1)
		for(i=min;i<max && r == 0;i++)
			r = get_pixel(img,i,j);
	else
		for(j=min;j<max && r == 0;j++)
			r = get_pixel(img,i,j);
	return r;
}

void search_text(Image * img)
{
	int i_min = -1;
	int i_max = -1;
	int j_min = -1;
	int j_max = -1;
	for(int i=0; i<img->h && i_min == -1; ++i)
		i_min=not_empty(img,i,-1,0,img->w)?i:-1;

	for(int i=img->h-1; i>0 && i_max == -1; --i)
		i_max=not_empty(img,i,-1,0,img->w)?i:-1;

	for(int j=0; j<img->w && j_min == -1; ++j)
		j_min=not_empty(img,-1,j,0,img->h)?j:-1;

	for(int j=img->w-1; j>0 && j_max == -1; --j)
		j_max=not_empty(img,-1,j,0,img->h)?j:-1;
	set_text(img,i_min,i_max,j_min,j_max);
}

void search_row(Image *img)
{
	Text *te = img->te;
	int i_min=-1;
	for(int i = te->i_min; i< te->i_max; ++i)
	{
		int r = not_empty(img,i,-1,te->j_min,te->j_max);
		if(r!=0 && i_min == -1)
			i_min=i;
		else if((r==0 || i+1 == te->i_max) && i_min != -1){
			add_row(te,i_min,i);
			i_min = -1;
		}
	}
}

void search_letter(Image *img)
{
	Text *te = img->te;
	for(int k=0; k< te->nb_li; ++k)
	{
		Ligne li= *(te->li + k);
		int j_min = -1;
		for(int j=te->j_min; j<te->j_max; ++j)
		{
			int r = not_empty(img,-1,j,li.i_min,li.i_max);
			if(r!=0 && j_min == -1)
				j_min = j;
			else if((r==0 || j+1== te->j_max) && j_min != -1){
				add_letter(&li,j_min,j);
				j_min = -1;
			}
		}
		*(te->li + k) = li;
	}
}
