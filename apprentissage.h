// apprentissage.h list of fonction for our neural network learning

# ifndef _OCROOT_APPRENTISSAGE_H_
# define _OCROOT_APPRENTISSAGE_H_

# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "reseau.h"
# include "matrice.h"

typedef struct Teach
{
	float *data, result;
}Teach;

//Function which shuffle an array of Teach
void shuffle(Teach *t, int length);
//Function which create two array with the size of weights and biases initialize to 0
void zeros(const Reseau *r, float **n_b, float **n_w);
//Function which get news value for nabla;
void maj_nabla(const Reseau *r, float *n_b, float *n_w, float *d_n_b, float *d_n_w);
//Function which get news value for biases and weight
void maj_reseau(Reseau *r, float *n_b, float *n_w, int batch_size, const float eta);
//Function which compute the sigmoid prime
float* sigmoid_prime(Reseau *r, int rang, float *data);
//Function which compute the cost derivative function
float* cost_derivative(Reseau *r, int rang, float *data, float result);
//Function which calcul delta for the final layer
float* calc_first_delta(Reseau *r, int rang, float *data, float result);
//Function which calcul delta for the others layer
void calc_delta(Reseau *r, int rang, float *data, float *delta);
//Function which evaluate the network
int evaluate(Reseau *r, const Teach* test_data, int length_tsd);
//Function which apply back propagation algorithme to the network
void back_propagation(Reseau *r, const Teach current_val, float **d_n_b, float **d_n_w);
//Function which teach to the network
void teach_reseau(Reseau *r, const Teach *tr_data, int length_trd, const int m_b_size, const float eta);
//Function which manage the learning of network
void sgd(Reseau *r, Teach *tr_data, int length_trd, int epoch, const int m_b_size, 
	float eta,const Teach* test_data, int length_tsd);
# endif /* _OCROOT_APPRENTISSAGE_H_ */
