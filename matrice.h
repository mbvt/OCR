//matrice.h list some function about matrice

# ifndef _OCROOT_MATRICE_H_
# define _OCROOT_MATRICE_H_

# include <stdlib.h> 

//Function which copy an array;
void copy_array(float *des, float *ori, int n);
//Function which transpose an array
float *transpose_array(float *a, int l, int h);
//Function which make the product of two array
float *multiplie_array(float *a, float *b, int l, int c, int h);

float *multiplie_scalaire(float *a, float *b, int t);

void addition_scalaire(float *a, float *b, int t);
# endif /* _OCROOT_MATRICE_H_ */
