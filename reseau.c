# include "reseau.h"
# include <stdio.h>
Reseau* construct(int *size, int ls)
{
	Reseau *r = malloc(sizeof(Reseau));
	r->size = size;
	r->length_size = ls;
	int t_biases = 0;
	int t_weight = 0;
	for(int i = 1; i < ls;++i)
	{
		t_biases+=*(size+i);
		t_weight+=*(size+i-1)**(size+i);
	} 
	r->length_bias = t_biases;
	r->length_weight = t_weight;
	r->biases = calloc(t_biases,sizeof(float));
	r->weight = calloc(t_weight,sizeof(float));
	int pos_w = 0, pos_b = 0;
	for(int i = 1; i<ls; ++i)
	{
		int length_n = *(size+i);
		int length_w = *(size+i-1);
		for(int j = 0; j<length_n;++j)
		{
			*(r->biases+ pos_b+j) = (double)rand() / (double)((unsigned)RAND_MAX + 1);
			for(int k = 0; k<length_w;++k)
			{
				*(r->weight + pos_w + j*length_w + k) 
					= (double)rand() / (double)((unsigned)RAND_MAX + 1);
			}
		}
		pos_w+=length_n * length_w;
		pos_b+=length_n;
	}
	return r;
}


int get_pos_biases(const Reseau *r, int rang)
{
	int pos = 0, i = 1;
	for(; i< rang;++i)
		pos += r->size[i];
	return pos;
}

int get_pos_weight(const Reseau *r, int rang)
{
	int pos = 0, i = 1;
	for(; i<rang; ++i)
		pos += r->size[i-1]*r->size[i];
	return pos;
}

void get_biases(const Reseau *r, int rang, float **begin)
{	
	*begin = r->biases + get_pos_biases(r,rang);
}


void get_weight(const Reseau *r, int rang,  float **begin)
{
	*begin = r->weight + get_pos_weight(r,rang);
}

void affiche_bias(float *f, int rang, int length)
{
	printf ("\nbiases rang %d : \n\n",rang);
	for(int i = 0; i<length; ++i)
		printf("bias %d : %f\n",i,*(f+i));
}

void affiche_weight(float *f, int rang, int length1, int length2)
{
	printf("\nweight rang %d : \n\n",rang);
	for(int i = 0; i<length1; ++i)
		for(int j = 0; j<length2; ++j)
			printf("weight %d : %f\n",i,*(f+i*length2+j));
}

void affiche_out(float *f, int rang, int length)
{
	printf("\noutput rang %d : \n\n",rang);
	for(int i = 0; i<length; ++i)
		printf("output %d : %f\n",i,*(f+i));
}

float* feed_forward(const Reseau *r, float *data)
{
	affiche_out(data,0,r->size[0]);
	for(int i = 1; i<r->length_size;++i)
	{
		float *w, *b;
		get_biases(r, i, &b);
		get_weight(r, i, &w);
		
		affiche_bias(b,i,r->size[i]);
		affiche_weight(w,i,r->size[i], r->size[i-1]);
		data = sigmoid(r,i,z_calc(r,i,data));
		affiche_out(data,i,r->size[i]);
	}
	return data;
}

float* z_calc(const Reseau *r, int rang, float *data)
{
	float *w, *b;
	get_biases(r, rang, &b);
	get_weight(r,rang,&w);
	float *temp = multiplie_array(w,data,r->size[rang],r->size[rang-1],1);
	for(int i = 0; i<r->size[rang]; ++i)
	{
		*(temp+i)+=*(b+i);
	}
	return temp;
}

float* sigmoid(const Reseau *r, int rang, float *data)
{
	for(int i = 0; i<r->size[rang]; ++i)
	{	
		*(data+i)=1.0/(1.0+exp(-1.0**(data+i)));
	}
	return data;
}
