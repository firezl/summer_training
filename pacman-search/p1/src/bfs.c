#include "util.h"
#include <stdio.h>
#include <string.h>

char temppath[1000];

typedef struct Queue
{
    int x, y;
    int parent;
} queue;

void printpath(queue q[],char dir[],int f)
{
    int count = 0;
    while (q[f].parent != f)
    {
        temppath[count] = dir[f];
        f = q[f].parent;
        count++;
    }
    for (int i = count-1; i >=0;i--)
    {
        printf("%c", temppath[i]);
    }
    return;
}

int main()
{
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here
    queue q[1000];
    char dir[1000] = {0};
    int f = 0;
    int r = 0;
    q[r].x = state.start_x;
    q[r].y = state.start_y;
    q[r].parent = f;
    state.grid[q[r].x][q[r].y] = 1;
    r++;
    while (f != r)
    {
        int x = q[f].x;
        int y = q[f].y;
        f++;
        if(x==state.goal_x&&y==state.goal_y)
        {
            printpath(q, dir, f - 1);
            break;
        }
        if(state.grid[x+1][y]==0&&x+1>=0&&x+1<state.n)
        {
            state.grid[x + 1][y] = 1;
            q[r].x = x + 1;
            q[r].y = y;
            q[r].parent = f - 1;
            dir[r] = 'S';
            r++;
        }
        if(state.grid[x][y+1]==0&&y+1>=0&&y+1<state.m)
        {
            state.grid[x][y + 1] = 1;
            q[r].x = x;
            q[r].y = y + 1;
            q[r].parent = f - 1;
            dir[r] = 'E';
            r++;
        }
        if(state.grid[x-1][y]==0&&x-1>=0&&x-1<state.n)
        {
            state.grid[x - 1][y] = 1;
            q[r].x = x - 1;
            q[r].y = y;
            q[r].parent = f - 1;
            dir[r] = 'N';
            r++;
        }
        if(state.grid[x][y-1]==0&&y-1>=0&&y-1<state.m)
        {
            state.grid[x][y - 1] = 1;
            q[r].x = x;
            q[r].y = y - 1;
            q[r].parent = f - 1;
            dir[r] = 'W';
            r++;
        }
    }

    //
    destroy(&state);
    return 0;
}
