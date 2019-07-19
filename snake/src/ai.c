#include "ai.h"
#include "game.h"
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct que{
	int x,y,len;
	int prt,way;
    int time;
}que;

que q[10005];
int vis[105][105][505];
int t[505][505];
direction_t get_action(game_t* game) {
    int x=game->snake->head->row,y=game->snake->head->col;
   // printf("%d %d\n",x,y);
    int n=game->board->rows,m=game->board->cols;
    int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
    int i,j,k;
    int head=1,tail=1;
    for(i=0;i<=10000;i++)q[i].x=q[i].y=q[i].len=0;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            for(k=0;k<=500;k++)
                vis[i][j][k]=0;
    snake_node_t *p=game->snake->head;
   // printf("here\n");
   // int len=(game->snake->)
    int len=0;
    while(p!=NULL)
    {
        len++;
        p=p->next;
    }
   // printf("---\n");
    p=game->snake->head;
    int len2=0;
    while(p!=NULL)
    {
        t[p->row][p->col]=len-len2;
        p=p->next;
    }
   // printf("----\n");
    vis[x][y][0]=1;
    q[head].x=x,q[head].y=y,q[head].len=0;
    int nx,ny,nt;
    while(head<=tail)
    {
      //  printf("%d %d\n",head,tail);
       // printf("***\n");
        if(*(board_cell(game->board,q[head].x,q[head].y))==1)
        {
           // printf("%d\n",*board_cell(game->board,q[head].x,q[head].y));
          //  printf("lyzdsb\n");
            break;
        }
        //printf("***\n");
        for(k=0;k<4;k++)
        {
            //printf("(%d,%d)",nx,ny);

            nx=q[head].x+dx[k],ny=q[head].y+dy[k];
            nt=q[head].time+1;
          //  printf("%d %d (%d,%d)",q[head].x,q[head].y,nx,ny);
          //  printf("%p***\n",(board_cell(game->board,nx,ny)));
            if(nx<0||nx>=n||ny<0||ny>=m||nt>500||vis[nx][ny][nt]||*(board_cell(game->board,nx,ny))==2||*(board_cell(game->board,nx,ny))==3)continue;

            vis[nx][ny][nt]=1;
            q[++tail].x=nx,q[tail].y=ny;
            q[tail].len=q[head].len+1;
            q[tail].prt=head;
            q[tail].way=k;
            q[tail].time=nt;
        }
        head++;
    }
    //printf("DONE\n");
    int prt=head;
    //printf("%d \n",prt);
    if(prt==1)goto end;
    if(head>tail)goto end2;
    while(q[prt].prt!=1)
    {
        prt=q[prt].prt;
      //  printf("%d \n",prt);
       // system("pause");
       // sleep(1000);
      //head++  for(i=0;i<=1000000000;i++)j=0;
    }
    end:;
    if(q[prt].way==0)return EAST;
    if(q[prt].way==1)return WEST;
    if(q[prt].way==2)return SOUTH;
    if(q[prt].way==3)return NORTH;
    end2:;
    //printf("everybody is here now\n");
    for(k=0;k<4;k++)
    {
        nx=x+dx[k],ny=y+dy[k];
        //printf("%d %d \n",nx,ny);
        if(nx<0||ny<0||nx>=n||ny>=m||*(board_cell(game->board,nx,ny))==2||*(board_cell(game->board,nx,ny))==3)continue;
        if(k==0)return EAST;
        if(k==1)return WEST;
        if(k==2)return SOUTH;
        if(k==3)return NORTH;
    }
   // printf("serious");
}
