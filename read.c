# include "read.h"

char * read_image(struct reseau *r, char* path)
{
	char *res = calloc(1000, sizeof(char));
	struct image *mat = convert_image(path);
	search_text(mat);
	struct letter *letter;
	int i = 0;
	while((letter = get_letter(mat)) == NULL)
	{
		res[i] = get_caractere(feed_forward(r, get_matrice(resize(mat,
		letter))->mat));
	}
	return res;
}

char get_caractere(float *out)
{
	int c = 63;
	for (int i = 1; i < 63; ++i)
	{
		if(fabsf(*out - (float) i / (float) 63) < 0.25)
			c = i;
	}
	if (c < 11)
		return c + 48;
	else if (c < 37)
		return c + 65;
	else if (c < 63)
		return c + 97;
	return '.';
}

int not_empty_mat(struct matrice *matrice, int i, int j, int min, int max)
{
	int r = 0;
	if (i == -1)
		for (i = min; i < max; ++i)
			r += *(matrice->mat + i * matrice->width + j);
	else
		for (j = min; j < max; ++j)
			r += *(matrice->mat + i * matrice->width + j);
	return r;
}

struct matrice *resize(struct image *img, struct letter *letter)
{
	int height 							= letter->i_max - letter->i_min;
	int width 							= letter->j_max - letter->j_min;
	struct matrice *matrice = init_matrice(width, height);
	
	for (int i = letter->i_min; i < letter->i_max; ++i)
		for (int j = letter->j_min; j < letter->j_max; ++j)
			set_val(matrice, i - letter->i_min, j - letter->j_min, get_pixel(img, i, j));
	
	int i_min				= -1;
	int j_min				= -1;
	int i_max				=	-1;
	int j_max				= -1;
	
	for (int i = 0; i < height && i_min == -1; ++i)
		i_min = not_empty_mat(matrice, i, -1, 0, width) ? i : -1;
	for (int i = height - 1; i > 0 && i_max == -1; --i)
		i_max = not_empty_mat(matrice, i, -1, 0, width) ? i : -1;
	for (int j = 0; j < width && j_min == -1; ++j)
		j_min = not_empty_mat(matrice, -1, j, 0, height) ? j : -1;
	for (int j = width - 1; j > 0 && j_max == -1; --j)
		j_max = not_empty_mat(matrice, -1, j, 0, height) ? j : -1;
	if(i_max < height)
		i_max++;
	if(j_max < width)
		j_max++;
	struct matrice *res 	= init_matrice(j_max - j_min, i_max - i_min);
	for (int i = i_min; i < i_max; ++i)
		for (int j = j_min; j < j_max; ++j)
			set_val(res, i - i_min, j - j_min, get_val(matrice, i, j));
	free(matrice);
	matrice = init_matrice(12,12);
	int dif_height 	= res->height - 12;
	int dif_width 	= res->width - 12;
	float rat_h 		= (float)res->height / (float)dif_height;
	if(rat_h != rat_h)
		rat_h = res->height;
	else if(rat_h == res->height)
		rat_h = 0;
	float rat_w			= (float)res->width / (float)dif_width;
	if(rat_w != rat_w)
		rat_w = res->width;
	else if (rat_w == res->width)
		rat_w = 0;
	int cpt_h = 0;
	int new_i = 0;
	for (int i = 0; i < res->height; ++i)
	{
		int new_j = 0;
		int cpt_w = 0;
		if(i != (int) (rat_h * (float) cpt_h))
		{
			for (int j = 0; j < res->width; ++j)
			{
				if(j != (int) (rat_w * (float) cpt_w))
				{
					set_val(matrice, new_i, new_j, get_val(res, i, j));
					new_j++;
				}
				else
					cpt_w++;
			}
			new_i++;
		}
		else
			cpt_h++;
	}		
	free(res);
	return matrice;
}

struct matrice *init_matrice(int width, int height)
{
	struct matrice *matrice = malloc(sizeof(struct matrice));
	matrice->width 	= width;
	matrice->height = height;
	matrice->mat 		= calloc(height * width, sizeof(float));
	return matrice;
}

struct matrice *get_matrice(struct matrice *matrice)
{
  struct matrice *res = init_matrice(16,16);
	for(int i = 0; i < matrice->height; ++i)
  {
    for(int j = 0; j < matrice->width; ++j)
    {
       set_val(res, i + 2, j + 2, get_val(matrice, i, j));
    }
  }
	free(matrice);
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
			printf("%d", (int) get_val(res, i, j));
		printf("\n");
	}
  return res;
 }

 void set_val(struct matrice *matrice, int i, int j, float val)
 {
		*(matrice->mat + i * matrice->width + j) = val;
 }

float get_val(struct matrice *matrice, int i, int j)
{
	return *(matrice->mat + i * matrice->width + j);
}

