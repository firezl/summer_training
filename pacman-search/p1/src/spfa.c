#include <stdio.h>
#include <string.h>
#include "util.h"
#define MaxN 5005
#define MaxM 500005
#define INF 0x3fffffff
#define eps 0.000000000001


struct Edge
{
    int to;
    double v;
    int next;
    char way;
} e[MaxM];


int h[MaxN]= {0};
int q[MaxN];
int s[MaxN]= {0};
int used[MaxN]= {0};
double d[MaxN];
int N;
int M;
int cnt=0;

struct node_
{
    int prt;
    char dir;
} path[MaxM];


void add(int x,int y,double z,char w)
{
    cnt++;
    e[cnt].to=y;
    e[cnt].v=z;
    e[cnt].next=h[x];
    h[x]=cnt;
    e[cnt].way=w;
}


game_state_t map;


int dx[]= {0,0,-1,1};
int dy[]= {-1,1,0,0};
char dc[]= {'W','E','N','S'};
int S,t;
int sum;


int SPFA(int v0)
{
    int L=0,r=0,i,j,p;

    for (i=1; i<=sum; i++)
    {
        d[i]=INF;
        d[v0]=0;
    }
    r++;
    q[r]=v0;
    s[v0]=1;//源点v0入队
    while(L!=r)
    {
        L = (L + 1) % MaxN;//用循环队列
        i = q[L];
        s[i] = 0; //出队并标记当前点不在队列中
        for(p = h[i]; p != 0; p = e[p].next)
        {
            j = e[p].to;
            if(d[j] > d[i] + e[p].v + eps)
            {
                used[j]++;
                if(used[j] >= sum)
                {
                    printf("error");
                    return 0;
                }
                d[j]=d[i]+e[p].v;
                path[j].prt=i;
                path[j].dir=e[p].way;
                if(!s[j])
                {
                    r=(r+1)%MaxN;
                    q[r]=j;
                    s[j]=1;
                }
            }
        }
    }
    return 1;
}


int printPath(int x)
{
    if(path[x].prt!=S)
    {
        printPath(path[x].prt);
    }
    printf("%c",path[x].dir);
}


int ht[2005][2005];


int main()
{
    memset(&map,0,sizeof(map));
    init(&map);
    N=map.n;
    M=map.m;
    int i,j,k;
    // int sum=0;
    sum=0;
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            sum++;
            ht[i][j]=sum;
        }
    }
    // printf("YES\n");
    int nx,ny;
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            if(i==map.start_x&&j==map.start_y)
            {
                S=ht[i][j];
            }
            if(i==map.goal_x&&j==map.goal_y)
            {
                t=ht[i][j];
            }
            if(map.grid[i][j]==0)
            {
                for(k=0; k<4; k++)
                {
                    nx=i+dx[k],ny=j+dy[k];
                    if(nx<0||nx>N||ny<0||ny>M)
                    {
                        continue;
                    }
                    add(ht[i][j],ht[nx][ny],map.cost[nx][ny],dc[k]);
                    // printf("%d ",map.cost[nx][ny]);
                }
            }
        }
    }
    SPFA(S);
    /*
     for(i=0;i<N;i++)
     {
         for(j=0;j<M;j++)
         {
             printf("%d ",d[ht[i][j]]);
         }
         printf("\n");
     }
    */
    // printf("%d %d***\n",t,d[t]);
    printPath(t);
    //if(SPFA(1))printf("%d\n",d[N]);
    // else printf("No Solution\n");
    return 0;
}

