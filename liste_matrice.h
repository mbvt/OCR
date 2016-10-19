// liste_matrice.h list some function for matrice collection

# ifndef _OCROOT_LISTE_MATRICE_H_
# define _OCROOT_LISTE_MATRICE_H_

# include "image.h"

//stock a list of image
typedef struct Mliste
{
	int l;
	Image *liste;
} Mliste;

//Initialize an empty liste
Mliste* new_liste(void);
//Add an element
void add_elem(Mliste *ml, Image *i);
//Remove an element
void del_liste(Mliste *ml);

#endif /* _OCROOT_LISTE_MATRICE_H_ */
