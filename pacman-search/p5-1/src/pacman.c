#include "util.h"
#include <stdio.h>
#include <string.h>

int flag = 0;
int dx[4] = { 0, 0,-1,1 };
int dy[4] = { 1,-1, 0,0 };
char dc[]={'E','W','N','S'};
int front, rear;
int visit[1000][1000];
game_state_t state;

typedef struct node {
	int x;
	int y;
}node;
int food[105][105];
node queue[10000];
typedef struct que{
    int x,y,len;
    int prt;
    char way;
}que;
que q[100005];
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
int g[105][105];
void bfs(int x, int y)
{
	enqueue(x, y);
	visit[x][y] = 1;
	while (front != rear)
	{
		node po = dequeue();
		int i;
		for ( i = 0;i < 4;i++) {
			int tx = po.x + dx[i];
			int ty = po.y + dy[i];
			if (tx >= 0 && tx < state.n && ty >= 0 && ty < state.m && state.grid[tx][ty] != 1 && visit[tx][ty] != 1)
			{
                if(g[tx][ty]==1)tx=1,ty=1;
				visit[tx][ty] = 1;
				switch (i) {
				case 0:pathc[rear] = 'E';break;
				case 1:pathc[rear] = 'W';break;
				case 2:pathc[rear] = 'N';break;
				case 3:pathc[rear] = 'S';break;
				}
				if (state.food[tx][ty] == 1)
				{
					flag = 1;
					path[rear] = front - 1;
					return;
				}
				enqueue(tx, ty);
				path[rear - 1] = front - 1;
			}
		}
	}
}
int start_x,start_y,ex,ey;
int vis[105][105];
//int g[105][105];
que gbfs(int x,int y,int opt,que dot)
{
    int head=1,tail=1;
    int i,j;
    for(i=0;i<101;i++)
    {
        for(j=0;j<101;j++)
            vis[i][j]=0;
    }
    q[head].x=x,q[head].y=y;
    q[head].len=0;
    int nx,ny;
    int k;
    //printf("%d %d %ddot\n",dot.x,dot.y,opt);
    while(head<=tail)
    {
    	//printf("%d %d (%d,%d)\n",head,tail,q[head].x,q[head].y);
        if(opt==1&&state.food[q[head].x][q[head].y]==1)
        {
            return q[head];
        }
        if(opt==2&&q[head].x==dot.x&&q[head].y==dot.y)
        {
            return q[head];
        }
        if(opt==3&&q[head].x==dot.x&&q[head].y==dot.y)
        {
        	//printf("%d >>?>\n",q[head].prt);
            return q[head];
        }
        for(k=0;k<4;k++)
        {
            nx=q[head].x+dx[k],ny=q[head].y+dy[k];
            if(nx<0||nx>=state.n||ny<0||ny>=state.m||vis[nx][ny]||state.grid[nx][ny]==1)continue;
            tail++;
            vis[nx][ny]=1;
            //printf("(%d,%d)\n",nx,ny);
            q[tail].y=ny,q[tail].x=nx;
            q[tail].len=q[head].len+1;
            q[tail].prt=head;
            q[tail].way=dc[k];
        }
        head++;
    }
}
int f(int x)
{
    if(x<0)return -x;
    else return x;
}
int main() {

	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
    // (7,12) -> (8,20) 14
    if(state.is_red==1)
    {
        start_x=state.red_x,start_y=state.red_y;
        ex=state.blue_x,ey=state.blue_y;
    }
    else 
    {
        start_x=state.blue_x,start_y=state.red_y;
        ex=state.red_x,ey=state.red_y;
    }
    int i,j;
    for(i=0;i<state.n;i++)
    {
        for(j=0;j<state.m;j++)
        {
            if(i==0&&j==0)food[i][j]=(state.food[i][j]==1);
            else if(i==0)food[i][j]=food[i][j-1]+(state.food[i][j]==1);
            else if(j==0)food[i][j]=food[i-1][j]+(state.food[i][j]==1);
            else food[i][j]=food[i-1][j]+food[i][j-1]-food[i-1][j-1]+(state.food[i][j]==1);
        }
    }
    que nulld;
    que centre;
    int fs=food[8][20]-food[6][20]-food[8][11]+food[6][11];
    if(food[8][20]-food[6][20]-food[8][11]+food[6][11]>=13&&f(start_x-8)+f(start_y-12)>=2)
    {
        nulld.x=8,nulld.y=12;
    	for(int i=0;i<state.num_ghosts;i++)
        {
            //while(nulld.x==state.ghost_x[i]&&nulld.y==state.ghost_y[i])nulld.y++;
            
    	    state.grid[state.ghost_x[i]][state.ghost_y[i]] = 1;
        }
        if((state.ghost_y[0] == 12 && state.ghost_y[1] == 13 && state.ghost_x[0] == 8 && state.ghost_x[1] == 8) || (state.ghost_y[0] == 13 && state.ghost_y[1] == 12 && state.ghost_x[0] == 8 && state.ghost_x[1] == 8))
        {
           
                nulld.y=14;
        }
        else if(state.ghost_x[0] == 8&&state.ghost_y[0]==12)
        {
		nulld.y=13;
        }
	else if(state.ghost_x[1] == 8&&state.ghost_y[1]==12)
	{
		nulld.y=13;
	}
        /*
		state.grid[state.ghost_x[i] + 1][state.ghost_y[i]] = 1;
		state.grid[state.ghost_x[i] - 1][state.ghost_y[i]] = 1;
		state.grid[state.ghost_x[i]][state.ghost_y[i] + 1] = 1;
		state.grid[state.ghost_x[i]][state.ghost_y[i] - 1] = 1;
    	*/
        //nulld.x=8,nulld.y=12;
        //printf("%d ****&^*\n",state.grid[nulld.x][nulld.y]); 
        centre=gbfs(start_x,start_y,3,nulld);
        //printf("???\n");
        while(centre.prt!=1)
        {
            //printf("%d* \n",centre.prt);
            //system("pause");
            centre=q[centre.prt];
            
        }
        printf("%c",centre.way);
        return 0;
    }
    que en=gbfs(ex,ey,1,nulld);
    que my=gbfs(start_x,start_y,2,en);
    if(en.len<my.len)
    {
        state.food[en.x][en.y]=0;
    }
    if(fs<=3&&food[2][15]>=6&&start_x>=6&&start_x<=9&&start_y>=12&&start_y<=20)
    {
        nulld.x=state.ghost_x[0],nulld.y=state.ghost_y[0];
        centre=gbfs(start_x,start_y,3,nulld);
        while(centre.prt!=1)centre=q[centre.prt];
        printf("%c",centre.way);
        return 0;
    }
    
	for (i = 0;i < state.num_ghosts;i++)
	{
        g[state.ghost_x[i]][state.ghost_y[i]]=1;
        if(start_x>=6&&start_x<=8&&start_y>=12&&start_y<=20&&fs>=3)
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
    
	if (state.is_red == 1)
    {
		bfs(state.red_x, state.red_y);
    }
	else
		bfs(state.blue_x, state.blue_y);
	if (flag != 1)
		rear--;
	 i = rear;
	char zhan[10000];
	int top = 0;
	while (i != 0)
	{
		zhan[top] = pathc[i];
		top++;
		i = path[i];
	}
	top--;
	if (rear != 0)
		printf("%c", zhan[top]);
	else
    {
        state.grid[start_x][start_y]=0;
        for(int k=0;k<4;k++)
        {
            int nx,ny;
            nx=start_x+dx[k],ny=start_y+dy[k];
            if(nx<0||nx>=state.n||ny<0||ny>=state.m||state.grid[nx][ny]==1)continue;
            printf("%c",dc[k]);
        }
    }
    for(int k=0;k<4;k++)
    {
        int nx,ny;
        nx=start_x+dx[k],ny=start_y+dy[k];
        for(int i=0;i<state.num_ghosts;i++)
        {
            if(nx==state.ghost_x[i]&&ny==state.ghost_y[i])
            {
                printf("%c",dc[k]);
                return 0;
            }
        }
    }
	destroy(&state);
	return 0;
}

