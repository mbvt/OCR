# include "chargement.h"
# define MAXSIZE 1000

void loading_file(/*Reseau *r*/)
{
	//struct Reseau *ldr = malloc(sizeof(struct Reseau));

	FILE *f = NULL;
	char chaine[MAXSIZE] = "";
	char *s = ";";
	int sign = 1;
	int dec = 10;
	int i = 0;
	int a = 0
	float res = 0;

	char *token;
	f = fopen("biases_n_weights.txt", "r");

	if(f != NULL)
	{
		while(fgets(chaine, MAXSIZE, f) != NULL)
		{
			token = strtok(chaine, s);
			
			



			if(token[0] == '-')
			{
				sign = -1;
			}
			while(token[i] != '\0')
			{
				if(!a)
				{
					if(token[i] == '.')
					{
						a = 1;
					}
					else
					{
						res = res*10 + (token[i] - 48);
					}
				}
				else
				{
					res += (token[i] - 48) / dec;
					dec *= 10;
				}
				++i
			}
			
			/*
			for(int i = 0; i < strlen(token); ++i)
			{
				if(token[i] == '.')
				{
					cpt = strlen(token) - i;
				}
				res +=  token[i] 
			}*/

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





