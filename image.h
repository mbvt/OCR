// image.h list functions about matrice treatement

# ifndef _OCR_IMAGE_H_
# define _OCR_IMAGE_H_

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
//Function who get a sub matrice between horizontal and vertical coordonnee and set a categorie
Image* cut_image(Image* img, Categorie cat, int i_min, int i_max, int j_min, int j_max);
//Function who free an image
void del_image(Image* img);

# endif /* _OCR_IMAGE_H_ */
