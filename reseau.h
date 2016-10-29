//reseau.h list of functions about your neurone network

# ifndef _OCROOT_RESEAU_H_
# define _OCROOT_RESEAU_H_

# include <stdlib.h>
# include <math.h>

typedef struct Reseau
{
	int *size;
	int length_size;
	float *biases;
	float *weight;
}Reseau;

Reseau* construct(int *size, int ls);

void get_biases(const Reseau *r, int rang, float **begin);
void get_weight(const Reseau *r, int rang, int neurone, float **begin);
float* feed_forward(const Reseau *r, float *data);
float* sigmoid(const Reseau *r , int rang, float *data);

# endif /* _OCROOT_RESEAU_H_ */
