// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>
# include <assert.h> 

# include "image.h"
# include "load_image.h"
# include "decoupage.h"
# include "reseau.h"
# include "apprentissage.h"
# include "sauvegarde.h"
# include "chargement.h"

//int main(int argc, char **argv)
int main(void)
{
	/*init_sdl();
	printf("Bienvenu sur le projet OCRoot\n");
	printf("Realise par la team M.A.T.\n");
	printf("Actuellement en API\n");
	printf("Vous allez a present voir le decoupage des blocs.\n");
	printf("Entrer un caractere.\n");
	char ch;
	scanf("%c", &ch);
	SDL_Surface *txt = load_image("lorem.bmp");
	Image *img = convert_image(txt);
	search_text(img);
	search_row(img);
	search_letter(img);
	display_image(txt);
	printf("Appuyer sur une touche...\n");
	edge_text(img,txt);
	display_image(txt);
	printf("Appuyer sur une touche...\n");
	edge_row(img,txt);
	display_image(txt);
	printf("Appuyer sur une touche...\n");
	edge_letter(img,txt);
	display_image(txt);
	printf("Appuyer sur une touche...\n");
		
	printf("Malheureusement l'apprentissage de la fonction xor n'est pas encore disponible.\n");*/
	
	Teach *te1 = malloc(sizeof(Teach));
	Teach *te2 = malloc(sizeof(Teach));
	Teach *te3 = malloc(sizeof(Teach));
	Teach *te4 = malloc(sizeof(Teach));
	float arr1[2] = {0,0};
	float arr2[2] = {0,1};
	float arr3[2] = {1,0};
	float arr4[2] = {1,1};
	te1->data = arr1;
	te2->data = arr2;
	te3->data = arr3;
	te4->data = arr4;
	float faux = 0;
	float vrai = 1;
	te1->result = faux;
	te2->result = vrai;
	te3->result = vrai;
	te4->result = faux;
	
	Teach tr_dt[4] ={*te1,*te2,*te3,*te4}; 

	int size[3] = {2,2,1};
	Reseau *r = construct(size,3);
		
	sgd(r,tr_dt,4,10000,2,3,tr_dt,4);


	saving_file(r);	
	loading_file();

	
	return 0;
}
