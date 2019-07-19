#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BEANVALUE -100
#define MONSTERVALUE 500
#define BEANSTEPCOST 10
#define MONSTERSTEPCOST 5
#define INF 0x3fffffff

int bfs(int *[100], int, int, int, int);
int calvalue(int , int);
int countpath(queue[], char[], int);
void countmap(state_map *);

int m, n; //game_state_t的m,n的值

typedef struct State_Map
{
    int map[100][100];     //储存墙的信息，有墙为1，没墙为0
    int monster[100][100]; //储存怪物的信息，有怪物为1，没怪物为0
    int bean[100][100];    //储存豆子的信息，有豆子为1，没豆子为0
} state_map;

typedef struct Point //不用管
{
    int x, y;
} point;

typedef struct Queue //不用管
{
    int x, y;
    int parent;
} queue;




int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int min = 0x3f3f3f3f;

int main()
{
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	state_map state__map;

	countmap(&state__map);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%d ", state__map.bean[i][j] + state__map.monster[i][j]);

        }
        printf("\n");
    }
	for (int i = 0; i < 100; i++)
	{
		printf("W");
	}
	
	int x = state.start_x;
	int y = state.start_y;
	int key;
	for (int i = 0; i < 4;i++) //比较权值最小
	{
		int tx = x + dx[i];
		int ty = y + dy[i];
		if (state__map.monster[tx][ty] + state__map.bean[tx][ty] < min && state__map.map[tx][ty] == 0) 
		{
			min = state__map.monster[tx][ty] + state__map.bean[tx][ty];
			key = i;
		}
	}
	
	//若权值同样小，以豆为基准
	if((min == state__map.monster[x + 1][y] + state__map.bean[x][y] || state__map.map[x + 1][y] == 1) &&
		(min == state__map.monster[x - 1][y] + state__map.bean[x][y] || state__map.map[x - 1][y] == 1) &&
		(min == state__map.monster[x][y] + state__map.bean[x][y - 1] || state__map.map[x][y - 1] == 1) &&
		(min == state__map.monster[x][y] + state__map.bean[x][y + 1] || state__map.map[x][y + 1] == 1))
		for (int i = 0; i < 4;i++) //比较豆值最小
		{
			int tempmin = 0x3f3f3f3f;
			int tx = x + dx[i];
			int ty = y + dy[i];
			if (state__map.monster[tx][ty] < tempmin && state__map.map[tx][ty] == 0)
			{
				tempmin = state__map.monster[tx][ty] + state__map.bean[tx][ty];
				key = i;
			}
		}

	switch (key)
	{
		case 0:printf("E");break;
		case 1:printf("W");break;
		case 2:printf("S");break;
		case 3:printf("N");break;
	}

}


int bfs(int *map[100], int sx, int sy, int gx, int gy)
{
	char dir[1000] = { 0 };
	queue q[1000];
	int f = 0, r = 0;
	int tempmap[n][m];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			tempmap[i][j] = map[i][j];
		}
	}
	q[r].x = sx;
	q[r].y = sy;
	q[r].parent = f;
	tempmap[sx][sy] = 1;
	r++;
	while (r != f)
	{
		int x = q[f].x;
		int y = q[f].y;
		f++;
		if (x == gx && y == gy)
		{
			return countpath(q, dir, f - 1);
		}
		if (tempmap[x + 1][y] == 0 && x + 1 >= 0 && x + 1 < n)
		{
			tempmap[x + 1][y] = 1;
			q[r].x = x + 1;
			q[r].y = y;
			q[r].parent = f - 1;
			dir[r] = 'S';
			r++;
		}
		if (tempmap[x][y + 1] == 0 && y + 1 >= 0 && y + 1 < m)
		{
			tempmap[x][y + 1] = 1;
			q[r].x = x;
			q[r].y = y + 1;
			q[r].parent = f - 1;
			dir[r] = 'E';
			r++;
		}
		if (tempmap[x - 1][y] == 0 && x - 1 >= 0 && x - 1 < n)
		{
			tempmap[x - 1][y] = 1;
			q[r].x = x - 1;
			q[r].y = y;
			q[r].parent = f - 1;
			dir[r] = 'N';
			r++;
		}
		if (tempmap[x][y - 1] == 0 && y - 1 >= 0 && y - 1 < m)
		{
			tempmap[x][y - 1] = 1;
			q[r].x = x;
			q[r].y = y - 1;
			q[r].parent = f - 1;
			dir[r] = 'W';
			r++;
		}
	}
	return -1;
}


int calvalue(int step, int flag)
{
	if (flag == 1)
	{
		//if (BEANVALUE - step * STEPCOST < 0)
			//return 0;
		//else
			return BEANVALUE + step * BEANSTEPCOST;
	}
	else
	{
		//if (MONSTERVALUE - step * STEPCOST < 0)
			//return 0;
		//else
		//{
			return MONSTERVALUE - step * MONSTERSTEPCOST;
        //}
	}
}

void countmap(state_map *map) //调用这个函数
{
	point p[200];
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map->bean[i][j] = 1)
			{
				p[count].x = i;
				p[count].y = j;
				count++;
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < m; k++)
			{
				if (map->map[j][k] == 1)
				{
                    map->bean[j][k] = 0;
                }
				else
				{
                    int tempvalue= bfs(map->map, p[i].x, p[i].y, j, k);
                    map->bean[j][k] += calvalue(tempvalue, 1);
				}
			}
		}
	}
	count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (map->monster[i][j] = 1)
			{
				p[count].x = i;
				p[count].y = j;
				count++;
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < m; k++)
			{
				if (map->map[j][k] == 1)
				{
					map->monster[j][k] = INF;
				}
				else
				{
					int tempvalue = bfs(map->map, p[i].x, p[i].y, j, k);
					map->monster[j][k] += calvalue(tempvalue, 0);
				}
			}
		}
	}
	return;
}

int countpath(queue q[], char dir[], int f)
{
	int count = 0;
	while (q[f].parent != f)
	{
		f = q[f].parent;
		count++;
	}
	return count;
}
