#include <stdio.h>
#include <stdlib.h>

//
// print comments in pgm file
//
void readprintComment(FILE *fp){
	// '#' preceeds comments
	char dumchar;
	while(fscanf(fp,"#%c", &dumchar)) {
		// But what if we reach EOF before '\n'?
		// Maybe this instead,
		// while(fscanf(fp,"%c",&dumchar), dumchar!='\n' && dumchar!=EOF) printf("%c",dumchar);
		while(fscanf(fp,"%c", &dumchar), dumchar!='\n') printf("%c", dumchar);
		printf("\n");
	}
}

//
// Read pgm file given pgm stream
//
unsigned char *readpgm(char *filename,int *width,int *height)
{
	unsigned char *img;
	int i,j,imgsize,c;
	int typeno,maxvalue;
	FILE *fp;

	fprintf(stderr,"readpgm: opening %s\n",filename);

	fp=fopen(filename,"rb"); /* 2nd parameter must be equal to "rb" in Windows! */
	if(!fp) {
		fprintf(stderr,"readpgm: error opening file\n");
		exit(0);
	}

	// Print/ignore comments
	readprintComment(fp);

	// A raw pgm file is identified by the number P5, for a plain pgm,
	// the number is P2
	if(fscanf(fp,"P%d\n",&typeno)!=1) {
		fprintf(stderr,"readpgm: error reading typeno\n");
		exit(0);
	}
	fprintf(stderr,"readpgm: ppm type P%d\n",typeno);	
	readprintComment(fp);

	// Read width and height
	if(fscanf(fp,"%d %d\n",width,height)!=2) {
		fprintf(stderr,"readpgm: error reading width,height\n");
		exit(0);
	}
	fprintf(stderr,"readpgm: w %d  h %d\n",*width,*height);
	readprintComment(fp);


	// Read maxvalue
	if(fscanf(fp,"%d",&maxvalue)!=1) {
		fprintf(stderr,"readpgm: error reading maxvalue\n");
		exit(0);
	}
	fprintf(stderr,"maxvalue %d\n",maxvalue);
	readprintComment(fp);

	/* fix 14.10.97: read newline separately to avoid skipping bytes of
   image data corresponding to form-feeds
*/
	fgetc(fp);

	imgsize=(*width)*(*height);

	switch(typeno) {

		case 2:		/*  plainbits pgm type */

			fprintf(stderr, "readppm: sorry plain ppm not implemented\n");
			exit(0);

		case 5:        	/*  rawbits pgm type */

			img=(unsigned char *)calloc(imgsize,sizeof(unsigned char));
			if(!img) {
				fprintf(stderr,"readppm: calloc error 3\n");
				exit(0);
			}
			if(fread(img,sizeof(unsigned char),imgsize,fp)!=imgsize) {
				fprintf(stderr,"readppm: error reading image\n");
				exit(0);
			}

			break;
		default:
			fprintf(stderr,"readppm: sorry ppm type not implemented\n");
			exit(0);
	}

	fclose(fp);

	return img;
}

//
// Write pgm file give pgm stream
//	
void writepgm(unsigned char *img, int width, int height, char *fname)
{
	int imgsize;
	FILE *fp;

	if(!(fp=fopen(fname,"wb"))) { /* 2nd parameter must be equal to "rb" in Windows! */
		fprintf(stderr,"writepgm: error opening output file\n");
		exit(0);
	}

	fprintf(fp,"P5\n");
	fprintf(fp,"%d %d\n",width,height);
	fprintf(fp,"%d\n",255);

	imgsize=width*height;

	if(!fwrite(img,sizeof(unsigned char),imgsize,fp)) {
		fprintf(stderr,"writepgm: write error\n");
		exit(0);
	}

	fclose(fp);
	fprintf(stderr,"%s successfully created\n",fname);
}

//
// Write text file given stream of unsigned char
//
void writeascii(unsigned char *img, int width, int height, char *fname){
	FILE *fp;
	if(!(fp = fopen(fname,"w"))){
		fprintf(stderr,"writeascii: error creating txt file\n");
		exit(0);
	}

	int imgsize = width*height;
	for(int i=0; i<imgsize; fprintf(fp,"%c",img[i++])){
		if(i%width==0){
			fprintf(fp,"\n");
		}
	} 

	fclose(fp);

	fprintf(stderr,"%s successfully created\n",fname);
}

