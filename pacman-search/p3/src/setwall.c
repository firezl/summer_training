#include "util.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

struct node
{
    int x,y;
    char ch;
    int prt;
} q[1000005];

typedef struct dot
{
    int i;
    int j;
} dot;

game_state_t s;

dot point;
int dx[]= {0,0,-1,1},dy[]= {-1,1,0,0};
char dc[]= {'W','E','N','S'};
int vis[2005][2005];
char dir[100005];
int flag[2005][2005];
int tot=0;
int m,n;


void printPath(int x)
{
    if(q[x].prt!=1)
    {
        printPath(q[x].prt);
    }
    dir[++tot]=q[x].ch;
}

void clearpath()
{
    memset(vis,0,sizeof(vis));
    tot = 0;
}

void bfs(int x,int y)
{
    int head=1,tail=1;
    q[head].x=x,q[head].y=y;
    int nx,ny;
    q[head].prt=-1;
    while(head<=tail)
    {
        int i;
        if(s.food[q[head].x][q[head].y] == 1 && flag[q[head].x][q[head].y] == 0)
        {
            //s.food[q[head].x][q[head].y] = 0;
            printPath(head);
            printf("%c",dir[1]);
            return;
        }
        for(i=0; i<4; i++)
        {
            nx=q[head].x+dx[i],ny=q[head].y+dy[i];
            if(nx<0||nx>s.n||ny<0||ny>s.m||vis[nx][ny]==1||s.grid[nx][ny]==1)continue;
            vis[nx][ny]=1;
            tail++;
            q[tail].x=nx,q[tail].y=ny;
            q[tail].ch=dc[i];
            q[tail].prt=head;
        }
        head++;
    }
    return;
}


int main()
{
    memset(&s, 0, sizeof(s));
    init(&s);
    int n = s.n;
    int m = s.m;

    point.i = s.start_x;
    point.j = s.start_y;
    memset(flag,0,sizeof(flag));

    dot ghostpos;
    for (int k = 0; k < s.num_ghosts; k++)
    {
        ghostpos.i = s.ghost_x[k];
        ghostpos.j = s.ghost_y[k];
        int nx,ny;
        for(int i=0; i<4; i++)
        {
            nx = ghostpos.i + dx[i] , ny = ghostpos.j + dy[i];
            if(nx<0||nx>s.n||ny<0||ny>s.m)continue;
            s.grid[nx][ny] = 1;
            flag[nx][ny] = 1;
            if(i <= 1) {
            	flag[nx-1][ny] = 1;
            	flag[nx+1][ny] = 1;
			}
        }
    }
    if(s.grid[point.i][point.j] == 1) {
    	if(point.j-1>=0 && point.j+1<m && s.grid[point.i][point.j - 1] == 1 && s.grid[point.i][point.j + 1] == 1 ) {
    		if(point.i-1 >= 0 && s.grid[point.i-1][point.j] == 0 ) {
    			printf("N");
    			return 0;
			} else if (point.i+1 < n && s.grid[point.i+1][point.j] == 0) {
				printf("S");
				return 0;
			} else {
				return 0;
			}
		} else if (point.i-1>=0 && point.i+1<n && s.grid[point.i-1][point.j] == 1 && s.grid[point.i+1][point.j] == 1) {
			if(point.j-1 >= 0 && s.grid[point.i][point.j-1] == 0 ) {
    			printf("W");
    			return 0;
			} else if (point.j+1 < m && s.grid[point.i][point.j+1] == 0) {
				printf("E");
				return 0;
			} else {
				return 0;
			}
		} else if (point.j-1>=0 && point.j+1<m && s.grid[point.i][point.j - 1] == 1 && s.grid[point.i][point.j + 1] == 0) {
			printf("E");
			return 0;
		} else if (point.j+1<m && point.j-1>=0 && s.grid[point.i][point.j + 1] == 1 && s.grid[point.i][point.j - 1] == 0) {
			printf("W");
			return 0;
		} else if (point.i-1>=0 && point.i+1<n && s.grid[point.i - 1][point.j] == 1 && s.grid[point.i + 1][point.j] == 0) {
			printf("S");
			return 0;
		} else if (point.i+1<n && point.i-1>=0 && s.grid[point.i+1][point.j] == 1 && s.grid[point.i-1][point.j] == 0) {
			printf("N");
			return 0;
		} else {
			bfs(point.i,point.j);
			return 0;
		}
	}
    bfs(point.i,point.j);
    destroy(&s);
    return 0;
}
