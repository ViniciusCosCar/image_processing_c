#ifndef AUXS_C
#define AUXS_C

#include <stdint.h>
#include <stdlib.h>

// ──────────────────────────────────────────────────────────
// ─── INVERT TWO uint8_t
// ──────────────────────────────────────────────────────────
int swap(uint8_t *c1, uint8_t *c2)
{
        if (!c1 || !c2)
                return 0;

        uint8_t aux = *c1;
        *c1 = *c2;
        *c2 = aux;

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── INVERT ARRAY
// ──────────────────────────────────────────────────────────
int invert_array(uint8_t *array, int bufsize)
{
        if (array == NULL || bufsize < 0)
                return 0;

        for (int i = 0, j = bufsize - 1; i < j; i++, j--)
                swap(&array[i++], &array[j--]);

        return 1;
}
// ──────────────────────────────────────────────────────────
// ─── COPY SOURCE ARRAY TO DESTINATION
// ──────────────────────────────────────────────────────────
int cp(const uint8_t *src, uint8_t *dest, const int buf_size)
{
        if (src == NULL || dest == NULL || buf_size < 0)
                return 0;

        for (int i = 0; i < buf_size; i++)
                dest[i] = src[i];

        return 1;
}

// ──────────────────────────────────────────────────────────
// ───
// ──────────────────────────────────────────────────────────
int forEach(uint8_t *buf, const int w, const int h, int (*func)(uint8_t *, int w, int h, int i))
{
        if (buf == NULL || w < 0 || h < 0)
                return 0;

        int res = 0;
        int datawidth = w * h;
        for (int i = 0; i < datawidth; i++)
                res += func(buf, w, h, i);

        return res;
}

#endif
