// read.h list of functions to read an image

# ifndef _OCROOT_READ_H_
# define _OCROOT_READ_H_

# include <stdlib.h>
# include <stdio.h>
# include "image.h"
# include "apprentissage.h"
# include "load_image.h"   
# include "decoupage.h"

struct matrice
{
	int width, height;
	float *mat;
};

char *read_image(struct reseau *r, char* path);
struct matrice *resize(struct image *img, struct letter *letter);
char get_caractere(float *out);
struct matrice *get_matrice(struct matrice *matrice);

struct matrice *init_matrice(int width, int height);

void set_val(struct matrice *matrice, int i, int j, float val);

float get_val(struct matrice *matrice, int i, int j);

char get_char(unsigned char *mat);

char* get_text(struct image *img);

# endif /* _OCROOT_READ_H_ */
