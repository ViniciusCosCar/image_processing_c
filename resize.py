# https://pillow.readthedocs.io/en/stable/handbook/tutorial.html
from PIL import Image
import sys

fname_in = sys.argv[1]
fname_out = sys.argv[2]

# Abrir a imagem original
img = Image.open(fname_in)

w = int(input("New width: "))
h = int(input("New height: "))

# Redimensionar para WxH
# img_resized = img.resize((w, h), Image.Resampling.LANCZOS)
img_resized = img.resize((w, h))

# Salvar a nova imagem
img_resized.save(fname_out)

print(f"{fname_out} successfully created")
