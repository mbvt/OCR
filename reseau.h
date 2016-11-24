//reseau.h list of functions about our neurone network

# ifndef _OCROOT_RESEAU_H_
# define _OCROOT_RESEAU_H_

# include <stdlib.h>
# include <math.h>
# include "matrice.h"

struct reseau
{
	int *size;
	int length_size, length_bias, length_weight;
	float *biases;
	float *weight;
};

//Function who construct a neural network with random value
struct reseau* construct(int *size, int ls);
int get_pos_biases(const struct reseau *r, int rang);
int get_pos_weight(const struct reseau *r, int rang);
//Function who get biases of a layer
void get_biases(const struct reseau *r, int rang, float **begin);
//Function who get weights of a layer
void get_weight(const struct reseau *r, int rang,  float **begin);
//Function who execute the neural network
float *feed_forward(const struct reseau *r, float *data);
//Function who compute z for the sigmoid
float *z_calc(const struct reseau *r, int rang, float *data);
//Function who compute the sigmoid
float *sigmoid(const struct reseau *r , int rang, float *data);

void free_reseau(struct reseau *r);
# endif /* _OCROOT_RESEAU_H_ */
