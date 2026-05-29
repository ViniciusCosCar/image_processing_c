#include "superIMG.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

char *format_number(int);
void clear();

const char *WHITE = "\033[m\033[30;47m";
const char *RED_FG = "\033[31m";
const char *GREEN_FG = "\033[32m";
const char *BLUE_FG = "\033[34m";
const char *PURPLE_FG = "\033[35m";

const char *RST = "\033[m";

// ──────────────────────────────────────────────────────────
// ─── O P E R A T I O N   S E L E C T I O N
// ──────────────────────────────────────────────────────────
void select_opt(char **opts, const int n_opts, const int selected)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        //      ...(TODO)...

        for (int i = 0; i < n_opts; i++)
                if (i == selected - 1)
                        printf("\033[7m%s\033[m", opts[i]);
                else
                        printf("%s", opts[i]);
}
void menu_mov(const char key, unsigned int *selectptr, char **opts, const int n_opts)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        //      ...(TODO)...

        int int_key;
        if (key == 'j' || key == 'B')
        {
                if (*selectptr == n_opts)
                        *selectptr = 1;
                else
                        (*selectptr)++;
        }

        else if (key == 'k' || key == 'A')
        {
                if (*selectptr != 1)
                        (*selectptr)--;
                else
                        (*selectptr) = n_opts;
        }

        else if (int_key = key - '0', int_key >= 1 && int_key <= n_opts)
                *selectptr = int_key;

        select_opt(opts, n_opts, *selectptr);
}
// ──────────────────────────────────────────────────────────
// ─── M E N U
// ──────────────────────────────────────────────────────────
Operation menu(IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        //      ...(TODO)...

        const char *opts_H = "▁▁▁Choose a function to perform▁▁▁▁▁▁▁▁▁▁\n";
        const char *opts_B = "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";

        char *opts[] = {"░ 1   exit                              ░\n", "░ 2   transform                         ░\n",
                        "░ 3   convert                           ░\n", "░ 4   view                              ░\n"};
        const int n_opts = sizeof(opts) / sizeof(*opts);

        system("");

        char key;
        unsigned int select = 1;
        do
        {
                clear();

                printf("Format: %s\n", types[img.type]);
                printf("Res: %dx%d\n", img.width, img.height);
                printf("Size: %sB\n", format_number(img.datasize));

                printf("\n%s", opts_H);

                menu_mov(key, &select, opts, n_opts);

                printf("%s", opts_B);

        } while ((key = raw_getch(STDIN_FILENO)) != '\n');

        return select;
}
// ──────────────────────────────────────────────────────────
// ─── M E N U   I M A G E   T R A N S F O R M A T I O N S
// ──────────────────────────────────────────────────────────
void menu_transform(const IMAGE img, char **argv)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        //      ...(TODO)...

        const char *opts_H = "▁▁▁Which transformation to apply▁▁▁▁▁▁▁▁▁\n";
        const char *opts_B = "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
        char *opts[] = {"░ 1   back                              ░\n", "░ 2   resize                            ░\n",
                        "░ 3   invert                            ░\n", "░ 4   binarize                          ░\n"};
        const int n_opts = sizeof(opts) / sizeof(*opts);

        system("");

        char key;
        unsigned int select = 1;
        while (1)
        {
                //      LET USER TO CHOOSE AN OPERATION
                //      ────────────────────────────────
                do
                {
                        clear();

                        printf("%s", opts_H);
                        menu_mov(key, &select, opts, n_opts);
                        printf("%s", opts_B);

                } while ((key = raw_getch(STDIN_FILENO)) != '\n');

                //      PERFORM CHOOSEN OPERATION
                //      ────────────────────────────────
                switch (select)
                {
                case 1: //      GO BACK
                        //      ───────
                        return;

                        // case 2: //      RESIZE IMAGE
                        //         //      ────────────
                        //         break;

                case 3: //      INVERT IMAGE
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

                case 4: //      BINARIZE PGM
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
        //      VERIFY ARGUMENTS
        //      ────────────────
        //      ...(TODO)...

        const char *opts_H = "▁▁▁Convert to▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
        const char *opts_B = "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
        char *opts[] = {"░ 1   back                              ░\n", "░ 2   PGM                               ░\n",
                        "░ 3   Plain PGM                         ░\n", "░ 4   PPM                               ░\n",
                        "░ 5   Plain PPM                         ░\n", "░ 6   ASCII                             ░\n"};
        const int n_opts = sizeof(opts) / sizeof(*opts);

        system("");

        char key;
        unsigned int select = 1;
        while (1)
        {
                //      LET USER TO CHOOSE AN OPERATION
                //      ────────────────────────────────
                do
                {
                        clear();

                        printf("%s", opts_H);
                        menu_mov(key, &select, opts, n_opts);
                        printf("%s", opts_B);

                } while ((key = raw_getch(STDIN_FILENO)) != '\n');

                //      PERFORM CONVERSION
                //      ──────────────────
                switch (select)
                {
                case 1: //      GO BACK
                        //      ───────
                        return;

                case 2: //      PGM
                        //      ───
                        if (img.type == PGM_TY)
                                continue;

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
                        // image_to_pgm();
                        break;

                case 3: //      PLAIN PGM
                        //      ─────────
                        if (img.type == PLAIN_PGM_TY)
                                continue;

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
                        // image_to_plain_pgm();
                        break;

                case 4: //      PPM
                        //      ───
                        if (img.type == PPM_TY)
                                continue;

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
                        // image_to_ppm();
                        break;

                case 5: //      PLAIN_PPM
                        //      ─────────
                        if (img.type == PLAIN_PPM_TY)
                                continue;

                        fprintf(stderr, "menu_convert: not implemented function yet\n");
                        // image_to_plain_ppm();
                        break;

                case 6: //      ASCII
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

// ──────────────────────────────────────────────────────────
// ─── FORMAT BIG NUMBERS WITH UNITS
// ──────────────────────────────────────────────────────────
char *format_number(int n)
{
        static char res[8 * sizeof(float) + 3 * sizeof(char)]; // Unit + ' ' + '\0'

        if (n > 1000000)
                sprintf(res, "%d %c", n / 1000000, 'M');
        else if (n > 1000)
                sprintf(res, "%d %c", n / 1000, 'K');
        else
                sprintf(res, "%d  ", n);

        return res;
}

void clear()
{
        printf("\033[2;3J\033[H");
}
