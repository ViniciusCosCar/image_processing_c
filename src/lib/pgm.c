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
                exit(0);
        }
        if (!(fp = fopen(fname, "wb")))
        {
                fprintf(stderr, "PGM_write: error opening output file\n");
                exit(0);
        }

        //      WRITE PGM TO FILE
        //      ─────────────────
        fprintf(fp, "P5\n");
        fprintf(fp, "%d %d\n", img.width, img.height);
        fprintf(fp, "%d\n", img.maxvalue);

        if (!fwrite(img.data, sizeof(uint8_t), img.width * img.height, fp))
        {
                fprintf(stderr, "PGM_write: write error\n");
                exit(0);
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
int PGM_print_colored(IMAGE img)
{
        int datasize = img.width * img.height;

        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || datasize < 0)
        {
                fprintf(stderr, "PGM_write: error reading image data\n");
                return 0;
        }

        //      PRINT COLORED IMAGE
        //      ───────────────────
        for (int i = 0; i < datasize; i++)
        {
                printf("\033[4%dm ", 7 * img.data[i] / 255);

                if (i % img.width == 0)
                        printf("\n");
        }

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── PRODUCE ASCII VERSION OF IMAGE PROVIDED
// ──────────────────────────────────────────────────────────
// int PGM2ascii(uint8_t *pgm_data, int imgsize, char *ascii_data)
// {
//         if (imgsize < 0 || ascii_data == NULL)
//                 return 0;
//
//         // https://paulbourke.net/dataformats/asciiart/
//         // char illumination[] =
//         // "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/()1{}[]?-_+~<>i!lI;:,`'. ";
//         char illumination[] = "@%#*+=-:. "; // Currently  uses 10 levels of grey
//         int scale_div = sizeof(illumination) / sizeof(char);
//
//         for (int i = 0; i < imgsize; i++)
//                 ascii_data[i] = illumination[(int)(pgm_data[i] * (scale_div - 1)) / 255];
//
//         return 1;
// }
// ──────────────────────────────────────────────────────────
// ─── PRODUCE BINARIZED VERSION OF PGM PROVIDED
// ──────────────────────────────────────────────────────────
IMAGE PGM_binarize(const IMAGE src_img)
{
        //      ────────────────
        const int datasize = src_img.width * src_img.height;

        //      VERIFY ARGUMENTS
        //      ────────────────
        if (src_img.data == NULL || src_img.width < 0 || src_img.height < 0)
                return src_img;

        //      CALCULATE LIMIAR
        //      ────────────────
        int limiar = 0;
        for (int i = 0; i < datasize; limiar += src_img.data[i++])
                ;
        limiar /= datasize;

        //      SET dest[i] TO BINARIZED PIXEL OF src[i]
        //      ────────────────────────────────────────
        uint8_t *dest_data = (uint8_t *)calloc(sizeof(uint8_t), datasize);
        for (int i = 0; i < datasize; i++)
                if (src_img.data[i] < limiar)
                        dest_data[i] = 0;
                else
                        dest_data[i] = 255;

        return (IMAGE){src_img.family, src_img.type, src_img.width, src_img.height, src_img.maxvalue, dest_data};
}
// ──────────────────────────────────────────────────────────
// ─── INVERT PGM ALONGSIDE AN SPECIFIEDED AXIS
// ──────────────────────────────────────────────────────────
IMAGE PGM_invert(const IMAGE src_img, const char *axis)
{
        int datasize = src_img.width * src_img.height;
        uint8_t *dest_data = (uint8_t *)calloc(sizeof(uint8_t), datasize);

        //      VERIFY ARGUMENTS
        //      ────────────────
        if (src_img.data == NULL || datasize < 0 || axis == NULL)
                return src_img;

        //      COPY SRC TO DEST DATA BUFFER
        //      ────────────────────────────
        cp(src_img.data, dest_data, datasize);

        //      INVERT ALONG AXIS
        //      ─────────────────
        // ─── yx
        if (strcmp(axis, "yx") == 0 || strcmp(axis, "xy") == 0)
                invert_array(dest_data, datasize);

        // ─── x
        else if (strcmp(axis, "x") == 0)
                for (int j = 0; j < src_img.width; j++)
                        for (int i = 0, k = src_img.height - 1; i < k; i++, k--)
                                swap(&dest_data[j + i * src_img.width], &dest_data[j + k * src_img.width]);

        // ─── y
        else if (strcmp(axis, "y") == 0)
                for (int i = 0; i < src_img.height; i++)
                        invert_array(dest_data + i * src_img.width, src_img.width);

        return (IMAGE){src_img.family, src_img.type, src_img.width, src_img.height, src_img.maxvalue, dest_data};
}
