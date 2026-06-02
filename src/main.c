#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "lib/superIMG.h"

int main(int argc, char **argv)
{
        struct stat s1, s2;

        //      Verify arguments
        //      ────────────────
        if (argc < 2 || argv[1] == NULL)
        {
                fprintf(stderr,
                        "main: correct usage './superIMG <path to src. file or directory> <Optional: path to dest. "
                        "file or directory>'\n");
                return 0;
        }

        //      GET PATH ATRIBUTES
        //      ──────────────────
        if (stat(argv[1], &s1) == -1)
        {
                fprintf(stderr, "main: this program is too dumb to handle this kind of input yet\n");
                return 0;
        }
        if (argc >= 3 && stat(argv[2], &s2) == -1)
        {
                fprintf(stderr,
                        "main: this program is too dumb to understand the second path; it will just ignore it\n");
                while (getchar() != '\n')
                        ;
        }

        //      READ PGM FILE TO ARRAY
        //      ──────────────────────
        const IMAGE img = image_read(argv[1]);

        //      SELECT OPERATIONS TO PERFORM
        //      ────────────────────────────
        while (1)
        {
                switch (menu(img))
                {
                case 1:
                        exit(0);

                case TRANSFORM:
                        menu_transform(img, argv);
                        break;

                case CONVERT:
                        menu_convert(img, argv);
                        break;

                case VIEW:;

                        // Distinguish a file from a directory
                        switch (s1.st_mode & S_IFMT)
                        {
                        case S_IFDIR: // If it is a dir
                        {

                                DIR *dir;
                                struct dirent *env;

                                // Open directory
                                if ((dir = opendir(argv[1])) != NULL)
                                {
                                        while ((env = readdir(dir)) != NULL)
                                        {
                                                char *fpath =
                                                malloc(strlen(argv[1]) + 1 + strlen(env->d_name) + 1); // '/','\0'

                                                strcpy(fpath, argv[1]);     // directory
                                                strcat(fpath, "/");         // directory/
                                                strcat(fpath, env->d_name); // directory/file

                                                printf("\033[2;3J\033[H");
                                                image_print(image_read(fpath));

                                                clock_t start = clock();
                                                while ((float)(clock() - start) / CLOCKS_PER_SEC <= 0.25)
                                                        ;
                                        }
                                }
                                // In case of an error
                                else
                                { // TODO
                                }

                                break;
                        }

                        case S_IFREG: // If it is a file

                                image_print(img);
                                while (getchar() != '\n')
                                        ;
                                break;

                        default: // Todo: handle weired path
                        ;
                        }
                        break;
                }
        };

        //      FREE ALLOCATED MEMORY
        //      ─────────────────────
        free(img.data);
}
