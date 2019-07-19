#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "file.h"
#include "game.h"

void test_create_game(char *a)
{
	game_t* game = create_game(a);
	assert(game != NULL);
	assert(game->board != NULL);
	assert(game->snake != NULL);
	assert(game->board->cells[0] == CELL_WALL);
	assert(game->snake->head->next == NULL);
	destroy_game(game);
}


int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: ./main file_name");
		exit(-1);
	}

	test_create_game(argv[1]);
	return 0;
}
