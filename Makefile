
CC=gcc

CPPFLAGS=  `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl`  -export-dynamic
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=

LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl`  -lSDL_image -export-dynamic -lm

SRC= chargement.c sauvegarde.c apprentissage.c reseau.c queue.c matrice.c read.c load_image.c image.c decoupage.c IHM.c decoupage.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: IHM

-include ${DEP}

IHM: ${OBJ}

clean:
	rm -f *~ ${OBJ} ${DEP} IHM

# END Makefile
