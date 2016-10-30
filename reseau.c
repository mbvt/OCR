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
			*(r->biases+ pos_b+j) = pos_b+j;
			for(int k = 0; k<length_w;++k)
			{
				*(r->weight + pos_w + j*length_w + k) 
					= pos_w + j*length_w + k;
			}
		}
		pos_w+=length_n * length_w;
		pos_b+=length_n;
	}
	return r;
}

void get_biases(const Reseau *r, int rang, float **begin)
{
	int pos = 0, i = 1;
	for(; i< rang;++i)
		pos += r->size[i];	
	*begin = r->biases + pos;
}

void get_weight(const Reseau *r, int rang, int neurone, float **begin)
{
	int pos = 0, i = 1;
	for(; i<rang; ++i)
		pos += r->size[i-1]*r->size[i];
	*begin = r->weight + pos + r->size[i-1]*neurone;
}

float* feed_forward(const Reseau *r, float *data)
{
	for(int i = 1; i<r->length_size;++i)
	{
		data = sigmoid(r,i,z_calc(r,i,data));
	}
	return data;
}

float* z_calc(const Reseau *r, int rang, float *data)
{
	float *temp = calloc(r->size[rang],sizeof(float));
	float *beg_w, *beg_b;
	get_biases(r, rang, &beg_b);
	for(int i = 0; i<r->size[rang]; ++i)
	{
		get_weight(r,rang,i,&beg_w);
		for(int j = 0 ; j<r->size[rang-1]; ++j)
		{
			*(temp+i)+=*(beg_w+j)**(data+j);
		}
		*(temp+i)+=*(beg_b+i);
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
