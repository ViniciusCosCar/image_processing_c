#include <stdio.h>
#include <stdlib.h>

#include "superIMG.h"

// ──────────────────────────────────────────────────────────
// ─── READ ASCII FILE
// ──────────────────────────────────────────────────────────
IMAGE ASCII_read(const char *fname)
{
        //      OPEN FILE
        //      ─────────
        FILE *fp = fopen(fname, "rb");
        if (fp == NULL)
        {
                fprintf(stderr, "ASCII_read: it was not possible to read ascii file\n");
                return NULLIMG;
        }
        //      READ FILE
        //      ─────────
        IMAGE img = ASCII;

        // ─── Find datasize
        fseek(fp, 0, SEEK_END);
        img.datasize = ftell(fp); // Store datasize

        if (img.datasize < 0)
        {
                fprintf(stderr, "ASCII_read: it was not possible to read ascii file");
                fclose(fp);
                return NULLIMG;
        }

        img.data = malloc(img.datasize); // Allocate sufficient memory
        if (img.data == NULL)
        {
                fprintf(stderr, "ASCII_read: it was not possible to allocate space for ascii file");
                fclose(fp);
                return NULLIMG;
        }

        // ─── Copy data to data buffer
        //      Also set img.width and img.height, where
        //      img.width is set to max width found in given image
        fseek(fp, 0, SEEK_SET);

        for (int i = 0, max = 0; i != img.datasize; i++)
        {
                if (fread(img.data + i, sizeof(char), 1, fp) != 1)
                {
                        fprintf(stderr, "ASCII_read: it was not sucessfull in copying all data from provided file");
                        fclose(fp);
                        return img;
                }
                if (((char *)img.data)[i] == '\n')
                {
                        img.height++;
                        if (max > img.width)
                                img.width = max;
                        max = 0;
                }
                else
                        max++;
        }

        fclose(fp);
        return img;
}

// ──────────────────────────────────────────────────────────
// ─── WRITE ASCII FILE BASED ON DATA SOURCE PROVIDED
// ──────────────────────────────────────────────────────────
int ASCII_write(const IMAGE img, const char *fname)
{
        //      VERIFY INPUT
        //      ────────────
        if (img.data == NULL || img.datasize < 0 || fname == NULL)
        {
                fprintf(stderr, "ASCII_write: it was not possible to write ascii file");
                return 0;
        }

        //      OPEN FILE
        //      ─────────
        FILE *fp;
        if (!(fp = fopen(fname, "w")))
        {
                fprintf(stderr, "ASCII_write: error creating txt file\n");
                return 0;
        }

        //      WRITE TO FILE
        //      ─────────────
        if (fwrite(((char *)img.data), sizeof(char), img.datasize, fp) != img.datasize)
        {
                fprintf(stderr, "ASCII_write: it was not possible to write all data to output file");
                return 0;
        }

        //      END CORRECTLY
        //      ─────────────
        fclose(fp);

        fprintf(stderr, "%s successfully created\n", fname);
        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── PRINT
// ──────────────────────────────────────────────────────────
int ASCII_print(const IMAGE img)
{
        //      VERIFY INPUT
        //      ────────────
        if (img.data == NULL || img.datasize < 0)
        {
                fprintf(stderr, "ASCII_print: It was not possible to print ascii image\n");
                return 0;
        }

        //      PRINT ASCII IMAGE
        //      ─────────────────
        // ─── Works if provided image's data is not null terminated
        for (int i = 0; i < img.datasize; printf("%c", ((char *)img.data)[i++]))
                ;

        printf("\n");

        return 1;
}
