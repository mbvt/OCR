# include <stdio.h>
# include "reseau.h"
# include "sauvegarde.h"



void saving_file(Reseau *r)
{

	float *bp = r->biases;
	float length_b = (float) r->length_bias;
	
	float *bw = r->weight;
	float length_w = (float) r->length_weight;
	 
	FILE *fp = NULL;
	
	fp = fopen("biases_n_weights.txt", "a");
	
	if (fp)
	{
		save_biases(bp, length_b, fp);
		save_weights(bw, length_w, fp);
 
		fclose(fp);
		
	}
	else
	{
		printf("Impossible d'ouvrir le fichier .txt");
	}
	
}

void save_biases(float *bp, float length_b, FILE *fp)
{

	printf("\nEcriture des biais dans file\n");
	
	for(float i = 0; i < length_b; ++i)
	{
		printf(" biais : %f\n", *bp);
		fputs((char *)bp, fp);
		fputc(';', fp);
		++bp;
	}

}


void save_weights(float *bw, float length_w, FILE *fp)
{
	
	printf("\nEcriture des biais dans file\n");
	
	for(float i = 0; i < length_w; ++i)
	{
		printf(" weight : %f\n", *bw);
		fputs((char *)bw, fp);
		fputc(';', fp);
		++bw;
	}	
	
}

 
