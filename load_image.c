# include "load_image.h"

void init_sdl(void)
{
	if(SDL_Init(SDL_INIT_VIDEO)==-1)
	{
		errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
	}
}

SDL_Surface* load_image(char *path)
{
	SDL_Surface *img;
	img =IMG_Load(path);
	if(!img)
		errx(3,"can't load %s: %s", path, IMG_GetError());
	return img;
}

static inline 
Uint8* pixelref(SDL_Surface *surface, unsigned x, unsigned y)
{
	int bpp = surface->format->BytesPerPixel;
	return (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
	Uint8 *p = pixelref(surface, x, y);
	switch(surface->format->BytesPerPixel) 
	{
		case 1:
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return	p[0] | p[1] << 8 | p[2] << 16;
		case 4:
			return *(Uint32 *)p;
	}
	return 0;
}

Image* convert_image(char *path)
{
	init_sdl();
	SDL_Surface* img = load_image(path);
	Image* new_img = new_matrice(img->w, img->h, IMAGE);
	unsigned char min = 255, max = 0;

	for(int i = 0; i < img->h; i++)
	{
		for(int j = 0 ; j < img->w; j++)
		{
			Uint32 p = getpixel(img, j, i);
			Uint8 r, g, b;
			SDL_GetRGB(p, img->format, &r, &g, &b);
			Uint32 gr=(0.2126*r+0.7152*g+0.0722*b);
			min = (gr<min)?gr:min;
			max = (gr>max)?gr:max;
			set_pixel(new_img,i,j,(gr>128)?1:0);
		}
	}
	printf("%d , %d", min, max);
	return new_img;
}
