from curses import KEY_DOWN
import pygame, sys, time
from pygame.locals import *
import random
import ctypes
from ctypes import *

clock = pygame.time.Clock()
SIZEX = 1000
SIZEY = 1000
IMAGE_SNAKE_X = 40
IMAGE_SNAKE_Y = 40
IMAGE_APPLE_X = 40
IMAGE_APPLE_Y = 40
X = (SIZEY / IMAGE_SNAKE_X)
Y = (SIZEY / IMAGE_SNAKE_Y)
RAZMER = int(X) * int(Y)
MOVE = 1
FPS = 15
pos_X = (ctypes.c_int * RAZMER)() 
pos_Y = (ctypes.c_int * RAZMER)() 
# pos_X = [0] * RAZMER 
# pos_Y = [0] * RAZMER 



def move_snake(button,x,y):
    if button == K_LEFT:
        x -= MOVE
    elif button == K_RIGHT:
        x += MOVE
    elif button == K_UP:
        y -= MOVE 
    elif button == K_DOWN:
        y += MOVE
    return (x,y)

def add_value(x,y,last):
    global pos_X
    global pos_Y
    pos_X[last] = x 
    pos_Y[last] = y
    last += 1
    if last >= RAZMER:
        last = 0
    return last

def remove_value(first):
    first += 1
    if first >= RAZMER :
        first = 0
    return first
    
def eat_apple(x,y,applex,appley,first,last):
    stop = False
    if x == applex and y == appley :
        applex = random.randint(0,(SIZEX/IMAGE_APPLE_X)-1)
        appley = random.randint(0,(SIZEY/IMAGE_APPLE_Y)-1)
        while not stop:
            apple = eat_snake(applex,appley,first,last)
            if apple:
                applex = random.randint(0,(SIZEX/IMAGE_APPLE_X)-1)
                appley = random.randint(0,(SIZEY/IMAGE_APPLE_Y)-1)
            else :
                stop = True

    else :
        first = remove_value(first)
    
    return (applex,appley,first)

def out_field(x,y):

    return x >= SIZEX/IMAGE_SNAKE_X or x < 0 or y >= SIZEY/IMAGE_SNAKE_Y or y < 0


def eat_snake(x,y,first,last):

    if first <= last :
        for i in range(first,last) :
            if x == pos_X[i] and y == pos_Y[i] :
                return True
    else :
        for i in range(0,last) :
            if x == pos_X[i] and y == pos_Y[i] :
                return True
 
        for i in range(first,RAZMER) :
            if x == pos_X[i] and y == pos_Y[i] :
                return True

            
def drawning(first,last,screen,snake) :
    if first <= last :
        for i in range(first,last) :
            screen.blit(snake,(pos_X[i] * IMAGE_SNAKE_X,pos_Y[i] * IMAGE_SNAKE_Y))
    else :
        for i in range(0,last) :
            screen.blit(snake,(pos_X[i] * IMAGE_SNAKE_X,pos_Y[i] * IMAGE_SNAKE_Y))
        for i in range(first,RAZMER) :
            screen.blit(snake,(pos_X[i] * IMAGE_SNAKE_X,pos_Y[i] * IMAGE_SNAKE_Y))
                

def new():
    
    # Инициализация PyGame
    pygame.init()

    # Окно игры: размер, позиция
    gameScreen = pygame.display.set_mode((0,0))

    # Параметры окна
    size = [SIZEX, SIZEY]
    screen = pygame.display.set_mode(size)
    pygame.display.set_caption("Snake")
    gameScreen.fill((0,0,0))
    pygame.display.flip()
    rungame = False
    bg = pygame.image.load('trava.png').convert_alpha()
    bg = pygame.transform.scale(bg,(SIZEX,SIZEY))
    apple = pygame.image.load('apple.png').convert_alpha()
    apple = pygame.transform.scale(apple,(IMAGE_APPLE_X,IMAGE_APPLE_Y))
    snake = pygame.image.load('kvadrat.png').convert_alpha()
    snake = pygame.transform.scale(snake,(IMAGE_SNAKE_X,IMAGE_SNAKE_Y))
    applex = 2
    appley = 2
    x,y = 10, 10
    first = 0
    last = 0
    button = K_UP
    last = add_value(x,y,last)
    Eat = False
    while not rungame:
        
        pygame.display.update()

        screen.blit(bg,(0,0))
        screen.blit(apple,(applex * IMAGE_APPLE_X,appley * IMAGE_APPLE_Y))

        for event in pygame.event.get():
            if event.type == pygame.QUIT: 
                rungame = False
            if event.type == KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    quit()
                else:
                    button = event.key
            if event.type == KEYUP:
                button = event.key

        (x,y)= move_snake(button,x,y)

        rungame = out_field(x,y)

        Eat = eat_snake(x,y,first,last) 
        
        if Eat:
            break

        (applex,appley,first) = eat_apple(x,y,applex,appley,first,last)

        last = add_value(x,y,last)

        drawning(first,last,screen,snake)

        clock.tick(FPS)

if __name__ == '__main__':
    new()