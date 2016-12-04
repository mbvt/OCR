# include "apprentissage.h"

float 				*sigmoid_prime(float *z, int col)
{
	float *temp = malloc(col*sizeof(float));
	for (int i = 0; i < col; ++i)                                                 
	{
		*(temp + i) = expf(-*(z+i))/powf(1.0+expf(-*(z+i)),2);
	}
	return temp;
}
/*
int 			evaluate(struct reseau *r, const struct teach* test_data, 
									int length_tsd, float taux_erreur)
{
	int res = 0;
	for (int i = 0; i<length_tsd;++i)
	{
		float *t = feed_forward(r, (test_data + i)->data);
		printf("Resultat : %f = %f - %f\n",*t - (test_data+i)->result, *t,
		(test_data+i)->result);
		res 		+= fabs(*t - (test_data+i)->result) < taux_erreur;
	}
	return res;
}
*/
float 	back_propagation(struct reseau *r,
												float eta, float *data, float res)
{
	float *z2;
	float *z2p;
	float *a2;
	float *z3;
	float *z3p;
	float *yc;
	float *at;
	float *dj3;
	float *dj2;
	float	*wt;
	float *d2;
	float *xt;
	float *w1;
	float *w2;
	float *d3;
	float *b1;
	float *b2;
	float count = 0;
	get_weight(r,1,&w1);
	get_weight(r,2,&w2);
	get_biases(r,1,&b1);
	get_biases(r,2,&b2);
	
	z2 	= multiplie_array(data, w1, 1, r->size[0], r->size[1]);
	addition_scalaire(z2, b1, r->size[1]);
	a2 	= sigmoid(z2, r->size[1]);
	z3 	= multiplie_array(a2, w2, 1, r->size[1], r->size[2]);
	addition_scalaire(z3, b2, r->size[2]);
	yc 	= sigmoid(z3, r->size[2]);
	for (int i = 0; i < r->size[2]; ++i)
		*(yc + i) = res - *(yc + i);
	for (int i = 0; i < r->size[2]; ++i)
		count = *(yc + i);
	z3p	= sigmoid_prime(z3, r->size[2]);
	d3 	= multiplie_scalaire(yc, z3p, r->size[2]);
	at 	= transpose_array(a2, 1, r->size[1]);
	dj3 = multiplie_array(at, d3, r->size[1], 1, r->size[2]);
	wt 	= transpose_array(w2, r->size[1], r->size[2]);
	d2 	= multiplie_array(d3, wt, 1, r->size[2], r->size[1]);
	z2p = sigmoid_prime(z2, r->size[1]);
	d2 	= multiplie_scalaire(d2, z2p, r->size[1]);
	xt 	= transpose_array(data, 1, r->size[0]);
	dj2 = multiplie_array(xt, d2, r->size[0], 1, r->size[1]);
	
	for (int i = 0; i < r->size[0]*r->size[1]; ++i)
		*(w1 + i) += eta	*	*(dj2 + i);
	for (int i = 0; i < r->size[1]*r->size[2]; ++i)
		*(w2 + i) += eta	*	*(dj3 + i);
	for (int i = 0; i < r->size[1]; ++i)
		*(b1 + i) += eta	*	*(d2 + i);
	for (int i = 0; i < r->size[2]; ++i)
		*(b2 + i) += eta	*	*(d3 + i);

	free(z2);
	free(a2);
	free(z3);
	free(yc);
	free(z3p);
	free(at);
	free(dj3);
	free(d3);
	free(wt);
	free(d2);
	free(dj2);
	return count;
}

float* getMat(int i, int j)
{
	float* res = malloc(256*sizeof(float));
	char *p = "./learn_dat/Sample0";
	char *sample = calloc(2,sizeof(char));
	char *samplet = calloc(4,sizeof(char));
	char *pict = calloc(4,sizeof(char));
	char *pictt = calloc(8,sizeof(char));
	char *path = calloc(30,sizeof(float));
	if (i < 10)
		strcpy(sample,"0");
	sprintf(samplet,"%d",i);
	strcat(sample,samplet);
	if (j < 10)
		strcpy(pict,"000");
	else if (j < 100)
		strcpy(pict, "00");
	else if (j < 1000)
		strcpy(pict, "0");
	sprintf(pictt,"%i",j);
	strcat(pict, pictt);
	strcpy(path,p);
	strcat(path,sample);
	strcat(path,"/");
	strcat(path,pict);
	FILE* file = NULL;
	file = fopen(path, "r");
	if (!file)
	{
		return NULL;
	}
	int cpt = 0;
	char c;
	while ((c = getc(file)) != EOF)
	{
		if(c != '\n'){
			*(res + cpt) = (c == '1') ? 0 : 1;
			cpt++;
		}
	}
	res = transpose_array(res, 16, 16);
	fclose(file);
	return res;
}

void launch_apprentissage(struct reseau *r, float eta, float taux_erreur)
{
	do
	{
		float *tab;
		float res;
		for (int i = 0; i <1016; ++i)
		{
			for (int j = 1; j < 63; ++j)
			{
				tab = getMat(j,i);
				cpt += fabs(back_propagation(r, eta, tab, (float)j/63));
			}
		}
	}while (cpt > 6000);
	//evaluate(r,tab,len,taux_erreur);
}

