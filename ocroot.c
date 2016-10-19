// ocroot.c contains main function

# include <stdio.h>
# include <stdlib.h>

# include "image.h"
# include "load_image.h"

int main()
{
	Image *img = convert_image("cLena.bmp");
	FILE *f = fopen("file.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	for(int i = 0; i < img->h; i++)
	{
		for(int j = 0; j < img->w; j++)
		{
			fputs(get_pixel(img,i,j)?"1":"0",f);
		}
		fputs("\n",f);
	}
	fclose(f);
	
	return 0;
};
