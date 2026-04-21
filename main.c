#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions/functions.h"

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
	unsigned char *data;
	int i,j,datasize,c;
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

	datasize=(*width)*(*height);

	switch(typeno) {

		case 2:		/*  plainbits pgm type */

			fprintf(stderr, "readppm: sorry plain ppm not implemented\n");
			exit(0);

		case 5:        	/*  rawbits pgm type */

			data=(unsigned char *)calloc(datasize,sizeof(unsigned char));
			if(!data) {
				fprintf(stderr,"readppm: calloc error 3\n");
				exit(0);
			}
			if(fread(data,sizeof(unsigned char),datasize,fp)!=datasize) {
				fprintf(stderr,"readppm: error reading data\n");
				exit(0);
			}

			break;
		default:
			fprintf(stderr,"readppm: sorry ppm type not implemented\n");
			exit(0);
	}

	fclose(fp);

	return data;
}

//
// Write pgm file give pgm stream
//	
void writepgm(unsigned char *data, int width, int height, char *fname)
{
	int datasize;
	FILE *fp;

	if(!(fp=fopen(fname,"wb"))) { /* 2nd parameter must be equal to "rb" in Windows! */
		fprintf(stderr,"writepgm: error opening output file\n");
		exit(0);
	}

	fprintf(fp,"P5\n");
	fprintf(fp,"%d %d\n",width,height);
	fprintf(fp,"%d\n",255);

	datasize=width*height;

	if(!fwrite(data,sizeof(unsigned char),datasize,fp)) {
		fprintf(stderr,"writepgm: write error\n");
		exit(0);
	}

	fclose(fp);
	fprintf(stderr,"%s successfully created\n",fname);
}

//
// Write text file given stream of unsigned char
//
void writeascii(unsigned char *data, int width, int height, char *fname){
	FILE *fp;
	if(!(fp = fopen(fname,"w"))){
		fprintf(stderr,"writeascii: error creating txt file\n");
		exit(0);
	}

	int datasize = width*height;
	for(int i=0; i<datasize; fprintf(fp,"%c",data[i++])){
		if(i%width==0){
			fprintf(fp,"\n");
		}
	} 

	fclose(fp);

	fprintf(stderr,"%s successfully created\n",fname);
}

int main(int argc, char **argv){

	int width, height;

	// Read pgm file
	unsigned char * data=readpgm(argv[1],&width,&height);

	int datasize=width*height;

	printf(
	"__ __ __ __ __ __ __ __ __ __ __ __ __ __ \n"
	"Which operation would you like to perform?\n"
	"------------------------------------------\n"
	"| 1 -> resize 	 (out -> *.pgm) 	  |\n"
	"| 2 -> binarize (out -> *.pgm)		  |\n"
	"| 3 -> ascii 	 (out -> *.txt)		  |\n"
	"| 4 -> exit				  |\n"
	"------------------------------------------\n"
	": "
	);

	int op;
	scanf("%d", &op);

	switch(op){
		case 1: // Execute python command to resize pgm

			; // Label followed by a declaration is a C23 extension
			char program[] = "python3 resize.py ";
			char *s = (char*)calloc(strlen(program)+strlen(argv[1])+strlen(argv[2])+3, sizeof(char));

			strcpy(s,program);
			strcat(s, argv[1]);
			strcat(s, " ");
			strcat(s, argv[2]);

			// Resize pgm
			system(s);

			free(s);
			break;

		case 2: // Binarize pgm

			;
			int limiar;
			printf("Limiar: ");	
			scanf("%d", &limiar);
			if(limiar<0){
				fscanf(stderr, "invalid limiar value");
				exit(0);
			}

			// Binarize image
			if(!img_bin(data, datasize, limiar))
				fprintf(stderr, "binarizepgm: error in applaying function\n");

			// Write bin file
			writepgm(data,width,height,argv[2]);
			
			break;

		case 3: // Ascii art of pgm

			// Transform pgm in ascii art
			if(!img_ascii(data, datasize))
				fprintf(stderr, "asciipgm: error in applaying function");

			// Write ascii file
			writeascii(data,width,height,argv[2]);

			printf(
				"Would you like to also print it?\n"
				"---------------------------\n"
				"| 1 -> Yes		   |\n"
				"| 2 -> No 		   |\n"
				"--------------------------|\n"
				": "
			);
			scanf("%d", &op);

			// Print ascii art
			if(op==1)
				for(int i=0; i<datasize; printf("%c",data[i++]))
					if(i%width==0) printf("\n");
			printf("\n");

			break;

		case 4: // Exit program
			exit(0);

		default:
			fprintf(stderr, "Invalid option\n");
			exit(0);
	}
}
