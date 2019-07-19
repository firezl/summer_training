#include "util.h"
#include <stdio.h>
#include <string.h>

int flag = 0;
int dx[4] = { 0, 0,-1,1 };
int dy[4] = { 1,-1, 0,0 };
int front, rear;
int visit[1000][1000];
game_state_t state;
int qiafood;
int foodnum;
int tx, ty;

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
			tx = po.x + dx[i];
			ty = po.y + dy[i];
			if (tx >= 0 && tx < state.n && ty >= 0 && ty < state.m && state.grid[tx][ty] != 1 && visit[tx][ty] != 1)
			{
				visit[tx][ty] = 1;
				switch (i) {
				case 0:pathc[rear] = 'E';break;
				case 1:pathc[rear] = 'W';break;
				case 2:pathc[rear] = 'N';break;
				case 3:pathc[rear] = 'S';break;
				}
				if (state.food[tx][ty] == 1)
				{
					path[rear] = front - 1;
					state.food[tx][ty] = 0;
					qiafood++;
					return;
				}
				enqueue(tx, ty);
				path[rear - 1] = front - 1;
			}
		}
	}

}

int inbfs(int x, int y)
{
	bfs(x, y);
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
	for (int i = top; i >= 0; i--)
	{
		printf("%c", zhan[i]);
	}
	rear = 0;
	front = 0;
	for(int i = 0; i < 1000; i++)
		for (int j = 0; j < 1000; j++)
		{
			visit[i][j] = 0;
		}
	return 0;
}

int main() {

	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	for(int i = 0; i < state.n; i++)
		for (int j = 0; j < state.m; j++)
		{
			if (state.food[i][j] == 1)
				foodnum++;
		}

	inbfs(state.start_x, state.start_y);
	while (qiafood != foodnum)
	{
		inbfs(tx, ty);
	}

	destroy(&state);
	return 0;
}

