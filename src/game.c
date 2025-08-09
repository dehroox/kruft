#include "game.h"
#include <stdio.h>

int game_init(Game *game, const char *title, int width, int height) {
  if ((int)SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 0;
  }

  game->window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
  if (!game->window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 0;
  }

  game->renderer = SDL_CreateRenderer(game->window, NULL);
  if (!game->renderer) {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    return 0;
  }

  game->running = 1;
  game->window_width = width;
  game->window_height = height;

  return 1;
}

void game_handle_events(Game *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_EVENT_QUIT:
      game->running = 0;
      break;

    case SDL_EVENT_KEY_DOWN:
      switch (event.key.key) {
      case SDLK_ESCAPE:
        game->running = 0;
        break;
      default:
        break;
      }
      break;

    case SDL_EVENT_WINDOW_RESIZED:
      game->window_width = event.window.data1;
      game->window_height = event.window.data2;
      break;

    default:
      break;
    }
  }
}

void game_update(Game *game) { (void)game; }

void game_render(Game *game) {
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);

  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
  SDL_FRect rect = {100, 100, 50, 50};
  SDL_RenderFillRect(game->renderer, &rect);

  SDL_RenderPresent(game->renderer);
}

void game_cleanup(Game *game) {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
}
