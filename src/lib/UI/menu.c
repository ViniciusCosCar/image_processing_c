#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../superIMG.h"
#include "UI.h"

// ──────────────────────────────────────────────────────────
// ─── M E N U
// ──────────────────────────────────────────────────────────
Operation menu()
{
        system("");

        int opt;
        while (1)
        {
                printf("\033[2;3J\033[H");
                printf("%s ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁ %s\n", WHITE, RST);
                printf("%s▕ Which operation would you like to perform? ▏%s\n", WHITE, RST);
                printf("%s▕────────────────────────────────────────────▏%s\n", WHITE, RST);
                printf("%s▕ 0 -> %sexit%s                                  ▏%s\n", WHITE, RED_FG, WHITE, RST);
                printf("%s▕ 1 -> %stransform%s                             ▏%s\n", WHITE, BLUE_FG, WHITE, RST);
                printf("%s▕ 2 -> %sconvert%s                               ▏%s\n", WHITE, PURPLE_FG, WHITE, RST);
                printf("%s▕ 3 -> %sview%s                                  ▏%s\n", WHITE, GREEN_FG, WHITE, RST);
                printf("%s▕▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▏%s\n", WHITE, RST);
                printf("%s                                              %s\n", WHITE, RST);
                printf(": ");

                scanf("%d", &opt);
                while (getchar() != '\n') // Clean buffer
                        ;

                if (opt == 0)
                        exit(0);

                if (opt != TRANSFORM && opt != CONVERT && opt != VIEW)
                {
                        fprintf(stderr, "menu: invalid option\n");
                        while (getchar() != '\n')
                                ;
                        continue;
                }

                return opt;
        };
}

// ──────────────────────────────────────────────────────────
// ─── M E N U   I M A G E   T R A N S F O R M A T I O N S
// ──────────────────────────────────────────────────────────
void menu_transform(const IMAGE img, char **argv)
{
        system("");

        while (1)
        {
                printf("\033[2;3J\033[H");
                printf("%s ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁ %s\n", WHITE, RST);
                printf("%s▕ Which file transformation would you like to perform? ▏%s\n", WHITE, RST);
                printf("%s▕──────────────────────────────────────────────────────▏%s\n", WHITE, RST);
                printf("%s▕ 0 -> %sback%s                                            ▏%s\n", WHITE, RED_FG, WHITE, RST);

                printf("%s▕ 1 -> %sresize%s                                          ▏%s\n", WHITE, BLUE_FG, WHITE,
                       RST);

                printf("%s▕ 2 -> %sinvert%s                                          ▏%s\n", WHITE, BLUE_FG, WHITE,
                       RST);

                printf("%s▕ 3 -> %sbinarize%s                                        ▏%s\n", WHITE, BLUE_FG, WHITE,
                       RST);

                printf("%s▕▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▏%s\n", WHITE, RST);
                printf("%s                                                        %s\n", WHITE, RST);
                printf(": ");

                int opt;
                scanf("%d", &opt);
                while (getchar() != '\n') // Clean buffer
                        ;

                //      ASK USER TO CHOOSE AN OPERATION AND PERFORM IT
                //      ──────────────────────────────────────────────
                switch (opt)
                {
                case 0: //      GO BACK
                        //      ───────
                        return;

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
                        printf("Axis: ");
                        scanf("%2[^\n]", axis);

                        // Invert and write new image
                        PGM_write(PGM_invert(img, axis), argv[2]);

                        break;

                case 3: //      BINARIZE PGM
                        //      ────────────
                ;
                        // Write bin file
                        PGM_write(PGM_binarize(img), argv[2]);

                        break;

                default: //     SORRY
                         //     ────
                        fprintf(stderr, "Invalid option or not implemented function yet\n");
                }
                while (getchar() != '\n')
                        ;
        }
}

// ──────────────────────────────────────────────────────────
// ─── M E N U   I M A G E   C O N V E R S I O N S
// ──────────────────────────────────────────────────────────
void menu_convert(const IMAGE img, char **argv)
{
        system("");

        while (1)
        {
                printf("\033[2;3J\033[H");
                printf("%s ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁ %s\n", WHITE, RST);
                printf("%s▕ Would you like to convert to which image format? ▏%s\n", WHITE, RST);
                printf("%s▕──────────────────────────────────────────────────▏%s\n", WHITE, RST);
                printf("%s▕ 0 -> %sback%s                                        ▏%s\n", WHITE, RED_FG, WHITE, RST);

                printf("%s▕ 1 -> %sPGM%s                                         ▏%s\n", WHITE,
                       (img.type == PGM_TY) ? (CROSSED) : (PURPLE_FG), WHITE, RST);

                printf("%s▕ 2 -> %sPlain PGM%s                                   ▏%s\n", WHITE,
                       (img.type == PLAIN_PGM_TY) ? (CROSSED) : (PURPLE_FG), WHITE, RST);

                printf("%s▕ 3 -> %sPPM%s                                         ▏%s\n", WHITE,
                       (img.type == PPM_TY) ? (CROSSED) : (PURPLE_FG), WHITE, RST);

                printf("%s▕ 4 -> %sPlain PPM%s                                   ▏%s\n", WHITE,
                       (img.type == PLAIN_PPM_TY) ? (CROSSED) : (PURPLE_FG), WHITE, RST);

                printf("%s▕ 5 -> %sASCII%s                                       ▏%s\n", WHITE,
                       (img.type == ASCII_TY) ? (CROSSED) : (PURPLE_FG), WHITE, RST);

                printf("%s▕▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▏%s\n", WHITE, RST);
                printf("%s                                                    %s\n", WHITE, RST);
                printf(": ");

                int opt;
                scanf("%d", &opt);
                while (getchar() != '\n') // Clean buffer
                        ;

                //      PERFORM CONVERSION
                //      ──────────────────
                switch (opt)
                {
                case 0: //      GO BACK
                        //      ───────
                        return;

                case 1: //      PGM
                        //      ───
                        if (img.type == PGM_TY)
                                continue;

                        fprintf(stderr, "menu_view: not implemented function yet\n");
                        // image_to_pgm();
                        break;

                case 2: //      PLAIN PGM
                        //      ─────────
                        if (img.type == PLAIN_PGM_TY)
                                continue;

                        fprintf(stderr, "menu_view: not implemented function yet\n");
                        // image_to_plain_pgm();
                        break;

                case 3: //      PPM
                        //      ───
                        if (img.type == PPM_TY)
                                continue;

                        fprintf(stderr, "menu_view: not implemented function yet\n");
                        // image_to_ppm();
                        break;

                case 4: //      PLAIN_PPM
                        //      ─────────
                        if (img.type == PLAIN_PPM_TY)
                                continue;

                        fprintf(stderr, "menu_view: not implemented function yet\n");
                        // image_to_plain_ppm();
                        break;

                case 5: //      ASCII
                        //      ─────
                        if (img.type == ASCII_TY)
                                continue;

                        ASCII_write(image_to_ascii(img), argv[2]);

                        break;

                default: //     SORRY
                         //     ────
                        fprintf(stderr, "Invalid option\n");
                }
                while (getchar() != '\n')
                        ;
        }
}
