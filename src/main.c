#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "lib/superIMG.h"
int comp(const void *a, const void *b)
{

        // Using strcmp() for comparing two strings
        return strcmp(*(const char **)a, *(const char **)b);
}

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
                        // ─── Distinguish a file from a directory
                        switch (s1.st_mode & S_IFMT)
                        {
                        case S_IFDIR: { // ─── TODO: transform it in a function

                                DIR *dir;
                                struct dirent *item;
                                char **fpaths = NULL;
                                size_t n_paths = 0;

                                // ─── Open directory
                                if ((dir = opendir(argv[1])) != NULL)
                                {
                                        // ─── Create list of file names
                                        while ((item = readdir(dir)) != NULL)
                                        {
                                                if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0)
                                                        continue;

                                                if (fpaths != NULL)
                                                        fpaths =
                                                        (char **)realloc(fpaths, sizeof(char *) * (n_paths + 1));
                                                else
                                                        fpaths = (char **)malloc(sizeof(char *));

                                                //                            '/'                      '\0'
                                                size_t len = strlen(argv[1]) + 1 + strlen(item->d_name) + 1;
                                                fpaths[n_paths] = malloc(len);
                                                snprintf(fpaths[n_paths], len, "%s/%s", argv[1], item->d_name);
                                                n_paths++;
                                        }

                                        // ─── Order list of file names
                                        qsort(fpaths, n_paths, sizeof(fpaths[0]), comp);

                                        for (int i = 0; i < n_paths; i++)
                                        {
                                                // printf("%s\n", fpaths[i]);
                                                const IMAGE n_img = image_read(fpaths[i]);

                                                // ─── Print image
                                                printf("\033[2;3J\033[H");
                                                image_print(n_img);

                                                // ─── fps
                                                clock_t start = clock();
                                                while ((float)(clock() - start) / CLOCKS_PER_SEC <= 0.25)
                                                        ;

                                                free(fpaths[i]);
                                        }
                                        while (getchar() != '\n')
                                                ;

                                        free(fpaths);
                                        closedir(dir);
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
