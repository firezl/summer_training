#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "game.h"

game_t *create_game(const char *file_name)
{
	FILE *fp;
	fp = fopen(file_name, "r");
	int num_row, num_col;
	game_t * game;
	game = (game_t *)malloc(sizeof(game_t));
	fscanf(fp, "%d %d", &num_row, &num_col);
	game->board = create_board(num_row, num_col);
	fscanf(fp, "%f %f %d", &game->time_step, &game->food_probability, &game->growth_per_food);
	for (int i = 0;i < num_row * num_col;i++)
	{
		char ch;
		char a[2];
		fscanf(fp, "%1s", a);
		ch = a[0];
		switch (ch)
		{
		case 'X':game->board->cells[i] = CELL_WALL;break;
		case '-':game->board->cells[i] = CELL_OPEN;break;
		case 'W':game->board->cells[i] = CELL_SNAKE;break;
		case 'E':game->board->cells[i] = CELL_SNAKE;break;
		case 'S':game->board->cells[i] = CELL_SNAKE;break;
		case 'N':game->board->cells[i] = CELL_SNAKE;break;
		default:break;
		}
		int fku=i%num_col;
		//if(fku!=0)fku--;
		//else fku=num_col-1;
		if (ch == 'W')
			game->snake = create_snake(game->board, i/num_col, i%num_col, WEST);
		if (ch == 'S')
		{
			game->snake = create_snake(game->board, i/num_col, i%num_col, SOUTH);
		}
		if (ch == 'E')
			game->snake = create_snake(game->board, i/num_col, i%num_col, EAST);
		if (ch == 'N')
			game->snake = create_snake(game->board, i/num_col, i%num_col,NORTH);
	}
	fclose(fp);
	return game;
}

void destroy_game(game_t *game)
{
	destroy_board(game->board);
	destroy_snake(game->snake);
	free(game);
}
