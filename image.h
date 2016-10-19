// image.h list functions about matrice treatement

# ifndef _OCROOT_IMAGE_H_
# define _OCROOT_IMAGE_H_

//list type of matrice
typedef enum Categorie
{
	IMAGE,COLONNE,LIGNE,MOT,LETTRE
} Categorie;

//stock an image
typedef struct Image
{
	int w,h;
	unsigned char *dat;
	Categorie cat;	
} Image;

//Initialize an empty matrice
Image* new_matrice(int w, int h, Categorie cat);
//Setteur for a pixel
void set_pixel(Image* img, int i, int j, unsigned char px);
//Getteur for a pixel
unsigned char get_pixel(Image* img, int i, int j);
//Function who free an image
void del_image(Image* img);

# endif /* _OCROOT_IMAGE_H_ */
