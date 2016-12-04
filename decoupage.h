// decoupage.h list of functions use to get sub matrice

# ifndef _OCROOT_DECOUPAGE_H_
# define _OCROOT_DECOUPAGE_H_

# include <assert.h>

# include "image.h"

/*
	test if a column/row isn't empty
	i = -1 to test a column
	j = -1 to test a row
*/
int not_empty(struct image *img, int i, int j, int min, int max);

//Find text zone
int search_text(struct image * img);

int search_block(struct image *img, int fmn, int fmx, int min, int max, int l);

# endif /* _OCROOT_DECOUPAGE_H_ */
