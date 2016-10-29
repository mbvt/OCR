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
	printf("%d : %d\n",t_biases, t_weight);
	r->biases = calloc(t_biases,sizeof(float));
	r->weight = calloc(t_weight,sizeof(float));
	int pos_w = 0, pos_b = 0;
	for(int i = 1; i<ls; ++i)
	{
		int length_n = *(size+i);
		int length_w = *(size+i-1);
		printf("%d : %d\n", length_n, length_w);
		for(int j = 0; j<length_n;++j)
		{
			*(r->biases+ pos_b+j) = pos_b + j;
			for(int k = 0; k<length_w;++k)
			{
				*(r->weight + pos_w + j*length_w + k) = pos_w + j*length_w + k;
			}
		}
		pos_w+=length_n * length_w;
		pos_b+=length_n;
	}
	return r;
}

void get_biases(const Reseau *r, int rang, float **begin, float **end)
{
	int pos = 0, i = 1;
	rang++;
	for(; i< rang;++i)
		pos += r->size[i];	
	*begin = r->biases + pos;
	*end = *begin + r->size[i];
}

void get_weight(const Reseau *r, int rang, int neurone, float **begin, float **end)
{
	int pos = 0, i = 1;
	rang++;
	for(; i<rang; ++i)
		pos += r->size[i-1]*r->size[i];
	*begin = r->weight + pos + r->size[i-1]*neurone;
	*end = *begin + r->size[i-1];
}
