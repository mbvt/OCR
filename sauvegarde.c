# include <stdio.h>
# include "reseau.h"
# include "sauvegarde.h"



void saving_file(struct reseau *r)
{

	int *bs = r->size;
	int length_s = r->length_size;

	float *bp = r->biases;
	int length_b = r->length_bias;
	
	float *bw = r->weight;
	int length_w = r->length_weight;
	 
	FILE *fp = NULL;
	
	fp = fopen("biases_n_weights.txt", "w");
	
	if (fp)
	{
		fprintf(fp, "%d %d %d\n", length_s, r->length_bias, r->length_weight);
		save_size(bs, length_s, fp);	
		fprintf(fp, "\n");
		save_biases(bp, length_b, fp);
		fprintf(fp, "\n");
		save_weights(bw, length_w, fp);
 
		fclose(fp);
		
	}
	else
	{
		printf("Impossible d'ouvrir le fichier .txt");
	}
	
}

void save_size(int *bs, int length_s, FILE *fp)
{
	int* end_s = bs + length_s;
	for(; bs < end_s; ++bs)
		fprintf(fp, "%d ", *bs);	
}


void save_biases(float *bp, int length_b, FILE *fp)
{
	float* end_b = bp + length_b;
	for(; bp < end_b; ++bp)
		fprintf(fp, "%f ", *bp);	
}


void save_weights(float *bw, int length_w, FILE *fp)
{
	float* end_w = bw + length_w;
	for(; bw < end_w; ++bw)
		fprintf(fp, "%f\n", *bw);	
}

 
