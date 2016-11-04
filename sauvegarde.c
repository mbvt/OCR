# include <stdio.h>
# include "reseau.h"
# include "sauvegarde.h"



int saving_file(float *bp, float *bw, int length_b, int length_w)
{
	FILE *fp = NULL;
	
	fp = fopen("bnw.txt", "a");
	
	if (fichier != NULL)
	{
		save_biases(*bp, length_b);
		save_weights(*bw, length_w);
 
		fclose(fp);
		
		return 1;
	}
	
	return 0;
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

 
