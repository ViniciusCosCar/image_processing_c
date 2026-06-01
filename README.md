# image_processing_c

# Plan
## Menu
|Status	| Task|
|-------|--------|
|🟧| Add a file selection menu so that user doesn't need indicate the file paths in the arguments |
|🟧| Add cursor suport|

## Image functions
|Status	| Task|
|-------|--------|
|🟧| Allow user to color ascii representation providing a certain gradiant, begining rgb -> final rgb, using ANSI escape codes: https://en.wikipedia.org/wiki/ANSI_escape_code|
|🟧| Allow transformation to be applied when receiving only one file path, then the transformed image will be created in the same directory with the same name plus a prefix that charactizes the transformation applieded
|🟧| Allow to perform transformations on directories; performing to each file in it. But for that, the transformation must receive to directory paths, one containing the sources, and a second indicating where the images will be created|
|🟧| Create image resize function |
|🟧| Add image rotation by a specified angle function|
 
|           |write()|binarize()|invert()|     print()   |resize()|image_to_pgm()|image_to_plain_pgm()|image_to_ppm()|image_to_plain_ppm()|image_to_ascii()|
|-----------|-------|----------|--------|---------------|--------|--------------|--------------------|--------------|--------------------|----------------|
| PGM       |  🟩   |    🟩    |   🟩   |       🟩      |   🟧   |              |          🟧        |      🟧      |         🟧         |       🟩       |
| Plain PGM |  🟧   |    🟧    |   🟧   |       🟧      |   🟧   |      🟧      |                    |      🟧      |         🟧         |       🟧       |
| PPM       |  🟧   |    🟧    |   🟧   |       🟧      |   🟧   |      🟧      |          🟧        |              |         🟧         |       🟧       |
| Plain PPM |  🟧   |    🟧    |   🟧   |       🟧      |   🟧   |      🟧      |          🟧        |      🟧      |                    |       🟧       |
| ASCII     |  🟩   |    🟧    |   🟧   |       🟩      |   🟧   |      🟧      |          🟧        |      🟧      |         🟧         |                |

## Description
*   🟧    if the task is to be implemented
*   🟨    if the task is in progress
*   🟩    if the task is finished

# To contributers
Please follow the project's format (.clang-format file) before making requests

#
![Image of a Good Boy](/input/sample.png "Woof!")
