# include <stdio.h>
# include "reseau.h"
# include "sauvegarde.h"



void saving_file(Reseau *r)
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
		fprintf(fp, "%d;%d;%d\n", length_s, r->length_bias, r->length_weight);
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

	printf("\nPrinting sizes :\n");
	
	int* end_s = bs + length_s;
	
	for(; bs < end_s; ++bs)
	{
		printf(" size : %d\n", *bs);
		fprintf(fp, "%d;", *bs);	
	}

}


void save_biases(float *bp, int length_b, FILE *fp)
{

	printf("\nPrinting biases :\n");
	
	float* end_b = bp + length_b;

	for(; bp < end_b; ++bp)
	{
		printf(" bias : %f\n", *bp);
		fprintf(fp, "%f;", *bp);	
	}

}


void save_weights(float *bw, int length_w, FILE *fp)
{
	
	printf("\nPrinting weights :\n");
	
	float* end_w = bw + length_w;
	
	for(; bw < end_w; ++bw)
	{
		printf(" weight : %f\n", *bw);
		fprintf(fp, "%f;", *bw);	
	
	}	
	
}

 
