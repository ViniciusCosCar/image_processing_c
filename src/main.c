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
                        fprintf(stderr, "main: option not implemented yet\n");
                        // menu_convert();
                        break;

                case VIEW:
                        fprintf(stderr, "main: option not implemented yet\n");
                        // menu_view();
                        break;
                }
        };

        //      FREE ALLOCATED MEMORY
        //      ─────────────────────

        free(img.data);
}
