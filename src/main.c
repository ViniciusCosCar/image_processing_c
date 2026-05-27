#include <stdio.h>
#include <stdlib.h>

#include "lib/UI/UI.h"
#include "lib/superIMG.h"

void clear()
{
        printf("\033[2;3J\033[H");
}

char *format_number(int n)
{
        static char res[8 * sizeof(int) + 3 * sizeof(char)]; // Unit + ' ' + '\0'

        if (n > 1000000)
                sprintf(res, "%d %c", n / 1000000, 'm');
        else if (n > 1000)
                sprintf(res, "%d %c", n / 1000, 'k');
        else
                sprintf(res, "%d  ", n);

        return res;
}

int main(int argc, char **argv)
{
        //      READ PGM FILE TO ARRAY
        //      ──────────────────────
        const IMAGE img = image_read(argv[1]);

        //      SELECT OPERATIONS TO PERFORM
        //      ────────────────────────────
        while (1)
        {
                const char *types[] = {"ASCII", "PGM", "Plain PGM", "PPM", "Plain PPM", "PNG", "JPEG_TY", "UNKNOWN"};
                clear();
                printf("Format: %s\n", types[img.type]);
                printf("Res: %dx%d\n", img.width, img.height);
                printf("Size: %sB\n", format_number(img.datasize));
                switch (menu())
                {
                case TRANSFORM:
                        menu_transform(img, argv);
                        break;

                case CONVERT:
                        menu_convert(img, argv);
                        break;

                case VIEW:
                        image_print(img);
                        while (getchar() != '\n')
                                ;
                        break;
                }
        };

        //      FREE ALLOCATED MEMORY
        //      ─────────────────────
        free(img.data);
}
