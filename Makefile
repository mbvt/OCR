## Simple SDL mini code
 
CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g3
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= load_image.c image.c decoupage.c reseau.c apprentissage.c ocroot.c matrice.c sauvegarde.c chargement.c
OBJ= ${SRC:.c=.o}
 
all: ocroot
 
ocroot: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f ocroot
 
# END
