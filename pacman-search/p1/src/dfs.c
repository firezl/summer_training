#include "util.h"
#include <stdio.h>
#include <string.h>
int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
char dc[]={'W','E','N','S'};
int vis[2005][2005];
int maxLen;
int flag=0;
int ans=0x3fffffff;
char dir[2005];
game_state_t s;
int dfs(int x,int y,int len)
{
    if(flag==1)return 0;
    if(x==s.goal_x&&y==s.goal_y)
    {
        if(len<ans)ans=len;
        ans=len;
        flag=1;
        return 0;
    }
    if(len>maxLen)return 0;
    int i;
    int nx,ny;
    for(i=0;i<4;i++)
    {
        nx=x+dx[i],ny=y+dy[i];
        //heng x shu y
        if(nx>=0&&nx<=s.n&&ny>=0&&ny<=s.m&&vis[nx][ny]==0&&s.grid[nx][ny]==0)
        {
            vis[nx][ny]=1;
            dir[len+1]=dc[i];
            dfs(nx,ny,len+1);
            vis[nx][ny]=0;
            if(flag==0)dir[len+1]=' ';
            else return 0;
        }
    }
    return 0;
}
int main() {
    // game_state_t s;
     memset(&s, 0, sizeof(s));
     init(&s);
    ans=0x3fffffff;
    flag=0;
    int i,j;
    for(i=1;i<=300;i++)dir[i]=' ';
    for(i=1;i<=s.n;i++)
    {
        for(j=1;j<=s.m;j++)
            vis[i][j]=0;
    }
    vis[s.start_x][s.start_y]=1;
    for(int i=1;i<=300;i++)
    {
        maxLen=i;
        dfs(s.start_x,s.start_y,0);
        if(flag==1)break;
    }
  //  for(int i=1)
  // write your code here
    //0 go 1 not go
    
   // printf("%d\n",ans);
   
    for(i=1;i<=ans;i++)
    {
        printf("%c",dir[i]);
    }
    destroy(&s);
    return 0;
}
