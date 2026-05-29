#ifndef NETPBM_C
#define NETPBM_C

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "superIMG.h"

// ──────────────────────────────────────────────────────────
// ─── READ AND PRINT COMMENTS IN NETPBM IMAGE FILE
// ──────────────────────────────────────────────────────────
int NETPBM_readprintComment(FILE *fp)
{
        //      VERIFY ARGUMENTS
        //      ────────────────
        if (fp == NULL)
                return 0;

        //      READ AND PRINT COMMENTS
        //      ───────────────────────

        // '#' preceeds comments
        char c;
        while (fscanf(fp, "#%c", &c))
        {
                while (fscanf(fp, "%c", &c), c != '\n')
                        printf("%c", c);

                printf("\n");
        }

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── READ NETPBM FILE AND RETURN IMAGE OBJECT
// ──────────────────────────────────────────────────────────
IMAGE NETPBM_read(const char *fname)
{
        uint8_t *data;
        int width, height, typeno, maxvalue, datasize;

        //      VERIFY ARGUMENTS
        //      ────────────────
        if (fname == NULL)
                return (IMAGE)NULLIMG;

        //      OPEN THE FILE
        //      ─────────────
        fprintf(stderr, "NETPBM_read: opening %s\n", fname);

        FILE *fp = fopen(fname, "rb");
        if (fp == NULL)
        {
                fprintf(stderr, "NETPBM_read: error opening file\n");
                return NULLIMG;
        }

        //      GATHER INFORMATION REGARDING IMAGE AND TYPE
        //      ───────────────────────────────────────────

        // ─── Type
        if (fscanf(fp, "P%d\n", &typeno) != 1)
        {
                fprintf(stderr, "NETPBM_read: error reading typeno\n");
                return NULLIMG;
        }
        NETPBM_readprintComment(fp);

        // ─── Width and Height
        if (fscanf(fp, "%d %d\n", &width, &height) != 2)
        {
                fprintf(stderr, "NETPBM_read: error reading width,height\n");
                return NULLIMG;
        }
        NETPBM_readprintComment(fp);

        // ─── Max value for data element
        if (fscanf(fp, "%d", &maxvalue) != 1)
        {
                fprintf(stderr, "readpgm: error reading maxvalue\n");
                return NULLIMG;
        }
        NETPBM_readprintComment(fp);

        /* Read newline separately to avoid skipping bytes of
           image data corresponding to form-feeds */
        fgetc(fp);

        //      READ DATA RESTER TO DATA FIELD
        //      ──────────────────────────────

        datasize = width * height;

        // ─── Allocate sufficient memory
        data = malloc(datasize);
        if (data == NULL)
        {
                fprintf(stderr, "NETPBM_read: calloc error\n");
                return NULLIMG;
        }
        if (fread(data, sizeof(uint8_t), datasize, fp) != datasize)
        {
                fprintf(stderr, "NETPBM_read: error reading image\n");
                return NULLIMG;
        }

        //      RETURN AND FINISH SAFETLY
        //      ─────────────────────────

        fclose(fp);

        Type type = (typeno == 2) ? (PLAIN_PGM_TY) : (typeno == 5) ? (PGM_TY) : (UNKNOWN_TY);
        return (IMAGE){NETPBM_F, type, width, height, datasize, maxvalue, data};
}

#endif
