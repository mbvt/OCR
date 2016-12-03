// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>
# include <assert.h> 
# include <math.h>

# include "image.h"
# include "load_image.h"
# include "decoupage.h"
# include "matrice.h"
# include "reseau.h"
//# include "read.h"

void print_mat(float *mat, int lin, int col)
{
		for(int i = 0; i < lin; ++i)
		{
			for(int j = 0; j < col; ++j)
			{
				printf("| %f ",*(mat + i * col + j));
			}
			printf("|\n");
		}
}

float *sigmoid(float *z, int lin, int col)
{
	float *temp = malloc(lin*col*sizeof(float));
	for (int i = 0; i < lin * col; ++i)
	{
		*(temp + i) = 1.0/(1.0 + expf(-*(z + i)));
	}
	return temp;
}

float *sigmoid_prime(float *z, int lin, int col)
{
	float *temp = malloc(lin*col*sizeof(float));
	for (int i = 0; i < lin * col; ++i)
	{
		*(temp + i) = expf(-*(z+i))/powf(1.0+expf(-*(z+i)),2);		
	}
	return temp;
}

//1.5 -> 55543
int main(void)
{
	float eta = 3.4;
	int size[] = {2,3,1};
	struct reseau *r = construct(size, 3);

	float **dat = malloc(4 * sizeof(float*));
	float *x = calloc(2,sizeof(float));
	float *x1 = calloc(2,sizeof(float));
	float *x2 = calloc(2,sizeof(float));
	float *x3 = calloc(2,sizeof(float));
	*x1 = 1;
	*(x2+1)=1;
	*x3=1;
	*(x3+1)=1;
	*dat = x3;
	*(dat+1)=x1;
	*(dat+2)=x2;
	*(dat+3)=x;
	float out[]		= {0,1,1,0};
	float *z2;
	float *z2p;
	float *a2;
	float *z3;
	float *z3p;
	float *yc;
	float *at;
	float *dj3;
	float *dj2;
	float	*wt;
	float *d2;
	float *xt;
	float *w1;
	float *w2;
	float *d3;
	float *b1;
	float *b2;
	float j = 1;
	int cpt = 0;
	do
	{
		float count = 0;
		cpt++;
		for(int k = 0; k < 4; ++k)
		{
			x 	= *(dat+k);
			printf("Iteration : %d\n",cpt);
			get_weight(r,1,&w1);
			get_weight(r,2,&w2);
			get_biases(r,1,&b1);
			get_biases(r,2,&b2);
			
			z2 	= multiplie_array(x,w1,1,r->size[0],r->size[1]);
			addition_scalaire(z2, b1, r->size[1]);
			a2 	= sigmoid(z2, 1, r->size[1]);
			z3 	= multiplie_array(a2, w2, 1,r->size[1],r->size[2]);
			addition_scalaire(z3, b2, r->size[2]);
			yc 	= sigmoid(z3,1,r->size[2]);
			for (int i = 0; i < r->size[2]; ++i)
				*(yc + i) = out[i] - *(yc + i);
			for (int i = 0; i < r->size[2]; ++i)
				count += powf(*(yc + i),2);
			z3p	= sigmoid_prime(z3,1,r->size[2]);
			d3 	= multiplie_scalaire(yc,z3p,r->size[2]);
			at 	= transpose_array(a2,1,r->size[1]);
			dj3 = multiplie_array(at,d3,r->size[1],1,r->size[2]);
			wt 	= transpose_array(w2,r->size[1],r->size[2]);
			d2 	= multiplie_array(d3,wt,1,r->size[2],r->size[1]);
			z2p = sigmoid_prime(z2,1,r->size[1]);
			d2 	= multiplie_scalaire(d2, z2p, r->size[1]);
			xt 	= transpose_array(x,1,r->size[0]);
			dj2 = multiplie_array(xt,d2,r->size[0],1,r->size[1]);
			
			for (int i = 0; i < r->size[0]*r->size[1]; ++i)
				*(w1 + i) += eta	*	*(dj2+i);
			for (int i = 0; i < r->size[1]*r->size[2]; ++i)
				*(w2 + i) += eta	*	*(dj3+i);
			for (int i = 0; i < r->size[1]; ++i)
				*(b1 + i) += eta	*	*(d2 + i);
			for (int i = 0; i < r->size[2]; ++i)
				*(b2 + i) += eta	*	*(d3 + i);

			free(z2);
			free(a2);
			free(z3);
			free(yc);
			free(z3p);
			free(at);
			free(dj3);
			free(d3);
			free(wt);
			free(d2);
			free(dj2);
		}
		j = count;
		printf("------ j ------\n");
		printf("%f\n",j);
	}while (j > 0.001);
	free_reseau(r);
	free(dat);
	free(x);
	free(x1);
	free(x2);
	free(x3);
}
