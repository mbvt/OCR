// decoupage.h list of functions use to get sub matrice

# ifndef _OCROOT_DECOUPAGE_H_
# define _OCROOT_DECOUPAGE_H_

# include "image.h"

/*
	test if a column/row isn't empty
	i = -1 to test a column
	j = -1 to test a row
*/
int not_empty(Image *img, int i, int j);

//Find text zone
void get_text(Image * img);

#endif /* _OCROOT_DECOUPAGE_H_ */
