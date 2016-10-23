## Simple SDL mini code
 
CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= load_image.c image.c liste_matrice.c decoupage.c ocroot.c
OBJ= ${SRC:.c=.o}
 
all: ocroot
 
ocroot: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f ocroot
 
# END
