# include "chargement.h"
# define MAXSIZE 1000


struct reseau* loading_file()
{
	struct reseau *r = malloc(sizeof(struct reseau));

	FILE *f = NULL;
	char chaine[MAXSIZE] = "";
	char *s = "\n";
	char *token;
	int cpt = 0;
	f = fopen("biases_n_weights.txt", "r");
	int cpt2 = 0;
	if(f != NULL)
	{
		while(fgets(chaine, MAXSIZE, f) != NULL)
		{
			token = strtok(chaine, s);

			while(token != NULL)
			{
	
				if (cpt == 0)
				{
					traitement_size_array(token, r);
				}
				else if (cpt == 1)
				{
					traitement_tab_size(token, r);
				}
				else if (cpt == 2)
				{
					traitement_tab_b(token, r);
				}
				else
				{
						*(r->weight + cpt2) = string_to_float(token) ;
						token = strtok(NULL, s);
						++cpt2;
				}
				++cpt;
			
				token = strtok(NULL, s);
			}
		}
		fclose(f);
	}
	else
	{
		printf("OOOOOhhhhh...");
	}

	return r;

}

void traitement_size_array(char* chaine, struct reseau *r)
{
	char* s = " ";
	char* token;
	int res;
	int cpt = 0;

		token = strtok(chaine, s);
		while(token != NULL)
		{
			res =  str_to_int(token);
			if(cpt == 0)
			{
				r->length_size = res;
				r->size = malloc(r->length_size
*(sizeof(int)));
			}
			else if(cpt == 1)
			{
				r->length_bias = res;
				r->biases =
malloc(r->length_bias*(sizeof(float)));
			}
			else if(cpt == 2)
			{
				r->length_weight = res;
				r->weight =
malloc(r->length_weight*(sizeof(float)));
			}

			++cpt;
			token = strtok(NULL, s);
		}
}

void traitement_tab_size(char* chaine, struct reseau *r)
{
	char* s = " ";
	char* token;
	int res;
	int cpt = 0;

	token = strtok(chaine, s);

	while(token != NULL)
	{
		res = str_to_int(token);
		*(r->size + cpt) = res;
		token = strtok(NULL, s);
		++cpt;
	}
}

void traitement_tab_b(char* chaine, struct reseau *r)
{
	char* s = " ";
	char* token;
	float res;
	int cpt = 0;

	token = strtok(chaine, s);

	while(token != NULL)
	{
		res = string_to_float(token);

		*(r->biases + cpt) = res;		
		token = strtok(NULL, s);
		++cpt;
	}

}

int str_to_int(char* token)
{
	int res = 0;
	int i = 0;
	while(token[i] != '\0')
	{
	 	res = res*10 + (token[i] - 48);
		++i;
	}

	return res;
}


float string_to_float(char* token)
{
	int sign = 1;
	int dec = 10;
	int i = 0;
	int a = 0;
	float res = 0;
	if(token[0] == '-')                                     
  {                                                       
		sign = -1;                                      
    i = 1;                                          
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
    	res = res*10 + (token[i] - 48);           
      dec *= 10;                              
    }
    ++i;
  }
	res = res / (dec/10);

	res *= sign;                                             
	return res;
}


