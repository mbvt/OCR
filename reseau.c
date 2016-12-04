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
  double cpt_b = 1, cpt_w = 1;
	for(int i = 1; i<ls; ++i)
	{
		int length_n = *(size+i);
		int length_w = *(size+i-1);
		for(int j = 0; j<length_n;++j)
		{
			*(r->biases+ pos_b+j) = (float)rand()/(float)(RAND_MAX);
      cpt_b++;
			for(int k = 0; k<length_w;++k)
			{
				*(r->weight + pos_w + j*length_w + k)	=
				(float)rand()/(float)(RAND_MAX);
        cpt_w++;
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
	float *w;
	float *z;
	float *b;
	for(int i = 1; i<r->length_size;++i)
	{
		get_weight(r,i,&w);
		get_biases(r,i,&b);
		z = multiplie_array(data, w, 1, *(r->size + i-1), *(r->size + i));
		addition_scalaire(z, b, *(r->size + i));
		data = sigmoid(z,*(r->size + i));
	}
	return data;
}

float* sigmoid(float *z, int col)
{
	float *temp = malloc(col * sizeof(float));
	for (int i = 0; i<col; ++i)
	{	
		*(temp + i) = 1.0 / (1.0 + expf(-*(z+i)));
	}
	return temp;
}


void free_reseau(struct reseau *r)
{
  free(r->biases);
  free(r->weight);
  free(r);
}
