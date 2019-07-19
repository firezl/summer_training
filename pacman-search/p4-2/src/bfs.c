#include "bfs.h"

void printpath(queue q[], char dir[], int f)
{
    char temppath[1000] = {0};
    int count = 0;
    while (q[f].parent != f)
    {
        temppath[count] = dir[f];
        f = q[f].parent;
        count++;
    }
    int i = count - 1;
    printf("%c", temppath[i]);
    return;
}

int bfs(game_state_t* state, int sx, int sy, int gx, int gy, int flag)
{
    char dir[1000] = {0};
    queue q[1000];
    int f = 0, r = 0;
    int tempmap[100][100];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            tempmap[i][j] = state->grid[i][j];
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
        if (x == gx && y == gy && flag == 0)
        {
            return countpath(q, dir, f - 1);
        }
        if (x == gx && y == gy && flag == 1)
        {
            printpath(q, dir, f - 1);
            return 1;
        }
		if(state->food[x][y]==1&&flag==2)
		{
			printpath(q, dir, f - 1);
            return 2;
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
