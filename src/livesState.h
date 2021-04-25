#ifndef LIVESSTATE_H_INCLUDED
#define LIVESSTATE_H_INCLUDED

void initLivesState(SDL_Window **window, SDL_Renderer **renderer, InitState *state);

void renderLivesState(SDL_Renderer *renderer, InitState *state);

bool updateLivesState(InitState *state);

bool processEventsLivesState(SDL_Window *window, InitState *state);

void endLivesState(SDL_Window **window, SDL_Renderer **renderer, InitState *state);

#endif // LIVESSTATE_H_INCLUDED
