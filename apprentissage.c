# include "apprentissage.h"

void shuffle(Teach *t, int length)
{
	srand(time(NULL));
	for(int i = length-1; i>0; --i)
	{
		int j = rand() %(i+1);
		Teach p = *(t+i);
		*(t+i) = *(t+j);
		*(t+j) = p; 
	}
}

void zeros(const Reseau *r, float **n_b, float **n_w)
{
	*n_b = calloc(r->length_biases,sizeof(float));
	*n_w = calloc(r->length_weigth,sizeof(float));
}

void maj_nabla(const Reseau *r, float *n_b, float *n_w, float *d_n_b, float *d_n_w)
{
	int i = 0;
	for(;i<r->length_bias;++i)
	{
		*(n_b+i)=*(n_b+i)+*(d_n_b+i);
		*(n_w+i)=*(n_w+i)+*(d_n_w+i);
	}
	for(;i<r->length_weight;++i)
		*(n_w+i)=*(n_w+i)+*(d_n_w+i);
	free(d_n_b);
	free(d_n_w);
}

void maj_reseau(Reseau *r, float *n_b, float *n_w, int batch_size, float eta)
{
	int i = 0;
	float tx = eta/(float)batch_size;
	for(;i<r->length_bias;++i)
	{
		*(r->biases+i) = *(r->biases+i)-tx**(n_b+i);
		*(r->weight+i) = *(r->weight+i)-tx**(n_w+i);
	}
	for(;i<r->length_weight;++i)
		*(r->weight+i) = *(r->weight+i)-tx**(n_w+i);
	free(n_b);
	free(n_w);
}

void copy_array(float *des, float *ori, int n)
{
	float *fin = ori+n;
	for(;ori<fin;++ori,++des)
	{
		*des = *ori;
	}
}

float* sigmoid_prime(Reseau *r, int rang, float *data)
{
	float *temp = sigmoid(r,i,z_calc(r,i,data));
	for(int i = 0; i < r->size[rang];++i)
	{
		*(temp+i) = *(temp+i)*(-1.0**(temp+i));
	}	
	return temp;
}

void cost_derivative(Reseau *r, int rang, float *data, float result)
{
	for(int i = 0; i<r->size[rang]; ++i)
	{
		*(data+i)-= result;
	}
}

float* calc_delta(Reseau *r, int rang, float *z, float *activation, float result)
{
	float *temp = sigmoid_prime(r,rang,z);
	cost_derivative(r,rang,activation,result);
	for(int i = 0; i<r->size[rang]; ++i)
	{
		*(temp + i) = *(activation+i)**(temp+i);
	}
	return temp;
}

float* first_delta(Reseau *r, int rang, float *delta, float *activation)
{ 
	float *temp = calloc(r->size[rang-1]);
	for(int i = 0; i<*(r->size[rang-1]);++i)
	{
		
	}
}

void back_propagation(Reseau *r, Teach current_val, float *d_n_b, float *d_n_w)
{
	zeros(r, &d_n_b, &d_n_w);
	float *activation = current_val.data;
	float *activations = calloc(r->length_biais+r->size[0],sizeof(float));
	float *zs = calloc(r->length_biais,sizeof(float));
	copy_array(activations,activation,r->size[0]);
	int pos_bz = 0, pos_ba = r->size[0], pos_w = 0;
	int i = 1;
	float *z = NULL;
	for(; i<r->length_size;++i)
	{
		z = z_calc(r,i,activation);
		activation = sigmoid(r,i,z);
		copy_array(zs+pos_bz,z,r->size[i]);
		copy_array(activations+pos_ba,activation,r->size[i]);
		free(z);
		pos_bz+=r->size[i];
		pos_ba+=r->size[i];
		pos_w+=r->size[i]*r->size[i-1];
		
	}
	--i;
	pos_bz-=r->size[i];
	pos_ba-=r->size[i];	
	pos_w-=r->size[i]*r->size[i-1];
	copy_array(z,zs+pos_bz,r->size[i]);
	float* delta = calc_delta(r,i,z,activation,current_val->result);
	pos_ba-=r->size[i-1];
	copy_array(activation,activations+pos_ba,r->size[i-1]);

}

void sgd(Reseau *r, Teach *tr_data, int length_trd, int epoch, int m_b_size, float eta,
	Teach* test_data, int length_tsd)
{
	for(int i = 0; i<epoch;++i)
	{
		shuffle(tr_data,length_trd);
		//update1
	}
}
