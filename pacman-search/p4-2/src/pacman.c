#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int flag = 0;
int dx[4] = { 0, 0,-1,1 };
int dy[4] = { 1,-1, 0,0 };
int front, rear;
int visit[1000][1000];
game_state_t state;

typedef struct node {
	int x;
	int y;
}node;
node queue[10000];

void enqueue(int x, int y)
{
	queue[rear].x = x;
	queue[rear].y = y;
	rear++;
}
node dequeue()
{
	return queue[front++];
}
int path[1000];
char pathc[1000];
void bfs(int x, int y)
{
	enqueue(x, y);
	visit[x][y] = 1;
	while (front != rear)
	{
		node po = dequeue();
		for (int i = 0;i < 4;i++) {
			int tx = po.x + dx[i];
			int ty = po.y + dy[i];
			if (tx >= 0 && tx < state.n && ty >= 0 && ty < state.m && state.grid[tx][ty] != 1 && visit[tx][ty] != 1)
			{
				visit[tx][ty] = 1;
				switch (i) {
				case 0:pathc[rear] = 'E';break;
				case 1:pathc[rear] = 'W';break;
				case 2:pathc[rear] = 'N';break;
				case 3:pathc[rear] = 'S';break;
				}
				int flagcap = 0;
				for (int i = 0; i < state.num_ghosts; i++)
				{
					if (state.timer[i] == 0)
						flagcap = 1;
				}
				if (state.num_capsule != 0)
				{
					for (int i = 0; i < state.num_capsule; i++)
						if (tx == state.capsule_x[i] && ty == state.capsule_y[i] && flagcap == 1)
						{
							path[rear] = front - 1;
							flag = 1;
							return;
						}
				}
				
					if (state.food[tx][ty] == 1)
					{
						path[rear] = front - 1;
						flag = 1;
						return;
					}
				enqueue(tx, ty);
				path[rear - 1] = front - 1;
			}
		}
	}
}

int main() {

	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
		for (int i = 0;i < state.num_ghosts;i++)
	{
		if (state.timer[i] <= 4)
		{
			state.grid[state.ghost_x[i]][state.ghost_y[i]] = 1;
			state.grid[state.ghost_x[i] + 1][state.ghost_y[i]] = 1;
			state.grid[state.ghost_x[i] - 1][state.ghost_y[i]] = 1;
			state.grid[state.ghost_x[i]][state.ghost_y[i] + 1] = 1;
			state.grid[state.ghost_x[i]][state.ghost_y[i] - 1] = 1;
			state.food[state.ghost_x[i]][state.ghost_y[i]] = 0;
			state.food[state.ghost_x[i] + 1][state.ghost_y[i]] = 0;
			state.food[state.ghost_x[i] - 1][state.ghost_y[i]] = 0;
			state.food[state.ghost_x[i]][state.ghost_y[i] + 1] = 0;
			state.food[state.ghost_x[i]][state.ghost_y[i] - 1] = 0;
		}
	}

	for (int i = 0;i < state.num_ghosts;i++)
		if(state.timer[i] > 5)
		state.food[state.ghost_x[i]][state.ghost_y[i]] = 1;

	for (int i = 0; i < state.num_capsule;i++)
	{
		state.food[state.capsule_x[i]][state.capsule_y[i]] = 1;
	}

	bfs(state.start_x, state.start_y);

	if (flag != 1)
		rear--;
	int i = rear;
	char zhan[10000];
	int top = 0;

	while (i != 0)
	{
		zhan[top] = pathc[i];
		top++;
		i = path[i];
	}
	top--;
	if(flag == 1)
	printf("%c", zhan[top]);

	//system("PAUSE");
	destroy(&state);
	return 0;
}
