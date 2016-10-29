// apprentissage.h list of fonction for our neural network learning

# ifndef _OCROOT_APPRENTISSAGE_H_
# define _OCROOT_APPRENTISSAGE_H_

# include <stdlib.h>
# include <time.h>

typedef struct Teach
{
	float *data, result;
}Teach;

void shuffle(Teach *t, int length);
void zeros(const Reseau *r, float **n_b, float **n_w);
void maj_nabla(const Reseau *r, float *n_b, float *n_w, float *d_n_b, float *d_n_w);
void maj_reseau(Reseau *r, float *n_b, float *n_w, int batch_size, float eta);
void copy_array(float *des, float *ori, int n);
float* sigmoid_prime(Reseau *r, int rang, float *data);
void cost_derivative(Reseau *r, int rang, float *data, float result);
float* calc_delta(Reseau *r, int rang, float *z, float *activation, float result)
void sgd(Reseau *r, Teach *tr_data, int length_trd, int epoch, int m_b_size, float eta,
	Teach* test_data, int length_tsd);
void teach_reseau(Reseau *r, Teach *tr_data, int length_trd, int m_b_size, float eta);
void back_propagation(Reseau *r, Teach current_val, float **d_n_b, float **d_n_w);

# endif /* _OCROOT_APPRENTISSAGE_H_ */
