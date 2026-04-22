#include <string.h>
#include "utils.h"

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

