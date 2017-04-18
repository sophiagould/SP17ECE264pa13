#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#ifndef READIMAGE_OFF
BMPImage * readImage(FILE * fp) {
	BMPImage * image = malloc(sizeof(BMPImage));
	fread(&(image -> header), sizeof(BMPHeader), 1 ,fp);

	image->norm_height = abs(image -> header.height_px);

	image->pixels = malloc(image->norm_height * sizeof(Pixel*));
	int i;
	for (i = 0; i < image->norm_height; i++) {
		image->pixels[i] = malloc((image->header).width_px * sizeof(Pixel));
	}

	int k;
	int j;
	for (k = 0; k < image->norm_height; k++) {
		for (j = 0; j < (((image)->header).width_px); j++) {
			fread((&(image)->pixels[k][j]), sizeof(Pixel), 1, fp);
		}
	}

//	FILE * output1;
//	fwrite((&((*image).header).num_colors), 1,1, output1);
	return(image);
}

void freeImage(BMPImage * image) {
//	free((image)->header);
//	free((image)->pixels);
	int x;
	for(x = 0; x < image -> norm_height; x++){
		free(image -> pixels[x]);
	}
	free(image-> pixels);
	free(image);
	
// FILL IN

}
#endif

#ifndef WRITEIMAGE_OFF
void writeImage(BMPImage * image, FILE * fp) {
	int k;
	int j;
	fwrite(&(image)->header, sizeof(BMPHeader), 1, fp);

	for (k = 0; k < image->norm_height; k++) {
		for (j = 0; j < (((image)->header).width_px); j++) {
			fwrite((&(image)->pixels[k][j]), sizeof(Pixel), 1, fp);
		}
	}
	freeImage(image);
// FILL IN

}
#endif
