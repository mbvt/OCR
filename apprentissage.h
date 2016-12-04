// apprentissage.h list of function for our neural network learning

# ifndef _OCROOT_APPRENTISSAGE_H_
# define _OCROOT_APPRENTISSAGE_H_

# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "reseau.h"
# include "matrice.h"
# include "image.h"

struct teach
{
	struct letter *letter;
	float  result;
};

float *sigmoid_prime(float *z, int col);
float *sigmoida(float *z, int col);
//Function which evaluate the network
int evaluate(struct reseau *r, const struct teach* test_data, int length_tsd,
float taux_erreur);
//Function which apply back propagation algorithme to the network
float back_propagation(struct reseau *r, float eta, float *data, float res);
//Function which teach to the network
void launch_apprentissage(struct reseau *r,	float eta, float taux_erreur);

struct teach *preparation(struct image *img, int nb);
# endif /* _OCROOT_APPRENTISSAGE_H_ */
