#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ──────────────────────────────────────────────────────────
// ─── INVERT TWO UNSIGNED CHARS
// ──────────────────────────────────────────────────────────
void invert(unsigned char *e1, unsigned char *e2)
{
        unsigned char aux = *e1;
        *e1 = *e2;
        *e2 = aux;
}
// ──────────────────────────────────────────────────────────
// ─── INVERT ARRAY
// ──────────────────────────────────────────────────────────
int invert_array(unsigned char *array, int size)
{
        if (!array || size < 0)
                return 0;

        for (int i = 0, j = size - 1; i < j; i++, j--)
        {
                invert(&array[i], &array[j]);
        }
        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── PRODUCE ASCII VERSION OF IMAGE PROVIDED
// ──────────────────────────────────────────────────────────
int img_ascii(unsigned char *img, int imgsize)
{
        if (imgsize < 0)
                return 0;

        // https://paulbourke.net/dataformats/asciiart/
        // char illumination[] =
        // "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/()1{}[]?-_+~<>i!lI;:,`'. ";
        char illumination[] = "@%#*+=-:. ";
        int scale_div = sizeof(illumination) / sizeof(char);

        for (int i = 0; i < imgsize; i++)
        {
                img[i] = illumination[(int)(img[i] * (scale_div - 1)) / 255];
        }

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── PRODUCE BINARIZED VERSION OF IMAGE PROVIDED
// ──────────────────────────────────────────────────────────
int img_bin(unsigned char *img, int imgsize, unsigned char limiar)
{
        if (imgsize < 0)
                return 0;

        for (int i = 0; i < imgsize; i++)
                if (img[i] < limiar)
                        img[i] = 0;

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── INVERT IMAGE ALONGSIDE AN SPECIFIEDED AXIS
// ──────────────────────────────────────────────────────────
int invert_img(unsigned char *img, int w, int h, char *axis)
{
        int imgsize = w * h;
        if (!img || imgsize <= 0 || !axis)
                return 0;

        // Invert along yx
        if (strcmp(axis, "yx") == 0 || strcmp(axis, "xy") == 0)
                invert_array(img, imgsize);
        // Invert along x
        else if (strcmp(axis, "x") == 0)
                for (int j = 0; j < w; j++)
                {
                        for (int i = 0, k = h - 1; i < k; i++, k--)
                                invert(&img[j + i * w], &img[j + k * w]);
                }
        // Invert along y
        else if (strcmp(axis, "y") == 0)
                for (int i = 0; i < h; i++)
                        invert_array(img + i * w, w);

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── PRINT COLORED PGM IMAGE WITH ASCII ESCAPE SEQUENCES
// ──────────────────────────────────────────────────────────
int print_color(unsigned char *img, int w, int h)
{
        if (img == NULL || w < 0 || h < 0)
                return 0;

        for (int i = 0; i < h; i++)
        {
                for (int j = 0; j < w; j++)
                        printf("\033[4%dm ", 7 * img[i * w + j] / 255);
                printf("\n");
        }
        printf("\033[m\n");

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── READ AND PRINT COMMENTS IN IMAGE FILE
// ──────────────────────────────────────────────────────────
void readprintComment(FILE *fp)
{
        // '#' preceeds comments
        char dumchar;
        while (fscanf(fp, "#%c", &dumchar))
        {
                // But what if we reach EOF before '\n'?
                // Maybe this instead,
                // while(fscanf(fp,"%c",&dumchar), dumchar!='\n' && dumchar!=EOF)
                // printf("%c",dumchar);
                while (fscanf(fp, "%c", &dumchar), dumchar != '\n')
                        printf("%c", dumchar);
                printf("\n");
        }
}
// ──────────────────────────────────────────────────────────
// ─── READ PGM FILE TO AN ARRAY
// ──────────────────────────────────────────────────────────
unsigned char *readpgm(char *filename, int *width, int *height)
{
        unsigned char *img;
        int i, j, imgsize, c;
        int typeno, maxvalue;
        FILE *fp;

        fprintf(stderr, "readpgm: opening %s\n", filename);

        fp = fopen(filename, "rb"); /* 2nd parameter must be equal to "rb" in Windows! */
        if (!fp)
        {
                fprintf(stderr, "readpgm: error opening file\n");
                exit(0);
        }

        // Print/ignore comments
        readprintComment(fp);

        // A raw pgm file is identified by the number P5, for a plain pgm,
        // the number is P2
        if (fscanf(fp, "P%d\n", &typeno) != 1)
        {
                fprintf(stderr, "readpgm: error reading typeno\n");
                exit(0);
        }
        fprintf(stderr, "readpgm: ppm type P%d\n", typeno);
        readprintComment(fp);

        // Read width and height
        if (fscanf(fp, "%d %d\n", width, height) != 2)
        {
                fprintf(stderr, "readpgm: error reading width,height\n");
                exit(0);
        }
        fprintf(stderr, "readpgm: w %d  h %d\n", *width, *height);
        readprintComment(fp);

        // Read maxvalue
        if (fscanf(fp, "%d", &maxvalue) != 1)
        {
                fprintf(stderr, "readpgm: error reading maxvalue\n");
                exit(0);
        }
        fprintf(stderr, "maxvalue %d\n", maxvalue);
        readprintComment(fp);

        /* fix 14.10.97: read newline separately to avoid skipping bytes of
      image data corresponding to form-feeds
      */
        fgetc(fp);

        imgsize = (*width) * (*height);

        switch (typeno)
        {
        case 2: /*  plainbits pgm type */

                fprintf(stderr, "readppm: sorry plain ppm not implemented\n");
                exit(0);

        case 5: /*  rawbits pgm type */

                img = (unsigned char *)calloc(imgsize, sizeof(unsigned char));
                if (!img)
                {
                        fprintf(stderr, "readppm: calloc error 3\n");
                        exit(0);
                }
                if (fread(img, sizeof(unsigned char), imgsize, fp) != imgsize)
                {
                        fprintf(stderr, "readppm: error reading image\n");
                        exit(0);
                }

                break;
        default:
                fprintf(stderr, "readppm: sorry ppm type not implemented\n");
                exit(0);
        }

        fclose(fp);

        return img;
}
// ──────────────────────────────────────────────────────────
// ─── WRITE PGM IMAGE CALLED fname BASED ON img PROVIDED
// ──────────────────────────────────────────────────────────
void writepgm(unsigned char *img, int width, int height, char *fname)
{
        int imgsize;
        FILE *fp;

        if (!(fp = fopen(fname, "wb")))
        { /* 2nd parameter must be equal to "rb" in Windows! */
                fprintf(stderr, "writepgm: error opening output file\n");
                exit(0);
        }

        fprintf(fp, "P5\n");
        fprintf(fp, "%d %d\n", width, height);
        fprintf(fp, "%d\n", 255);

        imgsize = width * height;

        if (!fwrite(img, sizeof(unsigned char), imgsize, fp))
        {
                fprintf(stderr, "writepgm: write error\n");
                exit(0);
        }

        fclose(fp);
        fprintf(stderr, "%s successfully created\n", fname);
}
// ──────────────────────────────────────────────────────────
// ─── WRITE ASCII FILE CALLED fname BASED ON img PROVIDED
// ──────────────────────────────────────────────────────────
void writeascii(unsigned char *img, int width, int height, char *fname)
{
        FILE *fp;
        if (!(fp = fopen(fname, "w")))
        {
                fprintf(stderr, "writeascii: error creating txt file\n");
                exit(0);
        }

        int imgsize = width * height;
        for (int i = 0; i < imgsize; fprintf(fp, "%c", img[i++]))
        {
                if (i % width == 0)
                {
                        fprintf(fp, "\n");
                }
        }

        fclose(fp);

        fprintf(stderr, "%s successfully created\n", fname);
}

#endif
