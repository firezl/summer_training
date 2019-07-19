#include<stdio.h>
#include"game.h"
#include<time.h>
#include<stdlib.h>

cell_t* board_cell(board_t* board, int row, int col)
{
	cell_t* cell;
	if (board == NULL || row >= board->rows || col >= board->cols || row < 0 || col < 0)
	{
		return NULL;
	}
	cell = &(board->cells[row * (board->cols) + col]);
	return cell;
}

board_t* create_board(int rows, int cols)
{
	board_t* map;
	if (rows <= 0 || cols <= 0)
	{
		return NULL;
	}
	map = (board_t*)malloc(sizeof(board_t));
	map->cells = (cell_t*)malloc(sizeof(cell_t) * rows * cols);
	int i, j;
	int tot = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			map->cells[tot] = CELL_OPEN;
			tot++;
		}
	}
	map->rows = rows; 
	map->cols = cols;
	return map;
}

void randomly_add_food(board_t* board, float probability)
{
	float a = rand() % 1000;
	if (a / 1000 < probability)
	{
		int flag = 0;
		while (flag == 0)
		{
			int i = rand() % ((board->cols) * (board->rows));
			if (board->cells[i] == CELL_OPEN)
			{
				board->cells[i] = CELL_FOOD;
				flag = 1;
			}
		}
	}
}

snake_t* create_snake(board_t* board, int row, int col, direction_t heading) {
	snake_t* snake;
	snake = (snake_t*)malloc(sizeof(snake_t));
	snake->head = (snake_node_t*)malloc(sizeof(snake_node_t));
	snake->head->row = row;
	snake->head->col = col;
	snake->tail = snake->head;
	snake->heading = heading;
	snake->growth = 0;
	snake->tail->next = NULL;
	if (board == NULL || row >= board->rows || col >= board->cols || row < 0 || col < 0)
	{
		return NULL;
	}
	else {
		board->cells[row * (board->cols) + col] = CELL_SNAKE;
		return snake;
	}
}

void destroy_snake(snake_t* snake) {
	snake_node_t* p = snake->head, * q = p->next;
	while (q != NULL)
	{
		free(p);
		p = q;
		q = q->next;
	}
	free(p);
    free(snake);
}

void destroy_board(board_t* board)
{
	free(board->cells);
	free(board);
}
//eswn
//// o f w s
int dx[] = { 0,1,0,-1 }, dy[] = { 1,0,-1,0 };
void update_snake_head(snake_t* snake, board_t* board, int growth_per_food)
{
	snake_node_t* p = (snake_node_t*)malloc(sizeof(snake_node_t));
	p->row = snake->head->row, p->col = snake->head->col;
	snake->head->row += dx[snake->heading];
	snake->head->col += dy[snake->heading];
	p->next = snake->head->next;
	snake->head->next = p;
	cell_t* temp = board_cell(board, snake->head->row, snake->head->col);
	if (*temp == CELL_FOOD)
	{
		snake->growth += growth_per_food;
	}
	*temp = CELL_SNAKE;
	if (snake->head == snake->tail)
	{
		snake->tail = snake->head->next;
	}
	return;
}

void set_direction(snake_t* snake, direction_t d)
{
	snake->heading = d;
	return;
}

void update_snake_tail(snake_t* snake, board_t* board)
{
	if (snake->growth == 0)
	{
    
		if (snake->head == NULL)
		{
			return;
		}
		if (snake->head == snake->tail)
		{
			return;
		}
		if (snake->head->next == snake->tail)
		{
            int rows=snake->tail->row;
            int cols=snake->tail->col;
            cell_t *cell=board_cell(board,rows,cols);
            *cell=CELL_OPEN;
			free(snake->tail);
			snake->tail = snake->head;
			snake->tail->next = NULL;
			return;
		}
		else
		{
            int rows=snake->tail->row;
            int cols=snake->tail->col;
            cell_t *cell=board_cell(board,rows,cols);
            *cell=CELL_OPEN;
			snake_node_t* temp = snake->head;
			while (temp->next != snake->tail)
			{
				temp = temp->next;
			}
			free(snake->tail);
			snake->tail = temp;
			temp->next = NULL;
		}
	}
	else
	{
		snake->growth--;
	}
	return;
}

int next_frame(game_t* cur_game)
{
	int tmp_row = cur_game->snake->head->row + dx[cur_game->snake->heading];
	int tmp_col = cur_game->snake->head->col + dy[cur_game->snake->heading];
	if (tmp_row < 0 || tmp_row >= cur_game->board->rows || tmp_col < 0 || tmp_col >= cur_game->board->cols)
	{
		return 1;
	}
	cell_t tmp_cell = *board_cell(cur_game->board, tmp_row, tmp_col);
	if (tmp_cell == CELL_SNAKE || tmp_cell == CELL_WALL)
	{
		return 1;
	}
	else
	{
		update_snake_head(cur_game->snake, cur_game->board, cur_game->growth_per_food);
		update_snake_tail(cur_game->snake, cur_game->board);
		randomly_add_food(cur_game->board, cur_game->food_probability);
		return 0;
	}
}
