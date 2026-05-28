#ifndef AUXS_C
#define AUXS_C

#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

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
                swap(&array[i], &array[j]);

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
// ─── CANONICAL CHARACTER INPUT
// ──────────────────────────────────────────────────────────
int raw_getch(int fd)
{
        struct termios oldt, newt;
        tcgetattr(fd, &oldt); // Save existing attributes from existing interface
        newt = oldt;

        newt.c_lflag &= ~(ICANON | ECHO); // Turn off echo and canonical input

        tcsetattr(fd, TCSANOW, &newt);       // Apply changes immediatly
        dprintf(STDOUT_FILENO, "\033[?25l"); // Hide cursor

        char c;
        read(fd, &c, 1);

        tcsetattr(fd, TCSANOW, &oldt);       // Restore last attributes
        dprintf(STDOUT_FILENO, "\033[?25h"); // Show cursor

        return c;
}

#endif
