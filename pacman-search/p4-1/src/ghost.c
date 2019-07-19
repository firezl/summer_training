#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int flag = 0;
int dx[4] = { 0, 0,-1,1 };
int dy[4] = { 1,-1, 0,0 };
int front, rear;
int visit[1000][1000];
game_state_t state;
game_state_t s;
struct node_
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

dot point;
//int dx[]= {0,0,-1,1},dy[]= {1,-1,0,0};
char dc[]= {'E','W','N','S'};
int vis[2005][2005];
char dir[100005];
int tot=0;
int m,n;
int nofood;
typedef struct node {
	int x;
	int y;
}node;
node queue[10000];
int map[105][105];
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
int path[10000];
char pathc[10000];

int tx;
int ty;
int prt[10005];
int cx,cy;
int fg=0;
void bfs(int x, int y)
{
    front=0,rear=0;
    int i,j;
    for(i=0;i<state.n;i++)
    {
        for(j=0;j<state.m;j++)
            visit[i][j]=0;
    }
    fg=0;
	enqueue(x, y);
	visit[x][y] = 1;
	while (front != rear)
	{
		node po = dequeue();
        if(map[po.x][po.y]==1&&fg==0)fg=1,cx=po.x,cy=po.y;
        int i;
		for (i = 0;i < 4;i++) {
			tx = po.x + dx[i];
			ty = po.y + dy[i];
			if (tx >= 0 && tx < state.n && ty >= 0 && ty < state.m && state.grid[tx][ty] == 0 && visit[tx][ty] != 1)
			{
				visit[tx][ty] = 1;
               // if(map[tx][ty]==1&&fg==0)fg=1,cx=tx,cy=ty;
				//switch (i) {
				//case 0:pathc[rear] = 'E';break;
				//case 1:pathc[rear] = 'W';break;
				//case 2:pathc[rear] = 'N';break;
				//case 3:pathc[rear] = 'S';break;
			//	}
				if (state.food[tx][ty] == 1&& nofood==0)
				{
					//path[rear] = front - 1;
                    prt[rear]=front-1;
					return;
				}
			//if (tx == 5 && ty == 9)
			//{
			//printf("%d %d :\n", tx, ty);
			//printf("%d %d %d %d %d %d", tx >= 0, tx < state.n, ty >= 0, ty < state.m, state.grid[tx][ty] != 1, visit[tx][ty] != 1);
			//}

			//printf("YES"m
				enqueue(tx, ty);
				prt[rear - 1] = front - 1;
			}
		}
	}
}

int mbx;
int mby;

int en[][4]={
    {0,1,2,3},
    {0,1,3,2},
    {0,2,1,3},
    {0,2,3,1},
    {0,3,1,2},
    {0,3,2,1},
    {1,0,2,3},
    {1,0,3,2},
    {1,2,0,3},
    {1,2,3,0},
    {1,3,0,2},
    {1,3,2,0},
    {2,0,1,3},
    {2,0,3,1},
    {2,1,0,3},
    {2,1,3,0},
    {2,3,0,1},
    {2,3,1,0},
    {3,0,1,2},
    {3,0,2,1},
    {3,1,0,2},
    {3,1,2,0},
    {3,2,0,1},
    {3,2,1,0}
};
void gbfs(int x, int y)
{
	enqueue(x, y);
	visit[x][y] = 1;
    srand(time(NULL));

	while (front != rear)
	{
		node po = dequeue();
        //for(int ii=0;ii<24;ii++){
        int kk=rand()%24;
        int i;
        int ii;
		for (ii = 0;ii < 4;ii++) {
            i=en[kk][ii];
			tx = po.x + dx[i];
			ty = po.y + dy[i];
			//if (tx == 5 && ty == 9)
			//{
			//printf("%d %d :\n", tx, ty);
			//printf("%d %d %d %d %d %d", tx >= 0, tx < state.n, ty >= 0, ty < state.m, state.grid[tx][ty] != 1, visit[tx][ty] != 1);
			//}

			//printf("YES");
			if (tx >= 0 && tx < state.n && ty >= 0 && ty < state.m && state.grid[tx][ty] != 1 && visit[tx][ty] != 1)
			{
				//printf("%d %d", tx, ty);
				//printf("YES");
				visit[tx][ty] = 1;
                //if(map[tx][ty]==1)cx=tx,cy=ty;
				switch (i) {
				case 0:pathc[rear] = 'E';break;
				case 1:pathc[rear] = 'W';break;
				case 2:pathc[rear] = 'N';break;
				case 3:pathc[rear] = 'S';break;

				}
				if (tx == mbx && ty == mby)
				{
					path[rear] = front - 1;
					return;
				}
				enqueue(tx, ty);
				path[rear - 1] = front - 1;
			}
		}
    
    }
}
int opt;
void cross()
{
    int i,j,k,sum;
    int nx,ny;
    for(i=1;i<state.n-1;i++)
    {
        for(j=1;j<state.m-1;j++)
        {
            sum=0;
            if(state.grid[i][j]==1){opt=2;continue;}
            for(k=0;k<4;k++)
            {
                
                nx=i+dx[k],ny=j+dy[k];
                if(nx<0||nx>=state.n||ny<0||ny>=state.m||state.grid[nx][ny]==1)continue;
                sum++;
            }
            if(sum>=3)
            map[i][j]=1;
        }
    }
    //if(opt==2){printf("U");}
}
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

dot csqbfs(int x,int y) //找到吃豆人距离最近的豆子
{
    int head=1,tail=1;
    q[head].x=x,q[head].y=y;
    int nx,ny;
    q[head].prt=-1;
    while(head<=tail)
    {
        int i;
        if(s.food[q[head].x][q[head].y] == 1)
        {
            s.food[q[head].x][q[head].y] == 0;
            point.i = q[head].x;
            point.j = q[head].y;
            clearpath();
            return point;
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
}
void ghost_bfs(int start_x, int start_y, int goal_x, int goal_y)//输出鬼走的路
{
    int head=1,tail=1;
    clearpath();
    q[head].x= start_x, q[head].y= start_y;
    int nx,ny;
    q[head].prt=-1;

    while(head<=tail)
    {
        if(q[head].x == goal_x && q[head].y == goal_y)
        {
            //printf("find\n");
            printPath(head);
            printf("%c",dir[1]);
            clearpath();
            return ;
        }
		int i;
        for ( i = 0; i < 4; i++)
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
}
void csq()
{
    s=state;
	int n = s.n;
    int m = s.m;
    point.i = s.start_x;
    point.j = s.start_y;
    int k;
    for ( k = 0; k < s.num_ghosts; k++)
    {
        int x = s.ghost_x[k];
        int y = s.ghost_y[k];
        int i;
        for (i = 0; i < 4; i++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            s.food[tx][ty] = 0;
        }
    }

    if(s.index == 1)
    {
        if (s.ghost_x[1] == s.start_x + 1 && s.grid[s.ghost_x[1] - 1][s.ghost_y[1]]==0)
        {
            printf("N");
        }
        else if (s.ghost_x[1] == s.start_x - 1 && s.grid[s.ghost_x[1] + 1][s.ghost_y[1]]==0)
        {
            printf("S");
        }
        else
        {
           // point = csqbfs(s.start_x,s.start_y);
            ghost_bfs(s.ghost_x[1],s.ghost_y[1],point.i,point.j);
        }
        destroy(&s);
        return ;
    }
    else if(s.index == 0)
    {
        if(s.ghost_y[0] == s.start_y + 1 && s.grid[s.ghost_x[0]][s.ghost_y[0] - 1]==0)
        {
            printf("W");
        }
        else if(s.ghost_y[0] == s.start_y - 1 && s.grid[s.ghost_x[0]][s.ghost_y[0] + 1]==0)
        {
            printf("E");
        }
        else
        {
            ghost_bfs(s.ghost_x[0],s.ghost_y[0],s.start_x,s.start_y);
        }
        destroy(&s);
        return ;
	}
}
int main() {

	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
    
  //  for(int i=0;i<=5000;i++)path[i]=-1;
    cross();
    if(opt!=2)
    {
       // printf("U");
       // return 0;
        csq();
        return 0;
    }
    nofood=1;
    bfs(state.start_x,state.start_y);
    nofood=0;
    
	bfs(state.start_x,state.start_y);

   // printf("%d %d\n",cx,cy); 
 cross();
end:
	rear = 0;
	front = 0;
	mbx = tx;
	mby = ty;
    int j=rear;
    int jtop=0;
    int jx,jy;
    int tmp=rand()%100;
    /*
    if(map[state.ghost_x[1]][state.ghost_y[1]]==1)
    {
        opt=3;
        mbx=state.start_x,mby=state.start_y;
    }*/
    
    if(opt==2)
    {
        opt=3;
        mbx=cx,mby=cy;
    }
    while(j!=0&&opt!=3)
    {
        j=prt[j];
        //if(map[queue[j].x][queue[j].y]==1&&opt==2){mbx=queue[j].x,mby=queue[j].y;continue;}
        jx=queue[j].x-state.start_x,jy=queue[j].y-state.start_y;
        if(jx<0)jx=-jx;if(jy<0)jy=-jy;
        if(jx+jy<4&&state.index==1)mbx=queue[j].x,mby=queue[j].y;
    }
	int i;
	for ( i = 0; i < 1000;i++)
	{
		int j;
		for (j = 0; j < 1000; j++)
		{
			visit[i][j] = 0;
		}		
	}

    char zhan[10005];
    for( i=0;i<=1000;i++)zhan[i]=' ',pathc[i]=' ',path[i]=0;
    if(state.index==0)
    {
        mbx=state.start_x,mby=state.start_y;
    }
    
    if(state.index==1&&tmp>90)
    {
        int x=mbx-state.ghost_x[1],y=mby-state.ghost_y[1];
        if(x<0)x=-x;if(y<0)y=-y;
        if(x+y<=4)mbx=state.start_x,mby=state.start_y;
    }
	gbfs(state.ghost_x[state.index], state.ghost_y[state.index]);
	if (tx != mbx && ty != mby)
		rear--;

	 i = rear;
	int top = 0;

	while (i != 0)
	{
		zhan[top] = pathc[i];
		top++;
		i = path[i];
	}

	top--;
    if(zhan[top]=='\x00'&&top>0)goto end;//printf("W");
    if(zhan[top]==' ')goto end;
    char ch=zhan[top];
	printf("%c", ch);

	//system("PAUSE");
	destroy(&state);
	return 0;
}
