#include <stdlib.h>
#include <sys/stat.h>

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

                                fprintf(stderr, "main: video visualization is still not ready...\n");
                                while (getchar() != '\n')
                                        ;
                                break;

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
