#include "main.h"

void drawTexture(SDL_Renderer *renderer, SDL_Texture *fullTexture, SDL_Rect *partTexture, SDL_Rect *rect, bool lines){
    int x = rect->x;
    int y = rect->y;
    int w = rect->w;
    int h = rect->h;
    if (lines){
        SDL_RenderDrawLine(renderer, x, y, x, y + h);
        SDL_RenderDrawLine(renderer, x + w, y, x + w, y + h);
        SDL_RenderDrawLine(renderer, x, y, x + w, y);
        SDL_RenderDrawLine(renderer, x, y + h, x + w, y + h);
    }
    SDL_RenderCopy(renderer, fullTexture, partTexture, rect);
}

void initRex(Rex *rex){
    rex->state = 0;
    rex->timeSalto = 0;
    rex->quantoSalto = 0;
    rex->animationSu = 1;
    rex->animationGiu = 1;
    rex->timeBetweenAnimation = 0;
    rex->speed = INITIAL_SPEED;
    rex->punteggio = 0;
    for (int i = 0; i < N_NUVOLETTE; i++){
        rex->nuvolette[i].y = Y_NUVOLETTA - randomInt(NUVOLETTA_HEIGHT * 2);
        rex->nuvolette[i].w = NUVOLETTA_WIDTH;
        rex->nuvolette[i].h = NUVOLETTA_HEIGHT;
        rex->nuvolette[i].partTexture = getPartNuvoletta();
    }
    rex->nuvolette[0].x = WIDTH;
    rex->nuvolette[1].x = WIDTH + WIDTH / 2;
    for (int i = 0; i < N_ENT; i++){
        rex->e[i].y = Y_CACTUS;
        rex->e[i].w = CACTUS_WIDTH;
        rex->e[i].h = CACTUS_HEIGHT;
        rex->e[i].partTexture = getPartCactusDue();
    }
    rex->e[0].x = WIDTH;
    rex->e[1].x = WIDTH + WIDTH / 2;
}

void initGameState(SDL_Window *window, SDL_Renderer *renderer, Rex *rex){
    SDL_Surface *fullSurface = IMG_Load("files/textures/fullSprite.png");
    if (fullSurface == NULL){
        printf("ERROR: cannot load full surface\n");
    }
    rex->fullTexture = SDL_CreateTextureFromSurface(renderer, fullSurface);
    SDL_FreeSurface(fullSurface);

    SDL_Surface *liveSurface = IMG_Load("files/textures/vita.png");
    if (fullSurface == NULL){
        printf("ERROR: cannot load vita surface\n");
    }
    rex->liveTexture= SDL_CreateTextureFromSurface(renderer, liveSurface);
    SDL_FreeSurface(liveSurface);

    rex->font = TTF_OpenFont("files/fonts/OpenSans-Regular.ttf", 48);
    if (rex->font == NULL){
        printf("ERROR: cannot load font\n");
    }
    initRex(rex);
}

void renderGameState(SDL_Renderer *renderer, Rex *rex, int lives){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    //draw nuvoletta
    for (int i = 0; i < N_NUVOLETTE; i++){
        SDL_Rect nuvolettaRect = {rex->nuvolette[i].x, rex->nuvolette[i].y, rex->nuvolette[i].w, rex->nuvolette[i].h};
        drawTexture(renderer, rex->fullTexture, rex->nuvolette[i].partTexture, &nuvolettaRect, false);
    }
    //draw entities
    for (int i = 0; i < N_ENT; i++){
        SDL_Rect eRect = {rex->e[i].x, rex->e[i].y, rex->e[i].w, rex->e[i].h};
        drawTexture(renderer, rex->fullTexture, rex->e[i].partTexture, &eRect, false);
    }
    //draw rex
    SDL_Rect rexRect = {X_REX, rex->y, rex->stateWidth, rex->stateHeight};
    drawTexture(renderer, rex->fullTexture, rex->partTexture, &rexRect, false);

    int qualeVita = lives;
    for (int i = 0; i < lives; i++, qualeVita--){
        int xl = WIDTH - 20 - 20 * qualeVita;
        int yl = 10;
        SDL_Rect livesRect = {xl, yl, 20, 20};
        drawTexture(renderer, rex->liveTexture, NULL, &livesRect, false);
    }

    //draw text
    SDL_Color black = {0, 0, 0, 0};
    char punteggio[11];
    sprintf(punteggio, "%d", rex->punteggio);
    SDL_Surface *fontSurface = TTF_RenderText_Blended(rex->font, punteggio, black);
    rex->label = SDL_CreateTextureFromSurface(renderer, fontSurface);
    SDL_FreeSurface(fontSurface);
    SDL_Rect textRect = {10, 10, TEXT_WIDTH, TEXT_HEIGHT};
    SDL_RenderCopy(renderer, rex->label, NULL, &textRect);

    SDL_RenderPresent(renderer);
}

//return true if collision happened
bool collision(Rex *rex){
    bool hit = false;
    for (int i = 0; i < N_ENT; i++){
        if (X_REX + rex->stateWidth >= rex->e[i].x && X_REX <= rex->e[i].x + rex->e[i].w &&
            rex->y + rex->stateHeight >= rex->e[i].y && rex->y <= rex->e[i].y + rex->e[i].h){
            hit = true;
        }
    }
    return hit;
}

bool updateGameState(Rex *rex){
    //printf("%f\n", delta);
    double delta = 1;
    bool hit = false;
    //update nuvoletta
    for (int i = 0; i < N_NUVOLETTE; i++){
        rex->nuvolette[i].x -= delta;
        if (rex->nuvolette[i].x < -NUVOLETTA_WIDTH){
            rex->nuvolette[i].x = WIDTH;
            rex->nuvolette[i].y = Y_NUVOLETTA - randomInt(NUVOLETTA_HEIGHT * 2);
        }
    }
    //update entities
    for (int i = 0; i < N_ENT; i++){
        rex->e[i].x -= rex->speed * delta;
        if (rex->e[i].state == 1){
            if (rex->e[i].timeBetweenAnimation >= CLICK_BETWEEN_ANIMATION_BIRD){
                if (rex->e[i].animation == 0){
                    rex->e[i].partTexture = getPartBirdDue();
                    rex->e[i].animation = 1;
                } else if (rex->e[i].animation == 1){
                    rex->e[i].partTexture = getPartBirdUno();
                    rex->e[i].animation = 0;
                }
                rex->e[i].timeBetweenAnimation = 0;
            } else {
                rex->e[i].timeBetweenAnimation++;
            }
        }
        if (rex->e[i].x < -rex->e[i].w){
            rex->speed += INCREMENT_SPEED;
            int ra = randomInt(1);
            if (ra == 0){
                rex->e[i].state = 0;
                rex->e[i].y = Y_CACTUS;
                rex->e[i].w = CACTUS_WIDTH;
                rex->e[i].h = CACTUS_HEIGHT;
                rex->e[i].partTexture = getPartCactusDue();
            } else {
                rex->e[i].state = 1;
                rex->e[i].animation = 0;
                rex->e[i].timeBetweenAnimation = 0;
                rex->e[i].y = Y_BIRD;
                rex->e[i].w = BIRD_WIDTH;
                rex->e[i].h = BIRD_HEIGHT;
                rex->e[i].partTexture = getPartBirdUno();
            }
            int quantoContaVelocita = 35;
            int distance = distanceBetweenEntities(&(rex->e[0]), &(rex->e[1])) - rex->speed * quantoContaVelocita;
            int randX = distance + MIN_DISTANCE + (rex->speed * quantoContaVelocita) +
                        randomInt(MAX_DISTANCE_DA_AGGIUNGERE + (rex->speed * quantoContaVelocita));
            rex->e[i].x = randX;
        }
    }
    //update rex
    rex->punteggio++;
    if (rex->state == 1 && rex->timeSalto > 10 && rex->y > Y_REX - REX_HEIGHT / 2){
        rex->y = Y_REX;
        rex->timeSalto = 0;
        rex->state = 0;
        rex->quantoSalto = 0;
    }
    if (rex->state == 1){
        rex->timeSalto += delta;
        //int velocita = UP_SPEED + rex->quantoSalto;
        int velocita = UP_SPEED;
        rex->y = Y_REX - velocita * rex->timeSalto + GRAVITY * rex->timeSalto * rex->timeSalto;
    }
    if (rex->state == 0){
        if (rex->timeBetweenAnimation >= CLICK_BETWEEN_ANIMATION_SU){
            if (rex->animationSu != 3){
                rex->animationSu++;
            } else {
                rex->animationSu = 1;
            }
            rex->timeBetweenAnimation = 0;
        } else {
            rex->timeBetweenAnimation++;
        }
        if (rex->animationSu == 1){
            rex->partTexture = getPartRexSuUno();
        } else if (rex->animationSu == 2){
            rex->partTexture = getPartRexSuDue();
        } else if (rex->animationSu == 3){
            rex->partTexture = getPartRexSuTre();
        }
        rex->y = Y_REX;
        rex->stateWidth = REX_WIDTH;
        rex->stateHeight = REX_HEIGHT;
    }
    if (rex->state == 2){
        if (rex->timeBetweenAnimation >= CLICK_BETWEEN_ANIMATION_GIU){
            if (rex->animationGiu == 1){
                rex->animationGiu = 2;
            } else {
                rex->animationGiu = 1;
            }
            rex->timeBetweenAnimation = 0;
        } else {
            rex->timeBetweenAnimation++;
        }
        if (rex->animationGiu == 1){
            rex->partTexture = getPartRexGiuUno();
        } else if (rex->animationGiu == 2){
            rex->partTexture = getPartRexGiuDue();
        }
        rex->y = Y_GIU;
        rex->stateWidth = GIU_WIDTH;
        rex->stateHeight = GIU_HEIGHT;
    }
    //check collision
    hit = collision(rex);
    return hit;
}

bool processEventsGameState(SDL_Window *window, Rex *rex){
    bool done = false;
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:{
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:{
                        done = true;
                    } break;
                    case SDLK_SPACE:{
                        if (rex->state == 0){
                            rex->state = 1;
                        }
                    } break;
                    case SDLK_DOWN:{

                    } break;
                }
            } break;
            case SDL_QUIT:{
                done = true;
            } break;
        }
    }

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_DOWN]){
        if(rex->state == 0){
            rex->state = 2;
        }
    } else {
        if(rex->state == 2){
            rex->state = 0;
        }
    }
    if (keyState[SDL_SCANCODE_SPACE]){
        if (rex->quantoSalto <= UP_SPEED / 5){
            rex->quantoSalto += 0.05;
        }
    }
    return done;
}

void endGameState(SDL_Window **window, SDL_Renderer **renderer, Rex *rex){
    SDL_DestroyTexture(rex->fullTexture);
    SDL_DestroyTexture(rex->label);
    TTF_CloseFont(rex->font);
}
