#include <stdlib.h>
#include <stdio.h>
#include "filter.h"

Pixel Pixelz(BMPImage * image, int x, int y);

Pixel Pixelz(BMPImage * image, int x, int y){
	if(x < 0){
		x = 0;
	}else if(x >= image -> norm_height){
		x = image -> norm_height - 1;
	}
	if(y < 0){
		y = 0;
	}else if(y >= image -> header.width_px){
		y = image -> header.width_px -1;
	}
	
	return(image -> pixels[x][y]);
}
#ifndef BLUR_OFF
BMPImage * blur(BMPImage * image) {

//FILL IN
	BoxFilter filt;	
	int x;
	int y;
	filt.norm = 9;

	for(x = 0; x < 3; x++){
		for(y = 0; y < 3; y++){
			filt.filter[x][y] =1;
		}
	}

	return(apply(image, filt));
}
#endif

// EXTRA CREDIT START
BMPImage * apply(BMPImage * image, BoxFilter f) {

//FILL INi
	BMPImage * finim = malloc(sizeof(BMPImage));
	finim ->norm_height = image -> norm_height;
	finim -> header = image -> header;
	finim -> pixels = malloc(sizeof(Pixel*) * finim -> norm_height);

	Pixel p;
	Pixel right;
	Pixel left;
	Pixel up;
	Pixel down;
	Pixel upright;
	Pixel upleft;
	Pixel downright;
	Pixel downleft;
	
	int x;
	int y;

	for(x = 0; x < finim ->norm_height; x++){
		finim -> pixels[x] = malloc(sizeof(Pixel) * finim -> header.width_px);
		for(y = 0; y < finim -> header.width_px; y++){
			p = Pixelz(image,x,y);
			right = Pixelz(image, x, y+1);
			left = Pixelz(image, x, y-1);
			up = Pixelz(image, x-1, y);
			down = Pixelz(image, x+1, y);
			upright = Pixelz(image, x-1, y+1);
			upleft = Pixelz(image, x-1, y-1);
			downright = Pixelz(image, x+1, y+1);
			downleft = Pixelz(image, x+1, y-1);

			finim -> pixels[x][y].red = ((downleft.red * f.filter[2][0]) + (p.red * f.filter[1][1]) + (upright.red * f.filter[0][2]) + (left.red * f.filter[1][0]) + (up.red * f.filter[0][1]) + (upleft.red * f.filter[0][0]) + (right.red * f.filter[1][2]) + (downright.red * f.filter[2][2]) + (down.red * f.filter[2][1]))/f.norm;

			finim -> pixels[x][y].blue = ((downleft.blue * f.filter[2][0]) + (p.blue * f.filter[1][1]) + (upright.blue * f.filter[0][2]) + (left.blue * f.filter[1][0]) + (up.blue * f.filter[0][1]) + (upleft.blue * f.filter[0][0]) + (right.blue * f.filter[1][2]) + (downright.blue * f.filter[2][2]) + (down.blue * f.filter[2][1]))/f.norm;
			finim -> pixels[x][y].green = ((downleft.green * f.filter[2][0]) + (p.green * f.filter[1][1]) + (upright.green * f.filter[0][2]) + (left.green * f.filter[1][0]) + (up.green * f.filter[0][1]) + (upleft.green * f.filter[0][0]) + (right.green * f.filter[1][2]) + (downright.green * f.filter[2][2]) + (down.green * f.filter[2][1]))/f.norm;
			finim -> pixels[x][y].alpha = ((downleft.alpha * f.filter[2][0]) + (p.alpha * f.filter[1][1]) + (upright.alpha * f.filter[0][2]) + (left.alpha * f.filter[1][0]) + (up.alpha * f.filter[0][1]) + (upleft.alpha * f.filter[0][0]) + (right.alpha * f.filter[1][2]) + (downright.alpha * f.filter[2][2]) + (down.alpha * f.filter[2][1]))/f.norm;

		}
	}

	return finim;

}

BoxFilter * readFilter(FILE * infile) {
	
//FILL IN
	BoxFilter * filttype = malloc(sizeof(BoxFilter));
	int x;
	double f;
	for(x = 0; x < 3; x++){
		fscanf(infile, "%d %d %d", &(filttype->filter[x][0]), &(filttype->filter[x][1]), &(filttype -> filter[x][2]));
		fgetc(infile);
	}

	fscanf(infile, "%lf", &f);
	filttype -> norm = (float)f;

	return filttype;

}
// EXTRA CREDIT END
