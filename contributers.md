# To contributers

## Project's structure
*   main.c: Program's control unit; responsible for detecting the type of path given (file or directory), presenting the main selection menu, getting input and choosing the next operation to execute (exit, image transformation, image conversion or image visualization)
*   Transformation functions: binarize(),resize() and invert() are all examples of transformation functions;
        IMAGE <name of type of image/format>_<name of transformation>(const IMAGE);
*   Conversion functions:
        IMAGE <name of type of image/format>_to_<name of image/format to convert>(const IMAGE);
*   Visualization:
        void <name of type of image/format>_<'f' if it is for files,'d' if it is for directories>print(const IMAGE);
