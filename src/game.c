// gaming hell yeah

#include "game.h"
#include "vector.h"
#include <math.h>
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

  Vector3 vertices[8] = {{{-1, -1, -1}}, {{1, -1, -1}}, {{1, 1, -1}},
                         {{-1, 1, -1}},  {{-1, -1, 1}}, {{1, -1, 1}},
                         {{1, 1, 1}},    {{-1, 1, 1}}};

  int edges[12][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
                      {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};

  float angle_x = ((float)SDL_GetTicks() / 1000.0F) * 0.5F;
  float angle_y = ((float)SDL_GetTicks() / 1000.0F) * 0.7F;
  float angle_z = ((float)SDL_GetTicks() / 1000.0F) * 0.3F;

  for (int i = 0; i < 8; i++) {
    float y_axis =
        (vertices[i].y * cosf(angle_x)) - (vertices[i].z * sinf(angle_x));

    float z_axis =
        (vertices[i].y * sinf(angle_x)) + (vertices[i].z * cosf(angle_x));

    vertices[i].y = y_axis;
    vertices[i].z = z_axis;

    float x_axis =
        (vertices[i].x * cosf(angle_y)) + (vertices[i].z * sinf(angle_y));
    z_axis = -(vertices[i].x * sinf(angle_y)) + (vertices[i].z * cosf(angle_y));

    vertices[i].x = x_axis;
    vertices[i].z = z_axis;

    x_axis = vertices[i].x * cosf(angle_z) - vertices[i].y * sinf(angle_z);
    y_axis = vertices[i].x * sinf(angle_z) + vertices[i].y * cosf(angle_z);
    vertices[i].x = x_axis;
    vertices[i].y = y_axis;

    float scale = 100.0F / (3.0F - vertices[i].z);
    vertices[i].x = vertices[i].x * scale + (float)game->window_width / 2;
    vertices[i].y = vertices[i].y * scale + (float)game->window_height / 2;
  }

  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
  for (int i = 0; i < 12; i++) {
    SDL_FPoint start = {vertices[edges[i][0]].x, vertices[edges[i][0]].y};
    SDL_FPoint end = {vertices[edges[i][1]].x, vertices[edges[i][1]].y};
    SDL_RenderLine(game->renderer, start.x, start.y, end.x, end.y);
  }

  SDL_RenderPresent(game->renderer);
}

void game_cleanup(Game *game) {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
}
