//reseau.h list of functions about our neurone network

# ifndef _OCROOT_RESEAU_H_
# define _OCROOT_RESEAU_H_

# include <stdlib.h>
# include <math.h>

# include "matrice.h"

typedef struct Reseau
{
	int *size;
	int length_size, length_bias, length_weight;
	float *biases;
	float *weight;
}Reseau;

//Function who construct a neural network with random value
Reseau* construct(int *size, int ls);
//Function who get biases of a layer
void get_biases(const Reseau *r, int rang, float **begin);
//Function who get weights of a layer
void get_weight(const Reseau *r, int rang,  float **begin);
//Function who execute the neural network
float *feed_forward(const Reseau *r, float *data);
//Function who compute z for the sigmoid
float *z_calc(const Reseau *r, int rang, float *data);
//Function who compute the sigmoid
float *sigmoid(const Reseau *r , int rang, float *data);

# endif /* _OCROOT_RESEAU_H_ */
