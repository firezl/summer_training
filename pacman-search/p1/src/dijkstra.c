#include<stdio.h>
#include"util.h"
#include<string.h>
#define MAXN 2510
#define INF 0x3fffffff
#define eps 0.00000000001

game_state_t map;
int q[MAXN*2],pos[MAXN*2];
int n,m,s,t;
double dis[MAXN];

struct node {
    int to;
    int nxt;
    double v;
    char way;
}e[MAXN*5];

struct node_{
    int prt;
    char dir;
}path[MAXN*5];

int head[MAXN],tot;
int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
char dc[]={'W','E','N','S'};
int vis[MAXN];

inline int read(){
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}

void add(int x,int y,double z,char w) {
    e[++tot].to=y;
    e[tot].v=z;
    e[tot].nxt=head[x];
    head[x]=tot;
    e[tot].way=w;
}

void init2(int x) {
    q[++tot]=x;
    pos[x]=tot;
    int p=tot;
    while(p>1) {
        if(dis[q[p]]+eps<dis[q[p>>1]]) {
        	int t=q[p];q[p]=q[p>>1];q[p>>1]=t;
            //swap(q[p],q[p>>1]);
            //swap(pos[q[p]],pos[q[p>>1]]);
            t=pos[q[p]];pos[q[p]]=pos[q[p>>1]];pos[q[p>>1]]=t;
            p>>=1;
        }
        else break;
    }
    return;
}

void pop() {
    pos[q[1]]=0;
    q[1]=q[tot--];
    if(tot) pos[q[1]]=1;
    int x=2;
    while(x<=tot) {
        if(dis[q[x]]+eps>dis[q[x+1]]) x++;
        if(dis[q[x]]<dis[q[x>>1]]+eps) {
        	int t=q[x];q[x]=q[x>>1];q[x>>1]=t;
            //swap(q[p],q[p>>1]);
            //swap(pos[q[p]],pos[q[p>>1]]);
            t=pos[q[x]];pos[q[x]]=pos[q[x>>1]];pos[q[x>>1]]=t;
           // swap(q[x],q[x>>1]);
           // swap(pos[q[x]],pos[q[x>>1]]);
            x<<=1;
        }
        else break;
    }
    return;
}

int ht[MAXN][MAXN];

int printPath(int x)
{
    if(path[x].prt!=s)
    {
        printPath(path[x].prt);
    }
  //  printf("%d\n",x);
    printf("%c",path[x].dir);
}

int main() {
    int x,y,z;
    //read(n);read(m);//read(s);read(t);
   // n=read();m=read();m
    memset(&map,0,sizeof(map));
    init(&map);
    n=map.n,m=map.m;
    // s=1,t=n;
    int i,j,k;
    int sum=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            sum++;
            ht[i][j]=sum;
        }
    }
    int nx,ny;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(i==map.start_x&&j==map.start_y)s=ht[i][j];
            if(i==map.goal_x&&j==map.goal_y)t=ht[i][j];
            if(map.grid[i][j]==0)
            {
                for(k=0;k<4;k++)
                {
                    nx=i+dx[k],ny=j+dy[k];
                    if(nx<0||nx>n||ny<0||ny>m)continue;
                    add(ht[i][j],ht[nx][ny],map.cost[nx][ny],dc[k]);
                }
            }
            
        }
    }
       
    for(i=1;i<=sum;i++) dis[i]=INF;
    path[s].prt=-1;
    tot=0;
    dis[s]=0;
    init2(s);
    while(tot) {
        int u=q[1];
        pop();
        if(vis[u]) continue;
        vis[u]=1;
        int i;
        for(i=head[u];i;i=e[i].nxt) {
            int v=e[i].to;
            if(!vis[v]&&dis[v]>dis[u]+e[i].v+eps) {
                dis[v]=dis[u]+e[i].v;
                init2(v);
                path[v].prt=u;
                path[v].dir=e[i].way;
                
            }
        }
    }
  //  printf("%d\n",dis[t]);
  //  printf("%d %d",s,t);
  //  printf("%d",path[t].prt);
    printPath(t);
    destroy(&map);
    return 0;
}