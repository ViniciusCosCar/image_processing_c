#ifndef IMGS_H
#define IMGS_H

#include <stdint.h>
#include <stdio.h>

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

enum Operation
{
        TRANSFORM = 1,
        CONVERT,
        VIEW

} typedef Operation;

static const char *CROSSED = "\033[9m";

struct IMAGE
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
static const char *types[] = {"ASCII", "PGM", "Plain PGM", "PPM", "Plain PPM", "PNG", "JPEG_TY", "UNKNOWN"};

//
// ──────────────────────────────────────────────── I ──────────
//  :::::: F - I/O : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────
//

// ──────────────────────────────────────────────────────────
// ─── F - I N P U T
// ──────────────────────────────────────────────────────────
// ─── Returns Family of provided file;
// return UNKNOWN_F if unable to detect
Family image_detect_family(const char *);
void NETPBM_readprint_comments(const FILE *);

//      IMAGE
//      ─────
// ───
// Returns an IMAGE out of provided file;
// returns NULLIMG otherwise
IMAGE image_read(const char *);

//      NETPBM
//      ──────
// ───
// Returns a NETPBM family IMAGE out of provided file;
// returns NULLIMG otherwise
IMAGE NETPBM_read(const char *);

//      ASCII
//      ─────
// ───
IMAGE ASCII_read(const char *);

// ──────────────────────────────────────────────────────────
// ─── F - O U T P U T
// ──────────────────────────────────────────────────────────

//      IMAGE
//      ─────
// ───
// Writes provided IMAGE to file; returns 1 if operation suceded and 0 otherwise
int image_write(const IMAGE, const char *fname);

//      NETPBM
//      ──────
// ─── PGM
int PGM_write(const IMAGE, const char *);

// ─── plain PGM (TODO)
int plain_PGM_write(const uint8_t *, const char *);

// ─── PPM (TODO)
int PPM_write(const uint8_t *, const char *);

// ─── plain PPM (TODO)
int plain_PPM_write(const uint8_t *, const char *);

//      ASCII
//      ─────
// ───
int ASCII_write(const IMAGE, const char *);

//
// ───────────────────────────────────────────────────────────────────── II ──────────
//  :::::: T R A N S F O R M A T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────
//

//      IMAGE
//      ─────
// ───
// Binarize IMAGE; returns binarized image in case of success, NULLIMG otherwise
IMAGE image_binarize(const IMAGE img);
// Invert; returns inverted image in case of success, NULLIMG otherwise
IMAGE image_invert(const IMAGE img, const char *fname);
// Print image; returns 1 in case of success, 0 otherwise
int image_print(const IMAGE);

//      NETPBM
//      ──────
// ─── PGM
IMAGE PGM_binarize(const IMAGE);
IMAGE PGM_invert(const IMAGE, const char *axis);
int PGM_print(const IMAGE);
// ─── plain PGM
int PLAIN_PGM_print(const IMAGE);
// ─── PPM
int PPM_print(const IMAGE);
// ─── plain PGM
int plain_PPM_print(const IMAGE);

//      ASCII
//      ─────
// ───
int ASCII_print(const IMAGE);

//
// ───────────────────────────────────────────────────────────────────────────── III ───────────
//  :::::: C O N V E R S I O N   F U N C T I O N S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────
//

//      IMAGE
//      ─────
// ───
IMAGE image_to_ascii(const IMAGE);

//      NETPBM
//      ──────
// ─── PGM
IMAGE PGM_to_ascii(const IMAGE);

//
// ────────────────────────────────────────────────────────────────────────────── V ──────────
//  :::::: A U X I L I A R S   F U N C T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────
//
int swap(uint8_t *c1, uint8_t *c2);
int invert_array(uint8_t *array, int bufsize);
int cp(const uint8_t *src, uint8_t *dest, const int buf_size);
int raw_getch(int fd);
//
// ───────────────────────────────────────────────────────────────────────────── VI ──────────
//  :::::: U I / M E N U   F U N C T I O N S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────────────
//
// ──────────────────────────────────────────────────────────
// ─── C O L O R S
// ──────────────────────────────────────────────────────────
static const char *WHITE = "\033[m\033[30;47m";
static const char *RED_FG = "\033[31m";
static const char *GREEN_FG = "\033[32m";
static const char *BLUE_FG = "\033[34m";
static const char *PURPLE_FG = "\033[35m";

static const char *RST = "\033[m";

static inline char *format_number(int n)
{
        static char res[8 * sizeof(int) + 3 * sizeof(char)]; // Unit + ' ' + '\0'

        if (n > 1000000)
                sprintf(res, "%d %c", n / 1000000, 'm');
        else if (n > 1000)
                sprintf(res, "%d %c", n / 1000, 'k');
        else
                sprintf(res, "%d  ", n);

        return res;
}

void clear();

Operation menu(IMAGE);
void menu_transform(const IMAGE img, char **argv);
void menu_convert(const IMAGE img, char **argv);
void menu_view(const IMAGE img);
void select_opt(char **opts, const int n_opts, const int selected);

#endif
