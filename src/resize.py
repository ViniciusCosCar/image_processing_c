# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html
from PIL import Image
import sys

fname_in = sys.argv[1]
fname_out = sys.argv[2]

# Open original image
img = Image.open(fname_in)

w = int(input("New width: "))
h = int(input("New height: "))

# Resize to new width and height
img_resized = img.resize((w, h))

# Save new image with the name of the output file
img_resized.save(fname_out)

print(f"{fname_out} successfully created")
