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

void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}

struct image* convert_image(char* path)                                                
{                                                                               
  init_sdl();                                                                   
	SDL_Surface *img = load_image(path);                                          
	struct image* new_img = new_matrix(img->w, img->h);                                  
	                                                                             
	for(int i = 0; i < img->h; i++)                                               
	{                                                                             
		for(int j = 0 ; j < img->w; j++)                                            
		{                                                                           
			Uint32 p = getpixel(img, j, i);                                           
			Uint8 r, g, b;                                                            
			SDL_GetRGB(p, img->format, &r, &g, &b);                                   
			Uint32 gr=(0.2126*r+0.7152*g+0.0722*b);                                   
			set_pixel(new_img,i,j,(gr<128)?1:0);                                      
		}                                                                           
	}                                                                             
	return new_img;                                                               
}     
									
void  conversion(struct image *img, SDL_Surface* conver)                               
{                                                                               

	for(int i = 0; i < img->h; i++)                                               
	{                                                                             
	 	for(int j = 0; j < img->w; j++)                                             
	 	{                                                                           
		  int k;                                                                    
		  if(get_pixel(img, i, j) ==  0)                                            
		  {                                                                       
		  	k = 255;                                                              
		  }                                                                       
		  else 
		  { 
		  	k = 0; 
		  } 
			putpixel(conver, j,i, SDL_MapRGB(conver->format, k,k,k));
		} 
	} 
	SDL_SaveBMP(conver, "img.bmp"); 
}                                                                             


void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}

void draw_square(SDL_Surface *surf, int i_min, int i_max, int j_min, int j_max, Uint32 p)
{
	for(int i = i_min; i<=i_max;++i)
  {
  	putpixel(surf,j_min,i,p);
    putpixel(surf,j_max,i,p);
  }
  for(int i = j_min; i<=j_max;++i)
  {
  	putpixel(surf,i,i_min,p);
    putpixel(surf,i,i_max,p);
  }
}


void 							edge_text(struct image *image, SDL_Surface *surf)
{
	int i_min = surf->w, i_max = 0, j_min = surf->h, j_max = 0;
	new_letter(image, 0, 0, 0, 0);
	struct letter *letter = get_letter(image);
	while (letter->i_min || letter->j_min || letter->i_max || letter->j_max)
	{
		if (letter->i_min < i_min)
			i_min = letter->i_min;
		if (letter->i_max > i_max)
			i_max = letter->i_max;
		if (letter->j_min < j_min)
			j_min = letter->j_min;
		if (letter->j_max < j_max)
			j_max = letter->j_max;
		new_letter(image, letter->i_min, letter->i_max, letter->j_min,
							letter->j_max);
		letter = get_letter(image);
	}
	Uint32 p 				= SDL_MapRGB(surf->format,255, 0, 0);
	draw_square(surf, i_min, i_max, j_min, j_max,p);
}

void edge_row(struct image *img, SDL_Surface *surf)
{	
	Uint32 p 				= SDL_MapRGB(surf->format,0, 255, 0);
	new_letter(img, 0, 0, 0, 0);
	struct letter *letter = get_letter(img);
	int i_min = letter->i_min, i_max = letter->i_max, 
			j_min = letter->j_min, j_max = letter->j_max;
	while (letter->i_min || letter->j_min || letter->i_max || letter->j_max)
	{
		if (letter->i_min < i_min)
			i_min = letter->i_min;
		else if(letter->i_min > i_max)
		{
			draw_square(surf, i_min, i_max, j_min, j_max,p);
			i_min = letter->i_min;
		}
		if (letter->i_max > i_max)
			i_max = letter->i_max;
		if (letter->j_min < j_min)
			j_min = letter->j_min;
		if (letter->j_max < j_max)
			j_max = letter->j_max;
		new_letter(img, letter->i_min, letter->i_max, letter->j_min,
							letter->j_max);
		letter = get_letter(img);
	}
}

void 				edge_letter(struct image *img, SDL_Surface *surf)
{
	struct letter *letter = get_letter(img);
	new_letter(img, 0, 0, 0, 0);
	while (letter->i_min || letter->j_min || letter->i_max || letter->j_max)
  {
    Uint32 p = SDL_MapRGB(surf->format,0,0,255); 
    draw_square(surf, letter->i_min, letter->i_max, letter->j_min, letter->j_max, p);
		new_letter(img, letter->i_min, letter->i_max, letter->j_min,
							letter->j_max);
		letter = get_letter(img);
  }
	SDL_SaveBMP(surf, "imgCut.bmp");
}
