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
int not_empty(Image *img, int i, int j, int min, int max);

//Find text zone
void search_text(Image * img);
//Find rows in image
void search_row(Image *img);
//Find letter in image
void search_letter(Image *img);
#endif /* _OCROOT_DECOUPAGE_H_ */
