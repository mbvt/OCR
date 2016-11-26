// read.h list of functions to read an image

# ifndef _OCROOT_READ_H_
# define _OCROOT_READ_H_

# include <stdlib.h>
# include "image.h"
# include "apprentissage.h"

# define TAILLE_J 20
# define TAILLE_I 30

unsigned char* get_matrice(struct image *img, struct letter *letter);

char get_char(unsigned char *mat);

char* get_text(struct image *img);

# endif /* _OCROOT_READ_H_ */
