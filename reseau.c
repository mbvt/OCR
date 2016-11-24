# include "reseau.h"
# include <stdio.h>

struct reseau* construct(int *size, int ls)
{
	struct reseau *r = malloc(sizeof(struct reseau));
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


int get_pos_biases(const struct reseau *r, int rang)
{
	int pos = 0, i = 1;
	for(; i< rang;++i)
		pos += r->size[i];
	return pos;
}

int get_pos_weight(const struct reseau *r, int rang)
{
	int pos = 0, i = 1;
	for(; i<rang; ++i)
		pos += r->size[i-1]*r->size[i];
	return pos;
}

void get_biases(const struct reseau *r, int rang, float **begin)
{	
	*begin = r->biases + get_pos_biases(r,rang);
}


void get_weight(const struct reseau *r, int rang,  float **begin)
{
	*begin = r->weight + get_pos_weight(r,rang);
}

float* feed_forward(const struct reseau *r, float *data)
{
	for(int i = 1; i<r->length_size;++i)
	{
		float *w, *b;
		get_biases(r, i, &b);
		get_weight(r, i, &w);
		
		data = sigmoid(r,i,z_calc(r,i,data));
	}
	return data;
}

float* z_calc(const struct reseau *r, int rang, float *data)
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

float* sigmoid(const struct reseau *r, int rang, float *data)
{
	for(int i = 0; i<r->size[rang]; ++i)
	{	
		*(data+i)=1.0/(1.0+exp(-1.0**(data+i)));
	}
	return data;
}

void free_reseau(struct reseau *r)
{
  free(r->biases);
  free(r->weight);
  free(r);
}
