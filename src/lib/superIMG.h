#ifndef IMGS_H
#define IMGS_H

#include <stdint.h>
#include <stdio.h>

//
// ────────────────────────────────────────────────── I ──────────
//  :::::: E N U M S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────
//
enum Family
{
        ASCII_F,
        NETPBM_F,
        PNG_F,
        JPEG_F,
        UNKNOWN_F,

} typedef Family;

enum Type
{
        ASCII_TY,

        PGM_TY,
        PLAIN_PGM_TY,

        PPM_TY,
        PLAIN_PPM_TY,

        PNG_TY,

        JPEG_TY,

        UNKNOWN_TY,

} typedef Type;

//
// ─────────────────────────────────────────────────── II ──────────
//  :::::: S T R U C T : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────
//
// ──────────────────────────────────────────────────────────
// ─── I M A G E
// ──────────────────────────────────────────────────────────
struct
{
        const Family family;
        Type type;
        int width;
        int height;
        int datasize;
        int maxvalue;

        void *data;
} typedef IMAGE;

#define ASCII                                                                                                          \
        {                                                                                                              \
                .family = ASCII_F, .type = ASCII_TY, .data = (char *)NULL                                              \
        }
#define PGM                                                                                                            \
        {                                                                                                              \
                .family = NETPBM, .type = PGM_TY, .data = (uint8_t *)NULL                                              \
        }

static const IMAGE nullimg = {.family = UNKNOWN_F, .type = UNKNOWN_TY, .data = NULL};
extern const char *types[];
// #define nullimg                                                                                                        \
//         {                                                                                                              \
//                 .family = UNKNOWN_F, .type = UNKNOWN_TY, .data = NULL                                                  \
//         }
//
// ──────────────────────────────────────────────────────────────────── III ──────────
//  :::::: I M A G E   F U N C T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────
//
// ──────────────────────────────────────────────────────────
// ─── I M A G E
// ──────────────────────────────────────────────────────────
Family image_detect_family(const char *fname); // TODO: Just returns NETPBM_F for now

// ─── Read
IMAGE image_read(const char *fname);

// ─── Write
int image_write(const IMAGE, const char *fname);

// ─── Binarize
IMAGE image_binarize(const IMAGE img);

// ─── Invert
IMAGE image_invert(const IMAGE img, const char *fname);

// ─── Print image
int image_print(const IMAGE);

// ──────────────────────────────────────────────────────────
// ─── N E T P B M
// ──────────────────────────────────────────────────────────
void NETPBM_readprint_comments(const FILE *);
IMAGE NETPBM_read(const char *fname);

// ─── PGM
int PGM_write(const IMAGE, const char *dest_fname);
IMAGE PGM_binarize(const IMAGE);
IMAGE PGM_invert(const IMAGE, const char *axis);
int PGM_print(const IMAGE);

// ─── plain PGM (TODO)
int plain_PGM_write(const uint8_t *src_data, const char *dest_fname);
int PLAIN_PGM_print(const IMAGE);

// ─── PPM (TODO)
int PPM_write(const uint8_t *src_data, const char *dest_fname);
int PPM_print(const IMAGE);

// ─── plain PPM (TODO)
int plain_PPM_write(const uint8_t *src_data, const char *dest_fname);
int PLAIN_PPM_print(const IMAGE);

// ──────────────────────────────────────────────────────────
// ─── T E X T
// ──────────────────────────────────────────────────────────
IMAGE ASCII_read(const char *fname);

// ─── ASCII
int ASCII_write(const IMAGE, const char *);
int ASCII_print(const IMAGE);

//
// ─────────────────────────────────────────────────────────────────────────────── IV ──────────
//  :::::: C O N V E R S I O N   F U N C T I O N S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────
//
IMAGE image_to_ascii(const IMAGE);

// ─── PGM
IMAGE PGM_to_ascii(const IMAGE);

//
// ────────────────────────────────────────────────────────────────────────────── V ──────────
//  :::::: A U X I L I A R Y   F U N C T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────
//
int swap(uint8_t *c1, uint8_t *c2);
int invert_array(uint8_t *array, int bufsize);
int cp(const uint8_t *src, uint8_t *dest, const int buf_size);
int forEach(uint8_t *buf, const int w, const int h, int (*func)(uint8_t *, int w, int h, int i));

#endif
