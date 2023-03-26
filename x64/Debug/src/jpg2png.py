import PIL
from PIL import Image
import sys

try:
    img_png = Image.open(sys.argv[1])
except:
    sys.stdout.write(' [E] There was an error during opening the image.')
    exit(0)

try:
    img_png.save(sys.argv[2])
    sys.stdout.write(' [•] Successfully Converted ' + sys.argv[3] + " to " + sys.argv[4] + "\n")
except:
    sys.stdout.write(' [E] There was an error during saving the image.')
    exit(0)