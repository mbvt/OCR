# include "read.h"

unsigned char* get_matrice(struct image *img, struct letter *letter)
{
  unsigned char *mat = calloc(TAILLE_I * TAILLE_J, sizeof(unsigned char));
  int i_min = (TAILLE_I - letter->i_max + letter->i_min) / 2;
  int j_min = (TAILLE_J - letter->j_max + letter->j_min) / 2;
  for(int i = letter->i_min; i < letter->i_max; ++i, ++i_min)
  {
    for(int j = letter->j_min, jmin = j_min; j < letter->j_max; ++j, ++jmin)
    {
      *(mat + i_min * TAILLE_J + jmin) = get_pixel(img, i, j);
    }
  }
  free(letter);
  return mat;
}
