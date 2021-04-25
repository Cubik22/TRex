#define SDL_MAIN_HANDLED

#include "main.h"
#include "gameState.h"

/*cose da aggiungere: schermata di start e fine*/

//rect used for delimiting part from fullTexture
SDL_Rect partRexSuConTerreno = {39, 3, 44, 47};
SDL_Rect partRexSuUno = {675, 1, 46, 47};
SDL_Rect partRexSuDue = {764, 1, 46, 47};
SDL_Rect partRexSuTre = {808, 1, 46, 47};
SDL_Rect partRexGiuUno = {940, 14, 60, 38};
SDL_Rect partRexGiuDue = {998, 14, 60, 38};
SDL_Rect partCactusDue = {227, 1, 35, 37};
SDL_Rect partBirdUno = {133, 6, 48, 36};
SDL_Rect partBirdDue = {181, 6, 48, 36};
SDL_Rect partNuvoletta = {83, 0, 50, 20};

SDL_Rect *getPartRexSuUno(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 675;
    (*cac).y = 1;
    (*cac).w = 46;
    (*cac).h = 47;
    return cac;
}
SDL_Rect *getPartRexSuDue(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 764;
    (*cac).y = 1;
    (*cac).w = 46;
    (*cac).h = 47;
    return cac;
}
SDL_Rect *getPartRexSuTre(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 808;
    (*cac).y = 1;
    (*cac).w = 46;
    (*cac).h = 47;
    return cac;
}
SDL_Rect *getPartRexGiuUno(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 940;
    (*cac).y = 14;
    (*cac).w = 60;
    (*cac).h = 38;
    return cac;
}
SDL_Rect *getPartRexGiuDue(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 998;
    (*cac).y = 14;
    (*cac).w = 60;
    (*cac).h = 38;
    return cac;
}
SDL_Rect *getPartBirdUno(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 133;
    (*cac).y = 6;
    (*cac).w = 48;
    (*cac).h = 36;
    return cac;
}
SDL_Rect *getPartBirdDue(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 181;
    (*cac).y = 6;
    (*cac).w = 48;
    (*cac).h = 36;
    return cac;
}
SDL_Rect *getPartCactusDue(){
    SDL_Rect *cac = malloc(sizeof(SDL_Rect));
    (*cac).x = 227;
    (*cac).y = 1;
    (*cac).w = 35;
    (*cac).h = 37;
    return cac;
}
SDL_Rect *getPartNuvoletta(){
    SDL_Rect *nuv = malloc(sizeof(SDL_Rect));
    (*nuv).x = 83;
    (*nuv).y = 0;
    (*nuv).w = 50;
    (*nuv).h = 20;
    return nuv;
}

//return random int between [0, max]
int randomInt(int max){
    int r = (int) ((double)rand() / (double)RAND_MAX * (double)(max + 1));
    return r;
}

//return distance in absolute value between two entities
int distanceBetweenEntities(Entity *e1, Entity *e2){
    int distance = e1->x - e2->x;
    if (distance < 0){
        distance = -distance;
    }
    return distance;
}

//used for drawing part of a texture
//last parameter used for drawing lines delimiting object



void loop(){
    bool done = false;
    int gameState = 0;
    Rex rex;
    InitState initState;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("T-Rex", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initLivesState(&window, &renderer, &initState);
    initGameState(window, renderer, &rex);

    unsigned int start = SDL_GetTicks();
    unsigned int prev = start;

    while(!done){
        unsigned int now = SDL_GetTicks();
        unsigned int diff = now - prev;
        if (diff >= (1000 / FRAME_PER_SECOND)){
            if (gameState == 1){
                done = processEventsGameState(window, &rex);
                if(updateGameState(&rex)){
                    gameState = 0;
                    initState.nLives--;
                    if (initState.nLives <= 0){
                        done = true;
                    }
                    initRex(&rex);
                }
                renderGameState(renderer, &rex, initState.nLives);
            } else if (gameState == 0){
                processEventsLivesState(window, &initState);
                if (updateLivesState(&initState)){
                    gameState = 1;
                    initState.time = 0;
                }
                renderLivesState(renderer, &initState);
            }
            prev = now;
        }
    }

    endGameState(&window, &renderer, &rex);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv){
    loop();
    return 0;
}
