# image_processing_c

# Plan
## Menu
|Status	| Task|
|-------|--------|
|🟧| Add a file selection menu so that user doesn't need indicate the file paths in the arguments |
|🟨| Use ansii escape sequances and termios.h to redesign the menu and have more control on the way the user interact with the menu, like turning input echo off, enter-less input or cursor option selection: Be creative and have fun! =)|
|🟩| Menu should start asking if user wants to 1: Apply an image transformation (like resize() or binarize()), 2: Convert (Should show only useful options, if input image is ascii, doesn't make sense to ask if the user would like to convert to ascii! Ask if they would like to convert to pgm or any other), 3: View (image_print())

## Image functions
|Status	| Task|
|-------|--------|
|🟧| Allow user to color ascii representation providing a certain gradiant, begining rgb -> final rgb, using ANSI escape codes: https://en.wikipedia.org/wiki/ANSI_escape_code|
|🟧| Create C image resize function |
|🟧| Add image rotation by a specified angle|
 
|           |write()|binarize()|invert()|     print()   |resize()|image_to_pgm()|image_to_plain_pgm()|image_to_ppm()|image_to_plain_ppm()|image_to_ascii()|
|-----------|-------|----------|--------|---------------|--------|--------------|--------------------|--------------|--------------------|----------------|
| PGM       |  🟩   |    🟩    |   🟩   |       🟩      |   🟩   |              |          🟧        |      🟧      |         🟧         |       🟩       |
| Plain PGM |  🟧   |    🟧    |   🟧   |       🟧      |   🟩   |      🟧      |                    |      🟧      |         🟧         |       🟧       |
| PPM       |  🟧   |    🟧    |   🟧   |       🟧      |   🟩   |      🟧      |          🟧        |              |         🟧         |       🟧       |
| Plain PPM |  🟧   |    🟧    |   🟧   |       🟧      |   🟩   |      🟧      |          🟧        |      🟧      |                    |       🟧       |
| ASCII     |  🟩   |    🟧    |   🟧   |       🟩      |   🟩   |      🟧      |          🟧        |      🟧      |         🟧         |                |

## Description
*   🟧    if the task is to be implemented
*   🟨    if the task is in progress
*   🟩    if the task is finished

# To contributers
Please follow the project's format (.clang-format file) before making requests

#
![Image of a Good Boy](/input/sample.png "Woof!")
