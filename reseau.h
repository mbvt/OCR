//reseau.h list of functions about your neurone network

# ifndef _OCROOT_RESEAU_H_
# define _OCROOT_RESEAU_H_

# include <stdlib.h>

typedef struct Reseau
{
	int *size;
	int length_size;
	float *biases;
	float *weight;
}Reseau;

Reseau* construct(int *size, int ls);

void get_biases(const Reseau *r, int rang, float **begin, float **end);
void get_weight(const Reseau *r, int rang, int neurone, float **begin, float **end);

# endif /* _OCROOT_RESEAU_H_ */
