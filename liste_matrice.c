# include <stdlib.h>
# include <assert.h>

# include "liste_matrice.h"

Mliste* new_liste(void)
{
	Mliste *ml = malloc(sizeof(Mliste));
	assert(ml);
	ml->l = 0;
	ml->liste = NULL;
	return ml;
}

void add_elem(Mliste *ml, Image *i)
{
	ml->l++;
	ml->liste = realloc(ml->liste,ml->l+1);
	*(ml->liste + ml->l - 1)=*i;	
}

void del_liste(Mliste *ml)
{
	Image *t = ml->liste;
	for(; t<t+ml->l;++t)
	{
		del_image(t);
	}
	free(ml->liste);
	free(ml);
}
