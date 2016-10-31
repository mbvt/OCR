# include "matrice.h"

void copy_array(float *des, float *ori, int n)
{
	float *fin = ori+n;
	for(;ori<fin;++ori,++des)
	{
		*des = *ori;
	}
}

float* transpose_array(float *a, int l, int h)
{
	float *temp = malloc(l*h*sizeof(float));
	for(int i =0; i<l; ++i)
	{
		for(int j = 0; j<h; ++j)
		{
			*(temp + j*l+i) = *(a + i*h+j);
		}
	}
	return temp;
}

float* multiplie_array(float *a, float *b, int l, int c, int h)
{
	float *temp = calloc(l*h,sizeof(float));
	for(int i =0; i<l; ++i)
	{
		for(int j = 0; j<h; ++j)
		{
			for(int k =0; k<c;++k)
			{
				*(temp+i*h+j)+=*(a+i*c+k)**(b+k*h+j);
			}
		}
	}
	return temp;
}

