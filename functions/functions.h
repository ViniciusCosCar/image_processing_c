#ifndef FUNCTIONS
#define FUNCTIONS

// raw_pgm -> plain_pgm
int raw2plainPGM(unsigned char *raw_pgm,int imgsize);
// pgm -> ascii represantation
int img_ascii(unsigned char *img,int imgsize);
// pgm -> binarized version by given limiar
int img_bin(unsigned char *img,int imgsize,unsigned char limiar);
// Invert image according to specified axis
int invert_img(unsigned char *img,int w,int h,char* axis);
int print_color(unsigned char *,int,int);


#endif
