# include <stdio.h>
# include "reseau.h"
# include "sauvegarde.h"



void saving_file(Reseau r)
{

	float *bp = r->biases;
	int length_b = r->length_bias;
	
	float *bw = r->weight;
	int length_w = r->length_weight;
	 
	FILE *fp = NULL;
	
	fp = fopen("biases_n_weights.txt", "a");
	
	if (fichier != NULL)
	{
		save_biases(*bp, length_b);
		save_weights(*bw, length_w);
 
		fclose(fp);
		
		//return 1;
	}
	else
	{
		printf("Impossible d'ouvrir le fichier .txt");
	}
	
//	return 0;
}

void save_biases(float *bp, int length_b)
{
	float *length_b = *bp + length_b;

	for(; bp < length_b; bp++)
	{
		fputs(*bp, fp);
		fputc(';', fp);
	}

}


void save_weights(float *bw, int length_w)
{
	float *length_w = *bw + length_w;

	for(; bw < length_w; bw++)
	{
		fputs(*bw, fp);
		fputc(';', fp);
	}	
	
}

 
