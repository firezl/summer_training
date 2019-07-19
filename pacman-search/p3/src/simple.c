#include "util.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define inf 0x3ffffffff
game_state_t s;
int n,m;
int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
char dc[]={'E','W','S','N'};
int sum=0;
int ht[1005][1005];
struct BEAN{
    int x,y,no;
}bean[5005];
struct que{
    int x,y;
    int len;
}q[100005];
int vis[1005][1005];
int map[1005][1005];
int vst[5005];
int tot;
int ans=0x3fffffff;
int path[10005];
int pathAns[10005];
int father[1005][1005];
int flag=0;
int vts[1005];
void dfs(int x,int len,int res)
{
    if(len>ans)return ;
    if(res==0)
    {
        if(len<ans)//modify
        {
            flag=1;
            int i;
            for(i=0;i<=tot;i++)pathAns[i]=path[i];
            ans=len;
        }
        return ;
    }
    int i;
    for(i=1;i<=tot;i++)
    {
        if(!vst[bean[i].no])
        {
            vst[bean[i].no]=1;
            path[tot-res+1]=bean[i].no;
            dfs(bean[i].no,len+map[x][bean[i].no],res-1);
            vst[bean[i].no]=0;
            if(flag==0)path[tot-res+1]=0;
        }
    }
}
struct Noname{
    int x,y;
}rev[10005];
void bfs(int x,int y,int num)
{
    int head=1,tail=1;
    int nx,ny;
    int i,j;
	for(i=0;i<=10000;i++)q[i].len=q[i].x=q[i].y=0;
    q[head].x=x,q[head].y=y;
    q[head].len=0;
    
    
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            vis[i][j]=0;
    }
    vis[x][y]=1;
    int k;
    while(head<=tail)
    {
        if((s.food[q[head].x][q[head].y]==1&&(q[head].x!=x||q[head].y!=y))||(num!=0&&q[head].x==bean[0].x&&q[head].y==bean[0].y) )//modify//
        {
            map[num][ht[q[head].x][q[head].y]]=q[head].len;
		}
        for(k=0;k<4;k++)
        {
            nx=q[head].x+dx[k],ny=q[head].y+dy[k];
            if(nx<0||nx>n||ny<0||ny>m||s.grid[nx][ny]==1||vis[nx][ny]==1)continue;
            vis[nx][ny]=1;
            tail++;
            q[tail].x=nx,q[tail].y=ny;
            q[tail].len=q[head].len+1;
        }
        head++;
    }
}
int LEN;
int u,v;
int fg=0;

int visit[1005][1005];
int ate[1005][1005];
void findPath(int x,int y,int len)
{
    if(rev[v].x==x&&rev[v].y==y)
    {
        fg=1;
        return; 
    }
    if(len>LEN)return ;
    int nx,ny;
    int k;
    for(k=0;k<4;k++)
    {
        nx=x+dx[k],ny=y+dy[k];
        if(nx<0||nx>n||ny<0||ny>m||s.grid[nx][ny]==1||visit[nx][ny]==1)continue;
        visit[nx][ny]=1;
        findPath(nx,ny,len+1);
        visit[nx][ny]=0;
        if(fg==1)
        {
        	if(dc[k]=='W')printf("E");
        	if(dc[k]=='E')printf("W");
        	if(dc[k]=='N')printf("S");
        	if(dc[k]=='S')printf("N");
            exit(0);
            if(s.food[nx][ny]==1&&(nx!=rev[v].x||ny!=rev[v].y))ate[nx][ny]=1;
            return ;
        }
    }
}
int tmpvis[10005];
int visant[10005];
double mess[1005][1005];
int path2[10005];
int main() {
    
    memset(&s, 0, sizeof(s));
    init(&s);
    n=s.n,m=s.m;
    int i,j,nx,ny;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            sum++;
            ht[i][j]=sum;
        }
    }
//    for(i=0;i<s.num_ghosts;i++)
       /*
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            
            if(s.food[i][j]==1)
            {
                bean[++tot].x=i;
                bean[tot].y=j;//modify
                bean[tot].no=ht[i][j];
                rev[ht[i][j]].x=i,rev[ht[i][j]].y=j;
            }
        }
    }
    */
    for(i=0;i<s.num_ghosts;i++)
    {
        s.grid[s.ghost_x[i]][s.ghost_y[i]]=1;
        s.food[s.ghost_x[i]][s.ghost_y[i]]=0;
        int nx,ny;
        for(j=0;j<4;j++)
        {
            nx=s.ghost_x[i]+dx[j];
            ny=s.ghost_y[i]+dy[j];
            if(nx<0||nx>=n||ny<0||ny>=m)continue;
            s.grid[nx][ny]=1;
            s.food[nx][ny]=0;
        }
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(s.food[i][j]==1)
            {
                bean[++tot].x=i;
                bean[tot].y=j;
                bean[tot].no=ht[i][j];
                rev[ht[i][j]].x=i,rev[ht[i][j]].y=j;
            }
        }
    }
	ht[s.start_x][s.start_y]=0;//modify
    s.grid[s.start_x][s.start_y]=0;
    rev[0].x=bean[0].x=s.start_x,rev[0].y=bean[0].y=s.start_y;
    bean[0].no=0;
    for(i=0;i<=tot;i++)
    {
        bfs(bean[i].x,bean[i].y,bean[i].no);
    }
    // ant group //
    srand(time(NULL));
    int maxL=500;
    int gen=0;
    int t1,t2,t3,t4;
    path[0]=bean[0].no;
   // for(i=0;i<=tot;i++)pathAns[i]=bean[i].no;
    pathAns[0]=0;
    tmpvis[0]=1;
    int tmp,pos;
    ans=0;
    int genans;
    for(i=0;i<tot;i++)
    {
        tmp=0x3fffffff;
        int x=pathAns[i],jj;
        for(j=0;j<=tot;j++)
        {
            jj=bean[j].no;
            if(tmpvis[jj])continue;
            if(tmp>map[x][jj])tmp=map[x][jj],pos=j;
        }
        ans+=tmp;
        tmpvis[bean[pos].no]=1;
        pathAns[i+1]=bean[pos].no;
    }
    genans=ans;
    int k;
    int T=1000;
    int antsum=25;
    int cur=0;
    double Q=1;
    double beta=0.9;
    int zero=0;
    for(i=0;i<=tot;i++)
    {
        for(j=0;j<=tot;j++)
        {
            mess[bean[i].no][bean[j].no]=Q/(map[bean[i].no][bean[j].no]*1.0);
            if(zero<bean[i].no)zero=bean[i].no;
            if(zero<bean[j].no)zero=bean[j].no;
        }
    }
    double minn;
    int posant;
    int jj;
    double anttmp,antans;
    double down=0.1;
    while(T--)
    {
        antans=0x3fffffff;
        for(i=1;i<=antsum;i++)
        {
            int start=0;
            int ii;
            for(ii=0;ii<=tot;ii++)visant[bean[ii].no]=0;
            visant[start]=1;
            cur=0;
            path[cur]=0;
            for(k=1;k<=tot;k++)
            {
                double tmp=rand()%100/100.0;
                int forget=0;
                if(tmp>beta)
                {
                    int tt=rand()%tot+1;
                    tmp=rand()%100/100.0;
                    if(tmp>0.0001)
                    {
                        int nx=rev[path[cur]].x,ny=rev[path[cur]].y;
                        int nnx,nny;
                        int p;
                        for(p=0;p<4;p++)
                        {
                            nnx=nx+dx[p],nny=ny+dy[p];
                            if(nnx>=0&&nnx<n&&nny>=0&&nny<m&&s.food[nnx][nny]==1&&visant[ht[nnx][nny]]==0&&s.grid[nnx][nny]==0)
                            {
                                visant[ht[nnx][nny]]=1;
                                path[++cur]=ht[nnx][nny];
                                forget=1;
                                break;
                            }
                        }
                    }
                    if(forget==0)
                    {
                        while(visant[bean[tt].no]==1)tt=rand()%tot+1;
                        visant[bean[tt].no]=1;
                        path[++cur]=bean[tt].no;
                    }   
                }
               // int jj=bean[j].no;
                else
                {
                    minn=-1;posant=-1;
                    for(j=1;j<=tot;j++)
                    {
                        jj=bean[j].no;
                        if(!visant[jj]&&minn<mess[path[cur]][jj])
                        {
                            minn=mess[path[cur]][jj];
                            posant=jj;
                        }
                    }
                    path[++cur]=posant;
                    visant[posant]=1;
                }
            }
            anttmp=0;
            for(j=0;j<tot;j++)
            {
                anttmp+=map[path[j]][path[j]];
            }
            if(anttmp<antans)
            {
                for(j=0;j<=tot;j++)
                    path2[j]=path[j];
            }
        }
        tmp=0;
        for(j=0;j<tot;j++)
        {
            tmp+=map[path2[j]][path2[j+1]];
        }
        if(tmp<genans)
        {
            genans=tmp;
            for(j=0;j<=tot;j++)pathAns[j]=path2[j];
        }
        for(i=0;i<=tot;i++)
        {
            for(j=0;j<=tot;j++)
            {
                mess[bean[i].no][bean[j].no]*=down;
                mess[bean[i].no][bean[j].no]+=(1-down)*Q/antans;
            }
        }
    }

    // ant group end//
    int st=0,ed=1;
    u=pathAns[1],v=pathAns[0],LEN=map[u][v];
    while(st<ed&&ed<=tot)
    {
        while(ate[rev[u].x][rev[u].y]==1)ed++,u=pathAns[ed];
        while(ate[rev[v].x][rev[v].y]==1)st++,v=pathAns[st];
        fg=0;
        u=pathAns[ed],v=pathAns[st];
        visit[rev[u].x][rev[u].y]=1;
        LEN=map[u][v];
        findPath(rev[u].x,rev[u].y,0);
        visit[rev[u].x][rev[u].y]=0;
        st++,ed++;
    }
    destroy(&s);
    return 0;
}
