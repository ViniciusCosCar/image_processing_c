#include <string.h>
#include <stdio.h>
#include "utils.h"

int img_ascii(unsigned char *img, int imgsize){
	if(imgsize<0) return 0;

	// https://paulbourke.net/dataformats/asciiart/
	// char illumination[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/()1{}[]?-_+~<>i!lI;:,`'. ";
	char illumination[] = "@%#*+=-:. ";
	int scale_div = sizeof(illumination)/sizeof(char);

	for(int i=0; i<imgsize; i++){
		img[i]=illumination[(int) (img[i]*(scale_div-1))/255];
	}

	return 1;
}

int print_color(unsigned char *img,int w,int h){
	if(img==NULL || w<0 || h<0) return 0;

	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++)
			printf("\033[4%dm ",7*img[i*w+j]/255);
		printf("\n");
	}
	printf("\033[m\n");

	return 1;
}

int img_bin(unsigned char *img, int imgsize, unsigned char limiar){
	if(imgsize<0) return 0;

	for(int i=0; i<imgsize; i++)
		if(img[i]<limiar) img[i]=0;

	return 1;
}

int invert_img(unsigned char *img,int w,int h,char* axis){
	int imgsize = w*h;
	if(!img || imgsize <= 0 || !axis) return 0;

	// Invert along yx
	if(strcmp(axis,"yx")==0||strcmp(axis,"xy")==0) 
		invert_array(img,imgsize);
	// Invert along x
	else if(strcmp(axis,"x")==0)
		for(int j=0; j<w; j++){
			for(int i=0,k=h-1; i<k; i++,k--)
				invert(&img[j+i*w],&img[j+k*w]);
		}
	// Invert along y
	else if(strcmp(axis,"y")==0)	
		for(int i=0; i<h; i++) invert_array(img+i*w,w);

	return 1;
}
