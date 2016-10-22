// image.h list functions about matrice treatement

# ifndef _OCROOT_IMAGE_H_
# define _OCROOT_IMAGE_H_

//Stock letter's position in a row
typedef struct Lettre
{
	int j_min,j_max;
}Lettre;

//Stock row's position in text
typedef struct Ligne
{
	int i_min,i_max,nb_le;
	Lettre *le;
}Ligne;

//Stock coordonne of text in an image
typedef struct Text
{
	int i_min,i_max,j_min,j_max,nb_li;
	Ligne *li;
}Text;

//stock an image
typedef struct Image
{
	int w,h;
	unsigned char *dat;
	Text *te;
} Image;

//Initialize an empty matrice
Image* new_matrice(int w, int h);

//Set a pixel
void set_pixel(Image* img, int i, int j, unsigned char px);
//Set text coordonnee
void set_text(Image *img, int i_min, int i_max, int j_min, int j_max);
//Add a row in text
void add_Ligne(Text *te, int i_min, int i_max);
//Add a letter in a row
void add_Lettre(Ligne *li, int j_min, int j_max);

//Get a pixel
unsigned char get_pixel(Image* img, int i, int j);
//Get a row
Ligne* get_ligne(Text* te, int i);
//Get a letter
Lettre* get_lettre(Ligne *li, int i);

//Free an image
void del_image(Image* img);

# endif /* _OCROOT_IMAGE_H_ */
