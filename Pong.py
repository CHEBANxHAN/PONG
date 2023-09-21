import pygame as pg
from pygame.mixer import music as mg
pg.init()
W = 1000
H = 500
sc = pg.display.set_mode((W, H), pg.SCALED)
pg.display.set_caption("Pong")
f1 = pg.font.Font("Data/pix.ttf", 24)
f2 = pg.font.Font("Data/pix.ttf", 24)

GREEN = (0, 255, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLACK = (0, 0, 0)
FPS = 60
clock = pg.time.Clock()
speed = 5

x1 = 950
y1 = 0

x2 = 20
y2 = 0

xb = 475
yb = 200

velX = 3
velY = 3

score1 = 0
score2 = 0
        
while True:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            exit()
    keys = pg.key.get_pressed()
    if keys[pg.K_p]:
        y1 -= speed
    elif keys[pg.K_l]:
        y1 += speed

    elif keys[pg.K_w]:
        y2 -= speed
    elif keys[pg.K_s]:
        y2 += speed


    if y1 < 0:
        y1 = 0

    elif y1 > H - 200:
        y1 = H - 200

    elif y2 < 0:
        y2 = 0

    elif y2 > H - 200:
        y2 = H - 200

    xb += velX
    yb += velY

    if xb < 0 or xb > W - 50:
        mg.load("Data/loose.mp3")
        mg.play(0)
        exit()
    elif yb < 0 or yb > H - 50:
        velY = -velY
        mg.load("Data/sound.mp3")
        mg.play(0)

    elif xb + 50 > x1 and yb > y1 and yb + 50 < y1 + 200:
        velX = -velX
        score1 += 1
        mg.load("Data/sound.mp3")
        mg.play(0)

    elif xb < x2 + 30 and yb > y2 and yb + 50 < y2 + 200:
        velX = -velX
        score2 += 1
        mg.load("Data/sound.mp3")
        mg.play(0)


    sc_text1 = f1.render(f"{score2}", 1, WHITE, BLACK)
    pos1 = sc_text1.get_rect(center=(W//4, 30))
    sc_text2 = f2.render(f"{score1}", 1, WHITE, BLACK)
    pos2 = sc_text2.get_rect(center=(3*W//4, 30))
    sc.fill(BLACK)
    sc.blit(sc_text2, pos2)
    sc.blit(sc_text1, pos1)
    pl1 = pg.draw.rect(sc, WHITE, (x1,y1, 30, 200))
    pl2 = pg.draw.rect(sc, WHITE, (x2,y2, 30, 200))
    r = pg.draw.rect(sc, WHITE, (485,0, 30, 500))
    ball = pg.draw.rect(sc, WHITE, (xb,yb, 50, 50))
    pg.display.update()

    clock.tick(FPS)

