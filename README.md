# image_processing_c

# Plan
|Status	| Task|
|-------|--------|
|🟧| Allow user to color ascii representation providing a certain gradiant, begining rgb -> final rgb, maybe using ANSI escape codes: https://en.wikipedia.org/wiki/ANSI_escape_code              |
|🟧| Create C image resize function                                                                    |
|🟧| Add suport for ppm images (read🟧,write🟧,binarize🟧,invert🟧,visualization🟧,ascii visualization and file creation🟧)|
|🟧| Create converter for most common image formats: png, jpeg, etc                                    |
|🟧| Add image rotation by a specified angle                                                           |
|🟩| Allow colored visualization of pgm                                                                |
|🟩| Allow invertion according a specified axis: x, y or xy                                            |

## Description
*   🟧    if the task is to be implemented
*   🟨    if the task is in progress
*   🟩    if the task is finished

# Overall project structure
## Structure of an image
*   const Family family
*   const Type type 
*   const int pixelsize

*   unsigned char **buf;

*   int width;
*   int height;

You might be thinking: "Why should the pgm object, for example, have a double array for the image, if each element could just contain the level of grey at that point?"
And the answer: "Because it is easier to generalize functions this way, like the invert_img() function"


# To contributers
Please follow the project's format (.clang-format file) before making requests

#
![Image of a Good Boy](/input/woof2.png "Woof!")
