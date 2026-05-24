#include <stdlib.h>

#include "superIMG.h"

// ──────────────────────────────────────────────────────────
// ─── WRITE ASCII FILE BASED ON DATA SOURCE PROVIDED
// ──────────────────────────────────────────────────────────
// int ASCII_write(const uint8_t *src, const int width, const int height, const char *fname)
// {
//         //      VERIFY INPUT
//         //      ────────────
//         if (src == NULL || width < 0 || height < 0 || fname == NULL)
//                 return 0;
//
//         //      OPEN FILE
//         //      ─────────
//         FILE *dest_f;
//         if (!(dest_f = fopen(fname, "w")))
//         {
//                 fprintf(stderr, "NETPBM_writeascii: error creating txt file\n");
//                 exit(0);
//         }
//
//         //      WRITE TO FILE
//         //      ─────────────
//         int datasize = width * height;
//         for (int i = 0; i < datasize; fprintf(dest_f, "%c", src[i++]))
//                 if (i % width == 0)
//                         fprintf(dest_f, "\n");
//
//         //      END CORRECTLY
//         //      ─────────────
//         fclose(dest_f);
//
//         fprintf(stderr, "%s successfully created\n", fname);
//         return 1;
// }
