// apprentissage.h list of fonction for our neural network learning

# ifndef _OCROOT_APPRENTISSAGE_H_
# define _OCROOT_APPRENTISSAGE_H_

# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "reseau.h"

typedef struct Teach
{
	float *data, result;
}Teach;

void shuffle(Teach *t, int length);
void copy_array(float *des, float *ori, int n);
int evaluate(Reseau *r, const Teach* test_data, int length_tsd);
void sgd(Reseau *r, Teach *tr_data, int length_trd, int epoch, float eta,
	const Teach* test_data, int length_tsd);
void teach_reseau(Reseau *r, const Teach *tr_data, int length_trd, const float eta);
void back_propagation(Reseau *r, const Teach current_val, const float eta);
float* first_delta(Reseau *r, int rang, float *delta, float *activation);

# endif /* _OCROOT_APPRENTISSAGE_H_ */
