#include <assert.h>
#include<stdio.h>
#include <stdlib.h>
#include "game.h"

void test_create_board() {
	board_t* board = create_board(5, 5);
	assert(board != NULL);
	assert(board_cell(board, 0, 0) != NULL);
	cell_t* cell = board_cell(board, 3, 2);
	assert(cell != NULL);
	assert(*cell == CELL_OPEN);
	assert(board_cell(board, -1, 0) == NULL);
	assert(board_cell(board, 0, 5) == NULL);
	assert(board_cell(board, 5, 5) == NULL);
	assert(board_cell(board, 4, 4) != NULL);
	destroy_board(board);
}


void test_create_snake() {
	game_t* game;
	game = (game_t*)malloc(sizeof(game_t));
	game->board = create_board(5, 5);
	game->snake = create_snake(game->board, 2, 3, EAST);
	game->food_probability = 0.3;
	game->time_step = 1;
	assert(game->snake != NULL);
	set_direction(game->snake, WEST);
	assert(game->snake->heading == WEST);
	assert(next_frame(game) == 0);
	destroy_board(game->board);
	destroy_snake(game->snake);
}

int main(int argc, char** argv) {
	test_create_board();
	test_create_snake();
	return 0;
}
