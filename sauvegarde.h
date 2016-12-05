//sauvegarde.h list of functions about our biases and weights saving file

# ifndef _OCROOT_SAUVEGARDE_H_
# define _OCROOT_SAUVEGARDE_H_

# include <stdlib.h>


//function who open and save biases and weights in file
void saving_file(struct reseau *r);

//function who writes biases in file
void save_size(int *bs, int length_s, FILE *fp);

//function who writes biases in file
void save_biases(float *bp, int length_b, FILE *fp);

//function who writes weights in file
void save_weights(float *wp, int length_w, FILE *p);

# endif /* _OCROOT_SAUVEGARDE_H_ */
