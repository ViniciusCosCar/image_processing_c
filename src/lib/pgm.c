#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "superIMG.h"

// ──────────────────────────────────────────────────────────
// ─── WRITE PGM IMAGE CALLED fname BASED ON img PROVIDED
// ──────────────────────────────────────────────────────────
int PGM_write(IMAGE img, const char *fname)
{
        FILE *fp;

        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || fname == NULL)
        {
                fprintf(stderr, "PGM_write: error reading image data or receiving file name\n");
                return 0;
        }
        if (!(fp = fopen(fname, "wb")))
        {
                fprintf(stderr, "PGM_write: error opening output file\n");
                return 0;
        }

        //      WRITE PGM TO FILE
        //      ─────────────────
        fprintf(fp, "P5\n");
        fprintf(fp, "%d %d\n", img.width, img.height);
        fprintf(fp, "%d\n", img.maxvalue);

        if (!fwrite(img.data, sizeof(uint8_t), img.width * img.height, fp))
        {
                fprintf(stderr, "PGM_write: write error\n");
                return 0;
        }

        //      RETURN AND FINISH SAFETLY
        //      ─────────────────────────
        fclose(fp);
        fprintf(stderr, "%s successfully created\n", fname);

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── PRINT COLORED PGM IMAGE WITH ANSII ESCAPE SEQUENCES
// ──────────────────────────────────────────────────────────
int PGM_print(IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.datasize < 0)
        {
                fprintf(stderr, "PGM_write: error reading image data\n");
                return 0;
        }

        //      PRINT COLORED IMAGE
        //      ───────────────────
        for (int i = 0; i < img.datasize; i++)
        {
                printf("\033[4%dm ", 7 * ((uint8_t *)img.data)[i] / 255);

                if (i % img.width == 0)
                        printf("\n");
        }
        printf("\033[m\n");

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── PRODUCE BINARIZED VERSION OF PGM PROVIDED
// ──────────────────────────────────────────────────────────
IMAGE PGM_binarize(const IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.datasize < 0)
        {
                fprintf(stderr, "PGM_binarize: invalid image\n");
                return img;
        }

        //      CALCULATE LIMIAR
        //      ────────────────
        int limiar = 0;
        for (int i = 0; i < img.datasize; limiar += ((uint8_t *)img.data)[i++])
                ;
        limiar /= img.datasize;

        //      SET dest[i] TO BINARIZED PIXEL OF src[i]
        //      ────────────────────────────────────────
        IMAGE img_bin = img;

        img_bin.data = malloc(img.datasize);
        for (int i = 0; i < img.datasize; i++)
                if (((uint8_t *)img.data)[i] < limiar)
                        ((uint8_t *)img_bin.data)[i] = 0;
                else
                        ((uint8_t *)img_bin.data)[i] = 255;

        return img_bin;
}
// ──────────────────────────────────────────────────────────
// ─── INVERT PGM ALONGSIDE AN SPECIFIEDED AXIS
// ──────────────────────────────────────────────────────────
IMAGE PGM_invert(const IMAGE img, const char *axis)
{
        IMAGE inv_img = img;
        inv_img.data = malloc(img.datasize);

        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.datasize < 0 || axis == NULL)
                return img;

        //      COPY SRC TO DEST DATA BUFFER
        //      ────────────────────────────
        cp(img.data, inv_img.data, img.datasize);

        //      INVERT ALONG AXIS
        //      ─────────────────
        // ─── yx
        if (strcmp(axis, "yx") == 0 || strcmp(axis, "xy") == 0)
                invert_array(inv_img.data, img.datasize);

        // ─── x
        else if (strcmp(axis, "x") == 0)
                for (int j = 0; j < inv_img.width; j++)
                        for (int i = 0, k = inv_img.height - 1; i < k; i++, k--)
                                swap(&((uint8_t *)inv_img.data)[j + i * inv_img.width],
                                     &((uint8_t *)inv_img.data)[j + k * inv_img.width]);
        // ─── y
        else if (strcmp(axis, "y") == 0)
                for (int i = 0; i < inv_img.height; i++)
                        invert_array(inv_img.data + i * inv_img.width, inv_img.width);

        return inv_img;
}
// ──────────────────────────────────────────────────────────
// ─── PGM resize
// ──────────────────────────────────────────────────────────
IMAGE PGM_resize(const IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.datasize < 0)
        {
                fprintf(stderr, "PGM_resize: invalid image\n");
                return img;
        }

        // ─── Ask new resolution

        return NULLIMG;
}

// ──────────────────────────────────────────────────────────
// ─── CONVERT PGM TO ASCII TO IMAGE
// ──────────────────────────────────────────────────────────
IMAGE PGM_to_ascii(const IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.datasize < 0)
        {
                fprintf(stderr, "PGM_to_ascii: inadequate pgm image provided");
                return img;
        }

        //      ACTUAL CONVERSION
        //      ─────────────────
        // https://paulbourke.net/dataformats/asciiart/
        // char illumination[] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/()1{}[]?-_+~<>i!lI;:,`'. ";
        char illumination[] = "@%#*+=-:. ";                      // Currently  uses 10 levels of grey
        int scale_div = sizeof(illumination) / sizeof(char) - 1; // -1 because of '\0'

        IMAGE ascii_img = ASCII;
        ascii_img.datasize = img.datasize + img.height + 1; // + 1 -> '\0'
        ascii_img.data = malloc(ascii_img.datasize);

        for (int i = 0, j = 0, again = 0; i < ascii_img.datasize - 1; i++) // - 1 -> '\0'
        {
                if (j % img.width == 0 && again == 0)
                {
                        ((char *)ascii_img.data)[i] = '\n';
                        again = 1;
                        continue;
                }

                ((char *)ascii_img.data)[i] = illumination[(int)(((uint8_t *)img.data)[j++] * (scale_div - 1)) / 255];
                again = 0;
        }
        ((char *)ascii_img.data)[ascii_img.datasize - 1] = '\0';

        return ascii_img;
}
