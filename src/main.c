#include "game.h"
#include <stdio.h>

int main(void) {
  Game game;

  if (!game_init(&game, "Kruft", 800, 600)) {
    perror("Failed to initialize!\n");
    return 1;
  }

  while (game.running) {
    game_handle_events(&game);
    game_update(&game);
    game_render(&game);

    SDL_Delay(16);
  }

  game_cleanup(&game);
  return 0;
}
