#include <stdlib.h>

#include "lib/UI/UI.h"
#include "lib/superIMG.h"

int main(int argc, char **argv)
{
        //      READ PGM FILE TO ARRAY
        //      ──────────────────────
        const IMAGE img = image_read(argv[1]);

        //      SELECT OPERATIONS TO PERFORM
        //      ────────────────────────────
        while (1)
        {
                switch (menu())
                {
                case TRANSFORM:
                        menu_transform(img, argv);
                        break;

                case CONVERT:
                        menu_convert(img, argv);
                        break;

                case VIEW:
                        image_print(img);
                        while (getchar() != '\n')
                                ;
                        break;
                }
        };

        //      FREE ALLOCATED MEMORY
        //      ─────────────────────

        free(img.data);
}
