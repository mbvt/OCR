# include "apprentissage.h"

void shuffle(struct teach *t, int length)
{
	srand(time(NULL));
	for(int i = length-1; i>0; --i)
	{
		int j = rand() %(i+1);
		struct teach p = *(t+i);
		*(t+i) = *(t+j);
		*(t+j) = p; 
	}
}

void zeros(const struct reseau *r, float **n_b, float **n_w)
{
	*n_b = calloc(r->length_bias,sizeof(float));
	*n_w = calloc(r->length_weight,sizeof(float));
}

void put_nabla_w(const struct reseau *r, int rang, float *n_w, float *ori)
{
	copy_array(n_w+get_pos_weight(r,rang),ori,r->size[rang]*r->size[rang-1]);
}

void put_nabla_b(const struct reseau *r, int rang, float *n_b, float *ori)
{
	copy_array(n_b+get_pos_biases(r,rang),ori,r->size[rang]);
}


void put_activations(const struct reseau *r, int rang, float *activations, float *ori)
{
	int pos = 0;
	if(rang>0)
		pos= get_pos_biases(r,rang) + r->size[0];
	copy_array(activations+pos,ori,r->size[rang]);
}

void get_nabla_w(const struct reseau *r, int rang, float *n_w, float **des)
{
	*des = n_w + get_pos_weight(r,rang);
}

void get_nabla_b(const struct reseau *r, int rang, float *n_b, float **des)
{
	*des = n_b + get_pos_biases(r,rang);
}


void get_activations(const struct reseau *r, int rang, float *activations, float **des)
{
	int pos = 0;
	if(rang>0)
		pos= get_pos_biases(r,rang) + r->size[0];
	*des = activations + pos;
}

void maj_nabla(const struct reseau *r, float *n_b, float *n_w, float *d_n_b, float *d_n_w)
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

void maj_reseau(struct reseau *r, float *n_b, float *n_w, int batch_size, const float eta)
{
	int i = 0;
	float tx = eta/(float)batch_size;
	for(;i<r->length_bias;++i)
	{
		*(r->biases+i) -= tx**(n_b+i);
		*(r->weight+i) -= tx**(n_w+i);
	}
	for(;i<r->length_weight;++i)
		*(r->weight+i) -= tx**(n_w+i);
	
	free(n_b);
	free(n_w);
}

float* sigmoid_prime(struct reseau *r, int rang, float *data)
{
	float *temp = malloc(r->size[rang]*sizeof(float));
	for(int i = 0; i < r->size[rang];++i)
	{
		*(temp+i) = *(data+i)*(1.0-*(data+i));
	}	
	return temp;
}

float* cost_derivative(struct reseau *r, int rang, float *data, float result)
{
	float *temp = malloc(r->size[rang]*sizeof(float));
	for(int i = 0; i<r->size[rang]; ++i)
	{
		*(temp+i) = *(data+i) - result;
	}
	return temp;
}

float* calc_first_delta(struct reseau *r, int rang, float *data, float result)
{
	float *temp = sigmoid_prime(r,rang,data);
	float *cost = cost_derivative(r,rang,data,result);
	float *res = multiplie_array(temp,cost,1,r->size[rang],1);
	free(cost);
	free(temp);
	return res;
}

void calc_delta(struct reseau *r, int rang, float *data, float **delta)
{
	float *temp = sigmoid_prime(r,rang,data);
	float *w;
	get_weight(r,r->size[rang+1],&w);
  float *trans = transpose_array(w,r->size[rang+1], r->size[rang]);
	float *cost = multiplie_array(trans, *delta,r->size[rang], r->size[rang+1], 1);
  free(*delta);
  *delta = malloc(r->size[rang]*sizeof(float));
  for(int i = 0; i<r->size[rang]; ++i)
	{
		*(*delta+i) = *(temp+i)**(cost+i);
	}
  free(trans);
	free(temp);
	free(cost);
}

int evaluate(struct reseau *r, const struct teach* test_data, int length_tsd)
{
	int res = 0;
	for(int i = 0; i<length_tsd;++i)
	{
		float *t = feed_forward(r, (test_data + i)->data);
		res+= *t == (test_data+i)->result;
	}
	return res;
}

void back_propagation(struct reseau *r, const struct teach current_val,
                      float **d_n_b, float **d_n_w)
{
	zeros(r, d_n_b, d_n_w);
	float *activation = current_val.data;
	float *activations = calloc(r->length_bias+r->size[0],sizeof(float));
	put_activations(r, 0, activations, activation);
	int i = 1;
	for(; i<r->length_size;++i)
	{
		float *t = sigmoid(r,i,z_calc(r,i,activation));
    if(i>1)
      free(activation);
    activation = t;
		put_activations(r, i, activations, activation);
	}
	--i;
	float *delta = calc_first_delta(r,i,activation,current_val.result);
	put_nabla_b(r, i, *d_n_b, delta);
	free(activation);
	get_activations(r, i-1, activations, &activation);
  float *trans = transpose_array(activation, r->size[i-1], r->size[i]);
	float *temp = multiplie_array( delta, trans, 1, r->size[i], r->size[i-1]);
	put_nabla_w(r, i, *d_n_w, temp);
	free(temp);
  free(trans);
	--i;
	for(;i>0;--i)
	{
		calc_delta(r,i,activation,&delta);
		put_nabla_b(r, i, *d_n_b, delta);
		get_activations(r, i-1, activations, &activation);
    trans = transpose_array(activation, r->size[i-1], 1);
		float *temp = multiplie_array(
                    delta, trans,
                    r->size[i], 1, r->size[i-1]);
		put_nabla_w(r, i, *d_n_w, temp);
    free(trans);
		free(temp);
	}
	free(delta);
	free(activations);
}

void teach_reseau(struct reseau *r, const struct teach *tr_data, int length_trd, 
                  const int m_b_size, const float eta)
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

void sgd(struct reseau *r, struct teach *tr_data, int length_trd, int epoch, 
         const int m_b_size, float eta, const struct teach* test_data, 
         int length_tsd)
{
	for(int i = 0; i<epoch;++i)
	{
		shuffle(tr_data,length_trd);
		teach_reseau(r,tr_data, length_trd, m_b_size, eta);
		if(length_tsd)
		{
			int res = evaluate(r,test_data,length_tsd);
			/*for(int i = 0 ; i < r->length_bias;++i)
			{
				printf("b%d : %f\n",i,*(r->biases+i));
			}
			for(int i = 0 ; i < r->length_weight;++i)
			{
				printf("w%d : %f\n",i,*(r->weight+i));
			}*/
			printf("Epoch %d : %d/%d\n",i+1,res,length_tsd);
		}
		else
			printf("Epoch %d complete\n",i+1);
	}
}
