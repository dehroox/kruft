#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int running;
  int window_width;
  int window_height;
} Game;

int game_init(Game *game, const char *title, int width, int height);
void game_handle_events(Game *game);
void game_update(Game *game);
void game_render(Game *game);
void game_cleanup(Game *game);

#endif
