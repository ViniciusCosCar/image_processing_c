#ifndef FUNCTIONS
#define FUNCTIONS

// pmg -> ascii represantation
int img_ascii(unsigned char *data, int datasize);
// pmg -> binarized version by given limiar
int img_bin(unsigned char *data, int datasize, unsigned char limiar);
// Invert image according to specified axis
int invert_img(unsigned char *img,int w,int h,char* axis);


#endif
