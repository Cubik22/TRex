#include "main.h"

void initLivesState(SDL_Window **window, SDL_Renderer **renderer, InitState *state){
    state->font = TTF_OpenFont("files/fonts/OpenSans-Regular.ttf", 48);
    if (state->font == NULL){
        printf("ERROR: cannot load font\n");
    }
    state->nLives = 3;
    state->time = 0;
}

bool updateLivesState(InitState *state){
    bool fine = false;
    if (state->time < MAX_TIME){
        state->time++;
    } else {
        fine = true;
    }
    return fine;
}

void renderLivesState(SDL_Renderer *renderer, InitState *state){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    char punteggio[11];
    sprintf(punteggio, "%d", state->nLives);
    SDL_Surface *fontSurface = TTF_RenderText_Blended(state->font, punteggio, white);
    state->label = SDL_CreateTextureFromSurface(renderer, fontSurface);
    SDL_FreeSurface(fontSurface);
    SDL_Rect textRect = {WIDTH / 2, HEIGHT / 2, TEXT_WIDTH, TEXT_HEIGHT * 2};
    SDL_RenderCopy(renderer, state->label, NULL, &textRect);

    SDL_RenderPresent(renderer);
}

bool processEventsLivesState(SDL_Window *window, InitState *state){
    int xMouse = 0, yMouse = 0;

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_MOUSEMOTION){
            SDL_GetGlobalMouseState(&xMouse, &yMouse);
        }
    }
    //printf("Mouse x: %d Mouse y: %d\n", xMouse, yMouse);
}

void endLivesState(SDL_Window **window, SDL_Renderer **renderer, InitState *state){

}
