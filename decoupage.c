# include "decoupage.h"

int not_empty(struct image *img, int i, int j, int min, int max)
{
  if(!(j<img->w))
    j--;
  if(!(i<img->h))
    i--;
	assert(img && (
			(i == -1 && j>=0 && j<img->w)||
			(j == -1 && i>=0 && i<img->h)));
	int r = 0;
	if(i==-1)
		for(i=min;i<max && r == 0;i++)
			r = get_pixel(img,i,j);
	else
		for(j=min;j<max && r == 0;j++)
			r = get_pixel(img,i,j);
	return r;
}

int search_text(struct image *img)
{
  int i_min = -1, i_max = -1, j_min = -1, j_max = -1;
	for(int i = 0; i < img->h && i_min == -1; ++i)
	  i_min = not_empty(img, i, -1, 0, img->w)? i : -1;
  for(int i = img->h-1; i > 0 && i_max == -1; --i)
    i_max = not_empty(img, i, -1, 0, img->w)? i : -1;
  for(int j = 0; j < img->w && j_min == -1; ++j)
    j_min = not_empty(img, -1, j, 0, img->h)? j : -1;
  for(int j = img->w-1; j > 0 && j_max == -1; --j)
    j_max = not_empty(img, -1, j, 0, img->h)? j : -1;
  return search_block(img, j_min, j_max, i_min, i_max, 0);
}

int search_block(struct image *img, int fmn, int fmx, int min, int max, int l)
{
	int cpt = 0;
  int s_min = -1;
  for(int i = min; i < max; ++i)
  {
    int r =
      (l)? not_empty(img, -1, i, fmn, fmx) : not_empty(img, i, -1, fmn, fmx);
    if(r && s_min == -1)
      s_min = i;
    else if((!r || i + 1 == max) && s_min != -1)
    {
      if(l){
        new_letter(img, fmn, fmx, s_min, i);
				cpt++;
			}
      else
        cpt +=  search_block(img, s_min, i, fmn, fmx, 1);
      s_min = -1;
    }
  }
	return cpt;
}
