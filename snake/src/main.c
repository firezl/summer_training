#include "file.h"
#include "ai.h"
#include "game.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  srand(time(0));
  if (argc != 2) {
    printf("Usage: ./main file_name");
    exit(-1);
  }
  game_t* game = create_game(argv[1]);
  while (1) {
    display(game);
    direction_t d = get_action(game);
    //  printf("out\n");
    set_direction(game->snake, d);
   //   printf("---\n");
    if (next_frame(game) != 0) {
      break;
    }
   //   printf("no sleep\n");
        unsigned timea = game->time_step * 1000000;
        usleep(timea);
  }
  destroy_game(game);
  return 0;
}
