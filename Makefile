## Simple SDL mini code
 
CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -g -Wall -Wextra -Werror -std=c99 
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= load_image.c image.c decoupage.c queue.c reseau.c apprentissage.c matrice.c  read.c ocroot.c 
OBJ= ${SRC:.c=.o}
 
all: ocroot
 
ocroot: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f ocroot
 
# END
