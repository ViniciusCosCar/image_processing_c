#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Read pgm file and return pgm image
unsigned char *readpgm(char *filename,int *width,int *height);
// Write pgm file according to given pgm image
void writepgm(unsigned char *img, int width, int height, char *fname);
// Write txt file according to given ascii art image
void writeascii(unsigned char *img, int width, int height, char *fname);

#endif
