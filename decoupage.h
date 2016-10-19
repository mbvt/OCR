// decoupage.h list of functions use to get sub matrice

# ifndef _OCROOT_DECOUPAGE_H_
# define _OCROOT_DECOUPAGE_H_

# include "image.h"

// Function who get a sub matrice between horizontal and vertical coordonnee and set a categorie
Image* cut_image(Image *img, Categorie cat, int i_min, int i_max, int j_min, int j_max);
// Use to find column return a list of column
Image *cut_column(Image* img);

#endif /* _OCROOT_DECOUPAGE_H_ */
