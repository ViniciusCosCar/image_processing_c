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
        NETPBM_F,
        PNG_F,
        JPEG_F,
        UNKNOWN_F

} typedef Family;

enum Type
{
        PGM_TY,
        PLAIN_PGM_TY,

        PPM_TY,
        PLAIN_PPM_TY,

        PNG_TY,

        JPEG_TY,

        UNKNOWN_TY

} typedef Type;
//
// ──────────────────────────────────────────────── II ─────────────
//  :::::: S T R U C T : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────
//
// ──────────────────────────────────────────────────────────
// ─── I M A G E
// ──────────────────────────────────────────────────────────
struct
{
        const Family family;
        const Type type;
        const int width;
        const int height;
        const int maxvalue;

        uint8_t *data;

} typedef IMAGE;
//
// ────────────────────────────────────────────────── III ────────────────────────────
//  :::::: I M A G E   F U N C T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────
//
// ──────────────────────────────────────────────────────────
// ─── I M A G E
// ──────────────────────────────────────────────────────────
Family image_get_family(const char *fname); // To be defined

// ─── Read
IMAGE image_read(const char *fname);

// ─── Write
int image_write(const IMAGE img, const char *dest_fname);

// ─── Print colored image with ansii escape sequences
int image_print_colored(const IMAGE img);

// ──────────────────────────────────────────────────────────
// ─── N E T P B M
// ──────────────────────────────────────────────────────────
void NETPBM_readprint_comments(const FILE *);
IMAGE NETPBM_read(const char *fname);

// ─── PGM
int PGM_write(IMAGE, const char *dest_fname);
IMAGE PGM_binarize(const IMAGE);
IMAGE PGM_invert(const IMAGE, const char *axis);
int PGM_print_colored(const IMAGE);
// int PGM_to_ascii(const IMAGE src, char *dest);

// ─── plain PGM
int plain_PGM_write(const uint8_t *src_data, const char *dest_fname);
int PLAIN_PGM_print_colored(const IMAGE);

// ─── PPM
int PPM_write(const uint8_t *src_data, const char *dest_fname);
int PPM_print_colored(const IMAGE);

// ─── plain PPM
int plain_PPM_write(const uint8_t *src_data, const char *dest_fname);
int PLAIN_PPM_print_colored(const IMAGE);

// int PGM_print_color(const uint8_t *buf, const int w, const int h, const int i);
// ──────────────────────────────────────────────────────────
// ─── T E X T
// ──────────────────────────────────────────────────────────

// ─── ASCII
// int ASCII_write(const unsigned char src, const char *dest_fname, const int width, const int height);

//
// ────────────────────────────────────────────────────────── IV ─────────────────────────────
//  :::::: A U X I L I A R Y   F U N C T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────
//
int swap(uint8_t *c1, uint8_t *c2);
int invert_array(uint8_t *array, int bufsize);
int cp(const uint8_t *src, uint8_t *dest, const int buf_size);
int forEach(uint8_t *buf, const int w, const int h, int (*func)(uint8_t *, int w, int h, int i));

#endif
