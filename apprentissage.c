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
	*n_b = calloc(r->length_bias,sizeof(float));
	*n_w = calloc(r->length_weight,sizeof(float));
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

void maj_reseau(Reseau *r, float *n_b, float *n_w, int batch_size, const float eta)
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

float* sigmoid_prime(Reseau *r, int rang, float *data)
{
	float *temp = malloc(r->size[rang]*sizeof(float));
	for(int i = 0; i < r->size[rang];++i)
	{
		*(temp+i) = *(data+i)*(1.0-*(data+i));
	}	
	return temp;
}

float* cost_derivative(Reseau *r, int rang, float *data, float result)
{
	float *temp = malloc(r->size[rang]*sizeof(float));
	for(int i = 0; i<r->size[rang]; ++i)
	{
		*(temp+i) = *(data+i) - result;
	}
	return temp;
}

float* calc_first_delta(Reseau *r, int rang, float *data, float result)
{
	float *temp = sigmoid_prime(r,rang,data);
	float *cost = cost_derivative(r,rang,data,result);
	temp = multiplie_array(temp,cost,1,r->size[rang],1);
	free(cost);
	return temp;
}

void calc_delta(Reseau *r, int rang, float *data, float *delta)
{
	float *temp = sigmoid_prime(r,rang,data);
	float *w;
	get_all_weight(r,r->size[rang+1],&w);
	float *cost = multiplie_array(transpose_array(w,r->size[rang+1],r->size[rang]),delta,r->size[rang],r->size[rang+1],1);
	for(int i = 0; i<r->size[rang]; ++i)
	{
		*(delta+i) = *(temp+i)**(cost+i);
	}
	free(temp);
	free(cost);
}

int evaluate(Reseau *r, const Teach* test_data, int length_tsd)
{
	int res = 0;
	for(int i = 0; i<length_tsd;++i)
	{
		float *t = feed_forward(r, (test_data + i)->data);
		res+= *t == (test_data+i)->result;
	}
	return res;
}

void back_propagation(Reseau *r, const Teach current_val, float **d_n_b, float **d_n_w)
{
	zeros(r, d_n_b, d_n_w);
	float *activation = current_val.data;
	float *activations = calloc(r->length_bias+r->size[0],sizeof(float));

	copy_array(activations,activation,r->size[0]);
	int pos_ba = r->size[0], pos_w = 0;
	int i = 1;
	for(; i<r->length_size;++i)
	{
		activation = sigmoid(r,i,z_calc(r,i,activation));
		copy_array(activations+pos_ba,activation,r->size[i]);
		pos_ba+=r->size[i];
		pos_w+=r->size[i]*r->size[i-1];
	}
	--i;
	pos_w-=r->size[i]*r->size[i-1];
	pos_ba-=r->size[i];	
	float *delta = calc_first_delta(r,i,activation,current_val.result);
	copy_array(*(d_n_b)+pos_ba,delta,r->size[i]);
	pos_ba-=r->size[i-1];
	free(activation);
	activation = activations+pos_ba;
	float *temp = multiplie_array(delta,activation,1,r->size[i],r->size[i-1]);
	copy_array(*(d_n_w)+pos_w,temp,r->size[i]*r->size[i-1]);
	free(temp);
	--i;
	for(;i>0;--i)
	{
		calc_delta(r,i,activation,delta);
		copy_array(*(d_n_b)+pos_ba,delta,r->size[i]);
		pos_w-=r->size[i]*r->size[i-1];
		pos_ba-=r->size[i-1];
		activation-=r->size[i-1];
		float *temp = multiplie_array(delta,activation,r->size[i],1,r->size[i-1]);
		copy_array(*(d_n_w)+pos_w,temp,r->size[i]*r->size[i-1]);
		free(temp);
	}
	free(delta);
	free(activations);
}

void teach_reseau(Reseau *r, const Teach *tr_data, int length_trd, const int m_b_size, const float eta)
{
	float *n_b = NULL, *n_w = NULL;
	zeros(r, &n_b, &n_w);
	for(int i = 0; i<length_trd;++i)
	{
		float *d_n_b = NULL, *d_n_w = NULL;
		back_propagation(r, *(tr_data + i), &d_n_b, &d_n_w);
		maj_nabla(r, n_b, n_w, d_n_b, d_n_w);
		if( ((i+1)%m_b_size == 0) || (i+1>=length_trd) )
		{
			int t_batch = m_b_size;
			
			if(i+1>=t_batch && length_trd%t_batch !=0)
			{
				int nb_b = floor((float)length_trd/(float)t_batch);
				t_batch = length_trd - nb_b * t_batch;			
			}
			maj_reseau(r, n_b, n_w, t_batch, eta);
			zeros(r, &n_b, &n_w);
		}		
	}
	free(n_b);
	free(n_w);
}

void sgd(Reseau *r, Teach *tr_data, int length_trd, int epoch, const int m_b_size, 
	float eta,const Teach* test_data, int length_tsd)
{
	for(int i = 0; i<epoch;++i)
	{
		shuffle(tr_data,length_trd);
		teach_reseau(r,tr_data, length_trd, m_b_size, eta);
		if(length_tsd)
		{
			int res = evaluate(r,test_data,length_tsd);
			for(int i = 0 ; i < r->length_bias;++i)
			{
				printf("b%d : %f\n",i,*(r->biases+i));
			}
			for(int i = 0 ; i < r->length_weight;++i)
			{
				printf("w%d : %f\n",i,*(r->weight+i));
			}
			printf("Epoch %d : %d/%d\n",i+1,res,length_tsd);
		}
		else
			printf("Epoch %d complete\n",i+1);
	}
}
