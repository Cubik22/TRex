#ifndef GAMESTATE_H
#define GAMESTATE_H

void initGameState(SDL_Window *window, SDL_Renderer *renderer, Rex *rex);

void renderGameState(SDL_Renderer *renderer, Rex *rex, int lives);

bool updateGameState(Rex *rex);

bool processEventsGameState(SDL_Window *window, Rex *rex);

void endGameState(SDL_Window **window, SDL_Renderer **renderer, Rex *rex);

void drawTexture(SDL_Renderer *renderer, SDL_Texture *fullTexture, SDL_Rect *partTexture, SDL_Rect *rect, bool lines);

#endif // GAMESTATE_H_INCLUDED
