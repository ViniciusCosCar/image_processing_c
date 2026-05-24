#include <stdlib.h>

#include "superIMG.h"

// ──────────────────────────────────────────────────────────
// ─── WRITE ASCII FILE BASED ON DATA SOURCE PROVIDED
// ──────────────────────────────────────────────────────────
int ASCII_write(const IMAGE src, const char *fname)
{
        //      VERIFY INPUT
        //      ────────────
        if (src.data == NULL || src.width < 0 || src.height < 0 || fname == NULL)
                return 0;

        //      OPEN FILE
        //      ─────────
        FILE *dest_f;
        if (!(dest_f = fopen(fname, "w")))
        {
                fprintf(stderr, "ASCII_write: error creating txt file\n");
                exit(0);
        }

        //      WRITE TO FILE
        //      ─────────────
        int datasize = src.width * src.height;
        for (int i = 0; i < datasize; fprintf(dest_f, "%c", src.data[i++]))
                if (i % src.width == 0)
                        fprintf(dest_f, "\n");

        //      END CORRECTLY
        //      ─────────────
        fclose(dest_f);

        fprintf(stderr, "%s successfully created\n", fname);
        return 1;
}

int ASCII_print(const IMAGE img)
{
        //      VERIFY INPUT
        //      ────────────
        if (img.data == NULL || img.width < 0 || img.height < 0)
        {
                fprintf(stderr, "ASCII_print: It was not possible to print ascii image\n");
                exit(0);
        }

        //      PRINT ASCII IMAGE
        //      ─────────────────
        int datasize = img.width * img.height;
        for (int i = 0; i < datasize; i++)
        {
                printf("%c", img.data[i]);

                if (i % img.width == 0)
                        printf("\n");
        }
        printf("\n");

        return 1;
}
