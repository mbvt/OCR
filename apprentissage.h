// apprentissage.h list of fonction for our neural network learning

# ifndef _OCROOT_APPRENTISSAGE_H_
# define _OCROOT_APPRENTISSAGE_H_

# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "reseau.h"
# include "matrice.h"

struct teach
{
	float *data, result;
};

//Function which shuffle an array of Teach
void shuffle(struct teach *t, int length);
//Function which create two array with the size of weights and biases initialize to 0
void zeros(const struct reseau *r, float **n_b, float **n_w);

void put_nabla_w(const struct reseau *r, int rang, float *n_w, float *ori);
void put_nabla_b(const struct reseau *r, int rang, float *n_b, float *ori);
void put_activations(const struct reseau *r, int rang, float *activations, float *ori);
void get_nabla_w(const struct reseau *r, int rang, float *n_w, float **des);
void get_nabla_b(const struct reseau *r, int rang, float *n_b, float **des);
void get_activations(const struct reseau *r, int rang, float *activations, float **des);
//Function which get news value for nabla;
void maj_nabla(const struct reseau *r, float *n_b, float *n_w, float *d_n_b, float *d_n_w);
//Function which get news value for biases and weight
void maj_reseau(struct reseau *r, float *n_b, float *n_w, int batch_size, const float eta);
//Function which compute the sigmoid prime
float* sigmoid_prime(struct reseau *r, int rang, float *data);
//Function which compute the cost derivative function
float* cost_derivative(struct reseau *r, int rang, float *data, float result);
//Function which calcul delta for the final layer
float* calc_first_delta(struct reseau *r, int rang, float *data, float result);
//Function which calcul delta for the others layer
void calc_delta(struct reseau *r, int rang, float *data, float **delta);
//Function which evaluate the network
int evaluate(struct reseau *r, const struct teach* test_data, int length_tsd);
//Function which apply back propagation algorithme to the network
void back_propagation(struct reseau *r, const struct teach current_val, float **d_n_b, float **d_n_w);
//Function which teach to the network
void teach_reseau(struct reseau *r, const struct teach *tr_data, int length_trd, const int m_b_size, const float eta);
//Function which manage the learning of network
void sgd(struct reseau *r, struct teach *tr_data, int length_trd, int epoch, const int m_b_size, 
	float eta,const struct teach* test_data, int length_tsd);
# endif /* _OCROOT_APPRENTISSAGE_H_ */
