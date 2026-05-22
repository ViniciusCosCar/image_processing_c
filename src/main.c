#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcs/general.c"
#include "funcs/netpbm.c"

int main(int argc, char **argv)
{
        //      READ PGM FILE TO ARRAY
        //      ──────────────────────
        int width, height;
        unsigned char *img = readpgm(argv[1], &width, &height);

        int imgsize = width * height;

        //      ASK USER TO CHOOSE AN OPERATION
        //      ───────────────────────────────
        system("");
        printf("\033[2J\033[H"
               "__ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __\n"
               "Which operation would you like to perform?	|\n"
               "------------------------------------------	|\n"
               "| 0 -> exit				  	|\n"
               "| 1 -> resize 	 	(pgm -> pgm)	  	|\n"
               "| 2 -> invert		(pgm -> pgm) 	  	|\n"
               "| 3 -> binarize 	(pgm -> pgm)    	|\n"
               "| 4 -> ascii 	 	(pgm -> txt)	  	|\n"
               "|						|\n"
               "| BETA						|\n"
               "| 5 -> print colored	(pgm -> nothing) 	|\n"
               "|______________________________________________|\n"
               "| TODO						|\n"
               "| convert		(? -> ?)       	        |\n"
               "| c_resize 	 	(? -> ?)	   	|\n"
               "-----------------------------------------------\n"
               ": ");

        int op;
        scanf("%d", &op);

        //      PERFORM CHOESEN OPERATION
        //      ─────────────────────────
        switch (op)
        {
        case 0: //      EXIT PROGRAM
                //      ────────────
                break;

        case 1: //      RESIZE IMAGE
                //      ────────────

                printf("hello");

                char program[] = "python3 resize.py ";

                char *s = (char *)calloc(strlen(program) + strlen(argv[1]) + strlen(argv[2]) + 3, sizeof(char));

                strcpy(s, program);
                strcat(s, argv[1]);
                strcat(s, " ");
                strcat(s, argv[2]);

                // Resize pgm
                system(s);

                free(s);
                break;

        case 2: //      INVERT IMAGE
                //      ────────────
        ;
                char axis[] = "yx";
                while (getchar() != '\n')
                        ; // Clean buffer
                scanf("%2[^\n]", axis);

                // Actual inversion
                invert_img(img, width, height, axis);

                // Write new image
                writepgm(img, width, height, argv[2]);

                break;

        case 3: //      BINARIZE PGM
                //      ────────────

        ;
                int limiar;
                printf("Limiar: ");
                scanf("%d", &limiar);
                if (limiar < 0)
                {
                        fscanf(stderr, "invalid limiar value");
                        exit(0);
                }

                // Binarize image
                if (!img_bin(img, imgsize, limiar))
                        fprintf(stderr, "binarizepgm: error in applaying function\n");

                // Write bin file
                writepgm(img, width, height, argv[2]);

                break;

        case 4: //      ASCII ART OF PGM
                //      ────────────────

                // Transform pgm in ascii art
                if (!img_ascii(img, imgsize))
                        fprintf(stderr, "asciipgm: error in applaying function");

                if (1)
                {
                        printf("Do something");
                }

                // Write ascii file
                writeascii(img, width, height, argv[2]);

                printf("Would you like to also print it?\n"
                       "---------------------------\n"
                       "| 1 -> Yes		   |\n"
                       "| 2 -> No 		   |\n"
                       "--------------------------|\n"
                       ": ");
                scanf("%d", &op);

                // Print ascii art
                if (op == 1)
                        for (int i = 0; i < imgsize; printf("%c", img[i++]))
                                if (i % width == 0)
                                        printf("\n");
                printf("\n");

                break;

        case 5: //      ACII COLORED VERSION OF PGM
                //      ───────────────────────────
                printf("\033[2J\033[H");
                print_color(img, width, height);

                break;

        default: //     SORRY
                 //     ────
                fprintf(stderr, "Invalid option or not implemented function yet\n");
        }

        //      FREE ALLOCATED MEMORY
        //      ─────────────────────
        free(img);
}
