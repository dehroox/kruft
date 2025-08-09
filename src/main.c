#include <SDL3/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void) {
  if ((int)SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("SDL3 Test", WINDOW_WIDTH,
                                        WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
  if (!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  int running = 1;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = 0;
      }
    }

    SDL_SetRenderDrawColor(SDL_GetRenderer(window), 0, 0, 0, 255);
    SDL_RenderClear(SDL_GetRenderer(window));
    SDL_RenderPresent(SDL_GetRenderer(window));
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
