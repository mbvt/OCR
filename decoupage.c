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

Image *cut_column(Image* img)
{
  Image* a;
  int i_min = -1;
  int i_max = -1;
  int j_min = 0;
  int j_max = img-> w;
  for(int i = 0; i < img->h; i++)
    {
      int res = 0;
      for(int j = 0 ; j < img->w; j++)
	{
	  res = res + get_pixel(Image* img, i, j);;
	}   
      if(res > 0 && i_min == -1)
	i_min = i;
      if(res = 0 && i_min == -1)
	{
	  i_max = i-1;
	  a = cut_image(Image* img, COLONNE, i_min, i_max, j_min, j_max);
	}
    }
  return a; 
}
