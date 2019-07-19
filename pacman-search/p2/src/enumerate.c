#include "util.h"
#include <stdio.h>
#include <string.h>
#define inf 0x3ffffffff
game_state_t state;
int n, m;
int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };
char dc[] = { 'E','W','S','N' };
int sum = 0;
struct Food {
	int x;
	int y;
	int no;
}food[5000];
int ht[1000][1000];
int vis[1000][1000];
int map[1000][1000];
int path[10000];
int pathAns[10000];
int pre[1000][1000];
int visit_1[5000];
int LEN;
int u, v;
int biaozhi = 0;
int visit[1005][1005];
int num_f;
int ans = 0x3fffffff;
int flag = 0;
int vis_1[1005];
struct queue {
	int x, y;
	int len;
}q[100000];
void dfs(int x, int len, int res)
{
	if (len > ans)return;
	if (res == 0)
	{
		if (len < ans)
		{
			flag = 1;
			int i = 0;
			while (i <= num_f)
			{
				pathAns[i] = path[i];
				i++;
			}
			ans = len;
		}
		return;
	}
	int i = 1;
	while (i <= num_f)
	{
		if (!visit_1[food[i].no])
		{
			visit_1[food[i].no] = 1;
			path[num_f - res + 1] = food[i].no;
			dfs(food[i].no, len + map[x][food[i].no], res - 1);
			visit_1[food[i].no] = 0;
			if (flag == 0)path[num_f - res + 1] = 0;
		}
		i++;
	}
}

void getpath(int x, int y, int len)
{
	if (lli[v].x == x && lli[v].y == y)
	{
		biaozhi = 1;
		return;
	}
	if (len > LEN)return;
	int nx, ny;
	int k;
	for (k = 0;k < 4;k++)
	{
		nx = x + dx[k], ny = y + dy[k];
		if (nx<0 || nx>n || ny<0 || ny>m || state.grid[nx][ny] == 1 || visit[nx][ny] == 1)continue;
		visit[nx][ny] = 1;
		getpath(nx, ny, len + 1);
		visit[nx][ny] = 0;
		if (biaozhi == 1)
		{
			if (dc[k] == 'W')printf("E");
			if (dc[k] == 'E')printf("W");
			if (dc[k] == 'N')printf("S");
			if (dc[k] == 'S')printf("N");
			return;
		}
	}
}


struct Noname {
	int x, y;
}lli[10005];
void bfs(int x, int y, int num)
{
	int head = 1, tail = 1;
	int nx, ny;
	int i, j;
	for (i = 0;i <= 10000;i++)q[i].len = q[i].x = q[i].y = 0;
	q[head].x = x, q[head].y = y;
	q[head].len = 0;


	for (i = 0;i < n;i++)
	{
		for (j = 0;j < m;j++)
			vis[i][j] = 0;
	}
	vis[x][y] = 1;
	int k;
	while (head <= tail)
	{
		if ((state.food[q[head].x][q[head].y] == 1 && (q[head].x != x || q[head].y != y)) || (num != 0 && q[head].x == food[0].x&&q[head].y == food[0].y))//modify//
		{
			map[num][ht[q[head].x][q[head].y]] = q[head].len;
		}
		for (k = 0;k < 4;k++)
		{
			nx = q[head].x + dx[k], ny = q[head].y + dy[k];
			if (nx<0 || nx>n || ny<0 || ny>m || state.grid[nx][ny] == 1 || vis[nx][ny] == 1)continue;
			vis[nx][ny] = 1;
			tail++;
			q[tail].x = nx, q[tail].y = ny;
			q[tail].len = q[head].len + 1;
		}
		head++;
	}
}


int main() {

	memset(&state, 0, sizeof(state));
	init(&state);
	int nx, ny;
	n = state.n, m = state.m;
	int i, j; 
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < m;j++)
		{
			sum++;
			ht[i][j] = sum;
		}
	}

	for (i = 0;i < n;i++)
	{
		for (j = 0;j < m;j++)
		{
			if (state.food[i][j] == 1)
			{
				num_f++;
				lli[ht[i][j]].x = i;
				lli[ht[i][j]].y = j;
				food[num_f].x = i;
				food[num_f].y = j;
				food[num_f].no = ht[i][j];
			}
		}
	}
	ht[state.start_x][state.start_y] = 0;
	lli[0].x = food[0].x = state.start_x;
	lli[0].y = food[0].y = state.start_y;
	food[0].no = 0;
	for (i = 0;i <= num_f;i++)
	{
		bfs(food[i].x, food[i].y, food[i].no);
	}
	visit_1[food[0].no] = 1;
	flag = 0;
	path[0] = food[0].no;
	dfs(food[0].no, 0, num_f);
	int k;
	for (i = 0;i < num_f;i++)
	{
		v = pathAns[i];
		biaozhi = 0;
		u = pathAns[i + 1]; 
		LEN = map[u][v];
		visit[lli[u].x][lli[u].y] = 1;
		getpath(lli[u].x, lli[u].y, 0);
		visit[lli[u].x][lli[u].y] = 0;
	}
	destroy(&state);
	return 0;
}
