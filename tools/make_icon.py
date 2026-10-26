"""Draws the icon of rewrite: a stylus drawing an integral sign.
Writes tools/rewrite.ico (16..256 px) and tools/rewrite.png (256 px).
Needs Pillow:  python tools/make_icon.py"""
import math, os
from PIL import Image, ImageDraw

S = 1024                     # drawn large, scaled down (smooth edges)
img = Image.new('RGBA', (S, S), (0, 0, 0, 0))
d = ImageDraw.Draw(img)

# background: a rounded square, deep blue
d.rounded_rectangle((40, 40, S - 40, S - 40), radius=190, fill=(28, 52, 110, 255))

def bezier(p, n=400):
    """points of a cubic Bezier curve"""
    out = []
    for k in range(n + 1):
        t = k / n
        a, b, c, e = (1 - t) ** 3, 3 * t * (1 - t) ** 2, 3 * t * t * (1 - t), t ** 3
        out.append((a * p[0][0] + b * p[1][0] + c * p[2][0] + e * p[3][0],
                    a * p[0][1] + b * p[1][1] + c * p[2][1] + e * p[3][1]))
    return out

def stroke(points, width0, width1, color):
    """a line of round dots whose width changes along it (as with a pen)"""
    n = len(points)
    for k, (x, y) in enumerate(points):
        t = k / (n - 1)
        w = width0 + (width1 - width0) * math.sin(math.pi * t) if width1 else width0
        d.ellipse((x - w / 2, y - w / 2, x + w / 2, y + w / 2), fill=color)

# the integral sign: a slanted S, thin at the ends, thick in the middle
top = bezier([(690, 170), (560, 60), (470, 260), (480, 470)])
bottom = bezier([(480, 470), (490, 690), (420, 900), (300, 820)])
white = (245, 245, 240, 255)
stroke(top, 30, 84, white)
stroke(bottom, 30, 84, white)
for (x, y) in ((690, 170), (300, 820)):          # the round ends
    d.ellipse((x - 26, y - 26, x + 26, y + 26), fill=white)

# the stylus: from the lower right, its tip at the lower end of the integral
tip = (300, 820)
ang = math.radians(-14)                            # direction tip -> back end
ux, uy = math.cos(ang), math.sin(ang)              # along the pen
vx, vy = -uy, ux                                   # across
def P(a, b):                                       # a along, b across
    return (tip[0] + a * ux + b * vx, tip[1] + a * uy + b * vy)
gold, dark, grey = (236, 170, 50, 255), (60, 60, 70, 255), (200, 205, 215, 255)
d.polygon([P(0, 0), P(60, -22), P(60, 22)], fill=dark)                    # point
d.polygon([P(60, -22), P(115, -34), P(115, 34), P(60, 22)], fill=grey)    # cone
d.polygon([P(115, -34), P(540, -34), P(540, 34), P(115, 34)], fill=gold)  # body
d.polygon([P(540, -34), P(590, -34), P(590, 34), P(540, 34)], fill=dark)  # end cap
cx, cy = P(590, 0)
d.ellipse((cx - 34, cy - 34, cx + 34, cy + 34), fill=dark)

here = os.path.dirname(os.path.abspath(__file__))
big = img.resize((256, 256), Image.LANCZOS)
big.save(os.path.join(here, 'rewrite.png'))
big.save(os.path.join(here, 'rewrite.ico'),
         sizes=[(16, 16), (24, 24), (32, 32), (48, 48), (64, 64), (128, 128), (256, 256)])
print('written: tools/rewrite.ico, tools/rewrite.png')
