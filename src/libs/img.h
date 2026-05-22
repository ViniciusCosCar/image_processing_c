#ifndef IMGS_H
#define IMGS_H

//
// ────────────────────────────────────────────────── I ──────────
//  :::::: E N U M S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────
//
enum Family
{
        NETPBM

} typedef Family;

enum Type
{
        PGM,
        plainPGM,

        PPM,
        plainPPM,

} typedef Type;
//
// ──────────────────────────────────────────────── II ─────────────
//  :::::: S T R U C T : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────
//
struct IMG
{
        const Family family;
        const Type type;
        const int pixelsize;

        unsigned char **buf;
        int width;
        int height;

} typedef IMG;

#endif
