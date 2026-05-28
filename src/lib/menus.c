#include "superIMG.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define UP_BORDER "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n"
#define DOWN_BORDER "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n"

char *OPTS[] = {"░ exit                                  ░\n", "░ transform                             ░\n",
                "░ convert                               ░\n", "░ view                                  ░\n"};
const int N_OPTS = sizeof(OPTS) / sizeof(OPTS[0]);

void clear()
{
        printf("\033[2;3J\033[H");
}
// ──────────────────────────────────────────────────────────
// ─── O P E R A T I O N   S E L E C T I O N
// ──────────────────────────────────────────────────────────
void select_opt(char **opts, const int n_opts, const int selected)
{
        for (int i = 0; i < n_opts; i++)
                if (i == selected)
                        printf("\033[41m%s\033[m", opts[selected]);
                else
                        printf("%s", opts[i]);
}
// ──────────────────────────────────────────────────────────
// ─── M E N U
// ──────────────────────────────────────────────────────────
Operation menu(IMAGE img)
{
        system("");

        char key;
        unsigned int select = 0;
        do
        {
                clear();

                printf("Format: %s\n", types[img.type]);
                printf("Res: %dx%d\n", img.width, img.height);
                printf("Size: %sB\n", format_number(img.datasize));

                printf("%s", UP_BORDER);
                switch (key)
                {
                case 'j':
                        if (select == N_OPTS - 1)
                                select = 0;
                        else
                                select++;

                        break;
                case 'k':
                        if (select != 0)
                                select--;
                        else
                                select = N_OPTS - 1;

                        break;
                }

                select_opt(OPTS, N_OPTS, select);
                printf("%s", DOWN_BORDER);

        } while ((key = raw_getch(STDIN_FILENO)) != '\n');

        if (select == 0)
                exit(0);

        if (select != 1 && select != 2 && select != 3)
        {
                fprintf(stderr, "menu: invalid option\n");
                while (getchar() != '\n')
                        ;
        }

        return select;
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

                        // case 1: //      RESIZE IMAGE
                        //         //      ────────────
                        //         break;

                case 2: //      INVERT IMAGE
                        //      ────────────
                ;
                        char axis[] = "yx";
                        printf("Axis: ");
                        scanf("%2[^\n]", axis);
                        while (getchar() != '\n') // Clean buffer
                                ;

                        // Invert and write new image
                        image_write(image_invert(img, axis), argv[2]);

                        break;

                case 3: //      BINARIZE PGM
                        //      ────────────
                ;
                        // Write bin file
                        image_write(image_binarize(img), argv[2]);

                        break;

                default: //     SORRY
                         //     ────
                        fprintf(stderr, "menu: invalid option or not implemented function yet\n");
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

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
                        // image_to_pgm();
                        break;

                case 2: //      PLAIN PGM
                        //      ─────────
                        if (img.type == PLAIN_PGM_TY)
                                continue;

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
                        // image_to_plain_pgm();
                        break;

                case 3: //      PPM
                        //      ───
                        if (img.type == PPM_TY)
                                continue;

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
                        // image_to_ppm();
                        break;

                case 4: //      PLAIN_PPM
                        //      ─────────
                        if (img.type == PLAIN_PPM_TY)
                                continue;

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
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
                        fprintf(stderr, "menu_convet: invalid option\n");
                }
                while (getchar() != '\n')
                        ;
        }
}
