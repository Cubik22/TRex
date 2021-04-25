#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#define WIDTH 900
#define HEIGHT 600
#define FRAME_PER_SECOND 60
#define UPDATE_PER_SECOND 5
#define GRAVITY 1
#define UP_SPEED 28
#define INITIAL_SPEED 10
#define INCREMENT_SPEED INITIAL_SPEED / 50
#define REX_WIDTH 50
#define REX_HEIGHT 80
#define GIU_WIDTH 80
#define GIU_HEIGHT 50
#define CACTUS_WIDTH 50
#define CACTUS_HEIGHT 80
#define BIRD_WIDTH 50
#define BIRD_HEIGHT 50
#define NUVOLETTA_WIDTH 75
#define NUVOLETTA_HEIGHT 50
#define TEXT_WIDTH 100
#define TEXT_HEIGHT 50
#define Y_PIANO HEIGHT - 50
#define X_REX 30
#define Y_REX Y_PIANO - REX_HEIGHT
#define X_GIU X_REX
#define Y_GIU Y_PIANO - GIU_HEIGHT
#define Y_CACTUS Y_PIANO - CACTUS_HEIGHT
#define Y_BIRD Y_PIANO - REX_HEIGHT - BIRD_HEIGHT / 2
#define Y_NUVOLETTA Y_PIANO - REX_HEIGHT - 2 * NUVOLETTA_HEIGHT
#define N_ENT 2
#define N_NUVOLETTE 2
#define MIN_DISTANCE 2 * WIDTH / 3
#define MAX_DISTANCE_DA_AGGIUNGERE WIDTH / 2
#define CLICK_BETWEEN_ANIMATION_SU 4
#define CLICK_BETWEEN_ANIMATION_GIU 6
#define CLICK_BETWEEN_ANIMATION_BIRD 10
#define MAX_TIME FRAME_PER_SECOND * 3

typedef struct{
    double x, y;

    int w, h;

    int state;                  //0 cactus 1 bird not used nuvoletta
    int animation;              //used just for bird
    int timeBetweenAnimation;   //used just for bird

    SDL_Rect *partTexture;
} Entity;

//struct that contains all useful parameters about game
typedef struct{
    double y;
    int state;                    //0 = normale 1 = salto 2 = sotto
    double timeSalto;
    float quantoSalto;
    int stateWidth, stateHeight;  //se è su o giu
    float speed;
    int punteggio;

    int animationSu, animationGiu;
    int timeBetweenAnimation;

    Entity e[N_ENT];
    Entity nuvolette[N_NUVOLETTE];
    int distanceE;

    SDL_Rect *partTexture;
    SDL_Texture *fullTexture;

    SDL_Texture *liveTexture;

    TTF_Font *font;
    SDL_Texture *label;
} Rex;

typedef struct{

    int nLives;
    unsigned int time;

    TTF_Font *font;
    SDL_Texture *label;

} InitState;

int randomInt(int max);

SDL_Rect *getPartRexSuUno();
SDL_Rect *getPartRexSuDue();
SDL_Rect *getPartRexSuTre();
SDL_Rect *getPartRexGiuUno();
SDL_Rect *getPartRexGiuDue();
SDL_Rect *getPartBirdUno();
SDL_Rect *getPartBirdDue();
SDL_Rect *getPartCactusDue();
SDL_Rect *getPartNuvoletta();

#endif // MAIN_H
