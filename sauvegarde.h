//sauvegarde.h list of functions about our biases and weights saving file

# ifndef _OCROOT_SAUVEGARDE_H_
# define _OCROOT_SAUVEGARDE_H_

# include <stdlib.h>
# include <stdio.h>

//function who open and save biases and weights in file
int saving_file(float *bp, float *bw, int length_b, int length_w);

//function who writes biases in file
void save_biases(float *bp, int length_b);

//function who writes weights in file
void save_weights(float *wp, int length_w)
