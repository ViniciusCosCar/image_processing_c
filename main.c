#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "functions/functions.h"
#include "functions/file_operations.h"

int main(int argc, char **argv){

	int width, height;

	// Read pgm file
	unsigned char * img=readpgm(argv[1],&width,&height);

	int imgsize=width*height;

	printf("\n"
	"__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __\n"
	"Which operation would you like to perform?	|\n"
	"------------------------------------------	|\n"
	"| 1 -> resize 	 	(pgm -> pgm)	  	|\n"
	"| 2 -> invert		(pgm -> pgm) 	  	|\n"
	"| 3 -> binarize 	(pgm -> pgm)    	|\n"
	"| 4 -> ascii 	 	(pgm -> txt)	  	|\n"
	"| 5 -> exit				  	|\n"
	"|______________________________________________|\n"
	"| Features to be implemented			|\n"
	"| scale 	 	(pgm -> pgm)	   	|\n"
	"| convert		(? -> ?)       	        |\n"
	"-----------------------------------------------\n"
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

		case 2: // Invert image

			;char axis[] = "yx";
			printf("Along which axis? (x, y or yx)\n: ");

			while(getchar()!='\n'); // Clean buffer
			scanf("%2[^\n]", axis);
			
			// Actual inversion
			invert_img(img,width,height,axis);
		
			// Write new image
			writepgm(img,width,height,argv[2]);

			break;


		case 3: // Binarize pgm

			;int limiar;
			printf("Limiar: ");	
			scanf("%d", &limiar);
			if(limiar<0){
				fscanf(stderr, "invalid limiar value");
				exit(0);
			}

			// Binarize image
			if(!img_bin(img, imgsize, limiar))
				fprintf(stderr, "binarizepgm: error in applaying function\n");

			// Write bin file
			writepgm(img,width,height,argv[2]);

			break;

		case 4: // Ascii art of pgm

			// Transform pgm in ascii art
			if(!img_ascii(img, imgsize))
				fprintf(stderr, "asciipgm: error in applaying function");

			// Write ascii file
			writeascii(img,width,height,argv[2]);

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
				for(int i=0; i<imgsize; printf("%c",img[i++]))
					if(i%width==0) printf("\n");
			printf("\n");

			break;

		case 5: // Exit program
			break;

		default:
			fprintf(stderr, "Invalid option\n");

		free(img);
	}
}
