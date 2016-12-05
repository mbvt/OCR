/* chargement.h */

# ifndef _OCROOT_CHARGEMENT_H_
# define _OCROOT_CHARGEMENT_H_

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "reseau.h"

struct Reseau* loading_file();

void traitement_size_array(char* chaine, struct Reseau *r);

void traitement_tab_size(char* chaine, struct Reseau *r);

void traitement_tab_b(char* token, struct Reseau *r);

void traitement_tab_w(char* token, struct Reseau *r);

int str_to_int(char* token);

float string_to_float(char* token);

# endif /* _OCROOT_CHARGEMENT_H_ */
