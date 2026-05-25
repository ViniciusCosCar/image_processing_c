#include "superIMG.h"

#include <stdio.h>
#include <stdlib.h>

// ──────────────────────────────────────────────────────────

// ─── Get image family specification
Family image_get_family(const char *fname)
{
        //      TODO: Improve; it assumes to be NETPBM for now
        //      ──────────────────────────────────────────────

        return NETPBM_F;
}

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
        //         return PLAIN_PGM_print_colored(img);
        // case PPM_TY:
        //         return PPM_print_colored(img);
        // case PLAIN_PPM_TY:
        //         return PLAIN_PPM_print_colored(img);
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
// ─── R E A D
// ──────────────────────────────────────────────────────────

// ─── Read image in file and return IMAGE object
IMAGE image_read(const char *fname)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (fname == NULL)
                return (IMAGE){UNKNOWN_F, UNKNOWN_TY, 0, 0, NULL};

        //      USE THE APROPRIATE READ FUNCTION
        //      ────────────────────────────────
        Family family = image_get_family(fname);

        switch (family)
        {
        case NETPBM_F:
                return NETPBM_read(fname);
        default:
                return (IMAGE){family, UNKNOWN_TY, 0, 0, NULL};
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
                fprintf(stderr, "image_to_ascii: Invalid img provided\n");
                exit(0);
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
                        fprintf(stderr, "image_to_ascii: Conversion function not developed yet\n");
                        exit(0);
                }
        default:
                fprintf(stderr, "image_to_ascii: Conversion function not developed yet\n");
                exit(0);
        }
}
