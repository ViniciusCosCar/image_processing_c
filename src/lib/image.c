#include "superIMG.h"

#include <stdio.h>
#include <stdlib.h>

// ──────────────────────────────────────────────────────────

// ─── Get image family specification
//      Supose that image files start immediatly with the header,
//      containing no comments before it
Family image_detect_family(const char *fname)
{
        //      OPEN FILE
        //      ─────────
        FILE *fp = fopen(fname, "rb");
        if (fp == NULL)
        {
                fprintf(stderr, "image_detect_family: it was not possible to open file for reading");
                return UNKNOWN_F;
        }

        //      DETECT FAMILY
        //      ─────────────
        /* ─── At this current moment, it detects
                NEPTBM files, and consider anything
                else to be an ascii image) */
        char first_char;
        fscanf(fp, "%c", &first_char);

        if (first_char == 'P')
                return NETPBM_F;

        return ASCII_F;
}
// ──────────────────────────────────────────────────────────
// ─── R E A D
// ──────────────────────────────────────────────────────────
// ─── Read image in file and return IMAGE object
IMAGE image_read(const char *fname)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (fname == NULL)
                return NULLIMG;

        //      USE THE APROPRIATE READ FUNCTION
        //      ────────────────────────────────
        Family family = image_detect_family(fname);

        switch (family)
        {
        case NETPBM_F:
                return NETPBM_read(fname);
        case ASCII_F:
                return ASCII_read(fname);
        default:
                return NULLIMG;
        }
}
// ──────────────────────────────────────────────────────────
// ─── W R I T E
// ──────────────────────────────────────────────────────────
// ─── Write src data to data
int image_write(const IMAGE img, const char *dest_fname)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (dest_fname == NULL)
                return 0;

        //      USE THE APROPRIATE READ FUNCTION
        //      ────────────────────────────────
        switch (img.family)
        {
        case NETPBM_F:
                switch (img.type)
                {
                case PGM_TY:
                        return PGM_write(img, dest_fname);
                // case PLAIN_PGM_TY:
                //         return plain_PGM_write(img.data, dest_fname);
                // case PPM_TY:
                //         return PPM_write(img.data, dest_fname);
                // case PLAIN_PPM_TY:
                //         return plain_PPM_write(img.data, dest_fname);
                default:
                        return 0;
                }
        default:
                return 0;
        }
}
// ──────────────────────────────────────────────────────────
// ─── C O N V E R T
// ──────────────────────────────────────────────────────────
IMAGE image_to_ascii(const IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.width < 0 || img.height < 0)
        {
                fprintf(stderr, "image_to_ascii: invalid img provided\n");
                return NULLIMG;
        }

        //      USE THE APROPRIATE CONVERSION FUNCTION
        //      ──────────────────────────────────────
        switch (img.family)
        {
        case NETPBM_F:
                switch (img.type)
                {
                case PGM_TY:
                        return PGM_to_ascii(img);
                default:
                        fprintf(stderr, "image_to_ascii: conversion function not developed yet\n");
                        return NULLIMG;
                }
        default:
                fprintf(stderr, "image_to_ascii: conversion function not developed yet\n");
                return NULLIMG;
        }
}
// ──────────────────────────────────────────────────────────
// ─── P R I N T
// ──────────────────────────────────────────────────────────
// ─── Print colored image
int image_print(const IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.width < 0 || img.height < 0)
        {
                fprintf(stderr, "PGM_write: error reading image data\n");
                return 0;
        }

        //      CHOOSE FUNCTION TO PRINT COLORED IMAGE
        //      ──────────────────────────────────────
        switch (img.type)
        {
        case PGM_TY:
                return PGM_print(img);
        // case PLAIN_PGM_TY:
        //         return PLAIN_PGM(img);
        // case PPM_TY:
        //         return PPM_print(img);
        // case PLAIN_PPM_TY:
        //         return PLAIN_PPM(img);
        case ASCII_TY:
                return ASCII_print(img);
        default:
                fprintf(stderr, "Feature not implemented yet for choose image format"
                                " or option choosen does not match any options\n");
                return 0;
        }

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── B I N A R I Z E
// ──────────────────────────────────────────────────────────
// ─── Binarize image
IMAGE image_binarize(const IMAGE img)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.width < 0 || img.height < 0)
        {
                fprintf(stderr, "image_binarize: invalid img provided\n");
                return NULLIMG;
        }

        //      USE THE APROPRIATE BINARIZE FUNCTION
        //      ────────────────────────────────────
        switch (img.family)
        {
        case NETPBM_F:
                switch (img.type)
                {
                case PGM_TY:
                        return PGM_binarize(img);
                default:
                        fprintf(stderr, "image_binarize: binarize function not developed yet\n");
                        return NULLIMG;
                }
        // case ASCII_F:
        //         return ASCII_binarize();
        default:
                fprintf(stderr, "image_binarize: binarize function not developed yet\n");
                return NULLIMG;
        }
}
// ──────────────────────────────────────────────────────────
// ─── I N V E R T
// ──────────────────────────────────────────────────────────
// ─── Invert image
IMAGE image_invert(const IMAGE img, const char *fname)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (img.data == NULL || img.width < 0 || img.height < 0)
        {
                fprintf(stderr, "image_invert: invalid img provided\n");
                return NULLIMG;
        }

        //      USE THE APROPRIATE BINARIZE FUNCTION
        //      ────────────────────────────────────
        switch (img.family)
        {
        case NETPBM_F:
                switch (img.type)
                {
                case PGM_TY:
                        return PGM_invert(img, fname);
                default:
                        fprintf(stderr, "image_invert: invert function not developed yet\n");
                        return NULLIMG;
                }
        // case ASCII_F:
        //         return ASCII_invert(img, argv[2]);
        default:
                fprintf(stderr, "image_invert: invert function not developed yet\n");
                return NULLIMG;
        }
}
