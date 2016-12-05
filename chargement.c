# include "chargement.h"
# define MAXSIZE 1000

void loading_file(Reseau *r)
{
	struct Reseau *ldr = malloc(sizeof(struct Reseau));

	FILE *f = NULL;
	char chaine[MAXSIZE] = "";
	char *s = ";";
	//char *nn = "\n";
	char *token;
	f = fopen("biases_n_weights.txt", "r");

	if(f != NULL)
	{
		while(fgets(chaine, MAXSIZE, f) != NULL)
		{
			token = strtok(chaine, s);
			while(token != NULL)
			{
				printf("%s", token);
				token = strtok(NULL, s);
			}
		}
		fclose(f);
	}
	else
	{
		printf("OOOOOhhhhh...");
	}

}





