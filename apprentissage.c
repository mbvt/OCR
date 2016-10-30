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

void copy_array(float *des, float *ori, int n)
{
	float *fin = ori+n;
	for(;ori<fin;++ori,++des)
	{
		*des = *ori;
	}
}

int evaluate(Reseau *r, const Teach* test_data, int length_tsd)
{
	int res = 0;
	for(int i = 0; i<length_tsd;++i)
	{
		float *t = feed_forward(r, (test_data + i)->data);
		int val = round(*t*100);
		int val2 = round((test_data+i)->result*100);
		res+= val == val2;
		printf("eval : %d , %d\n",val, val2);
	}
	return res;
}

float* compute_output_d(Reseau *r,int rang, float *data, float result)
{
	float *temp = calloc(r->size[rang],sizeof(float));
	for(int i = 0; i<r->size[rang];++i)
	{
		float ok = *(data+i);
		*(temp+i)=ok*(1-ok)*(ok-result);
	}
	return temp;
}

float* compute_hidden_d(Reseau *r, int rang, float *data, float *delta)
{
	float *temp = calloc(r->size[rang],sizeof(float));
	for(int i = 0; < r->size[rang+1]; ++i)
	{
		float *w;
		get_weight(r,rang+1,i,&w);
		int j = 0;
		for(;j<r->size[rang];++j)
		{
			
			*(temp+j)+= *(delta+i) + *(w+j); 
		}	
		--j;
		float oj = *(data+j);
		*(temp+j)*=oj*(1-oj);
	}
}

void update_bias(Reseau *r, int rang, const float eta, float *data)
{
	float *b;
	get_biases(r, rang, &b);
	for(int i = 0; i<r->size[rang];++i)
	{
		
		*(b+i)+=-1.0*eta**(data+i);
	}
}

void update_weight(Reseau *r, int rang, const float eta, float *data, float *hidden_output)
{
	float *w;
	for(int i = 0; i<r->size[rang]; ++i)
	{
		get_weight(r,rang,i,&w);
		for(int j = 0; j<r->size[rang-1]; ++j)
		{²
			*(w+j) += -1.0*eta**(data+i)**(hidden_output+j);
		}
	}
}

void back_propagation(Reseau *r, const Teach current_val, const float eta)
{
	float *d_n_b = calloc(r->length_bias+r->size[0],sizeof(float));
	

	float *data = current_val.data;

	copy_array(d_n_b,data,r->size[0]);
	int pos_b = r->size[0];
	int i = 1;
	for(; i<r->length_size;++i)
	{
		data = sigmoid(r,i,z_calc(r,i,data));
		copy_array(d_n_b+pos_b,data,r->size[i]);
		pos_b+=r->size[i];
	}
	--i;
	pos_b-=r->size[i];
	float *output_d = compute_output_d(r,i,data,current_val.result);
	update_bias(r, i, eta, output_d);
	--i;
	pos_b-=r->size[i];
	copy_array(data,d_n_b+pos_b,r->size[i]);
	update_weight(r, i+1, eta, output_d, data);
	--i;
	
	for(;i>0;--i)
	{
		pos_b-=r->size[i];
		copy_array(data,d_n_b+pos_b,r->size[i]);
		float *hidden_d = comput_hidden_d(r,i,data,outpud_d);
		update_bias(r, i, eta, output_d);
		update_weight(r, i+1, eta, output_d, data);
	}
}

void teach_reseau(Reseau *r, const Teach *tr_data, int length_trd, const float eta)
{
	for(int i = 0; i<length_trd;++i)
	{
		back_propagation(r, *(tr_data + i), eta);		
	}
}

void sgd(Reseau *r, Teach *tr_data, int length_trd, int epoch, 
	float eta, const Teach* test_data, int length_tsd)
{
	for(int i = 0; i<epoch;++i)
	{
		shuffle(tr_data,length_trd);
		teach_reseau(r,tr_data, length_trd, eta);	
		if(length_tsd)
		{
			int res = evaluate(r,test_data,length_tsd);
			/*int j = 0;
			for(; j < 1;++j)
			{
				printf("b%d : %f\n",j,*(r->biases+j));
				printf("w%d : %f\n",j,*(r->weight+j));
			}
		
			for(; j < 2;++j)
			{
				printf("w%d : %f\n",j,*(r->weight+j));
			}*/
			if(res>0)
			printf("Epoch %d : %d/%d\n",i+1,res,length_tsd);
		}
		else
			printf("Epoch %d complete\n",i+1);
	}
}
