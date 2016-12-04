# include "chargement.h"

void loading_file(Reseau *r)
{
	struct Reseau *ldr = malloc(sizeof(struct Reseau));
	FILE *fp;
	
	float fl;

	if((fp = fopen("biases_n_weights.txt", "r")) == NULL)
	{
		printf("Oooooohhh.. :,(");
	}
	else
	{
		
	}
	
	while()
	{	
		int ret = fscanf(fp, "%[^;] %f", fl);
		if(ret >= 1)
		{
			printf("\n%f\n",fl);
		}
	}
}


