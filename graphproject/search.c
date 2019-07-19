#define _CRT_SECURE_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "search.h"

#ifndef N
#define N 5000005
#endif
#define MAXN_dij 2510
#define INF 0x3fffffff
#define MOD 1000007

int mapcount = 0;
int qCount = 0;
int path[N], vis[N], used[N], dis[N];
int prt[N], prtAns[N];
int qHead[2 * N], locate[2 * N];
node_ graph[N];
queue front[N];

void add(int x, int y, int v)
{
	mapcount++;
	graph[mapcount].to = y;
	graph[mapcount].v = v;
	graph[mapcount].nxt = path[x];
	path[x] = mapcount;
}

void init(int x)
{
	qHead[++qCount] = x;
	locate[x] = qCount;
	int p = qCount;
	while (p > 1)
	{
		if (dis[qHead[p]] < dis[qHead[p >> 1]])
		{
			int t = qHead[p];
			qHead[p] = qHead[p >> 1];
			qHead[p >> 1] = t;
			t = locate[qHead[p]];
			locate[qHead[p]] = locate[qHead[p >> 1]];
			locate[qHead[p >> 1]] = t;
			p >>= 1;
		}
		else
			break;
	}
	return;
}

void pop()
{
	locate[qHead[1]] = 0;
	qHead[1] = qHead[qCount--];
	if (qCount)
	{
		locate[qHead[1]] = 1;
	}
	int x = 2;
	while (x <= qCount)
	{
		if (dis[qHead[x]] > dis[qHead[x + 1]])
		{
			x++;
		}
		if (dis[qHead[x]] < dis[qHead[x >> 1]])
		{
			int t = qHead[x];
			qHead[x] = qHead[x >> 1];
			qHead[x >> 1] = t;
			t = locate[qHead[x]];
			locate[qHead[x]] = locate[qHead[x >> 1]];
			locate[qHead[x >> 1]] = t;
			x <<= 1;
		}
		else
			break;
	}
	return;
}

void printPath(int x, int v)
{
	if (prtAns[x] != -1)
	{
		printPath(prtAns[x], v);
	}
	if (x == v)
	{
		printf("%d\n", v - 1);
	}
	else
	{
		printf("%d-> ", x - 1);
	}
	return;
}

int DFS(int now, int last, int len, int *ans, int n)
{
	int i;

	if (now == last)
	{
		if (len < *ans)
		{
			*ans = len;
			for (int i = 1; i <= n; i++)
			{
				prtAns[i] = prt[i];
			}
			return 0;
		}
		return 0;
	}
	if (len > *ans)
	{
		return *ans;
	}

	for (i = path[now]; i; i = graph[i].nxt)
	{
		int j = graph[i].to;
		if (!vis[j])
		{
			vis[j] = 1;
			prt[j] = now;
			DFS(j, last, len + graph[i].v, ans, n);
			vis[j] = 0;
		}
	}

	return 0;
}

int BFS(int now, int last, int n)
{
	int head = 1, tail = 1;
	int ans = 0x3ffffff;

	front[head].number = now, front[head].length = 0;
	while (head <= tail)
	{
		int j;
		for (j = path[front[head].number]; j; j = graph[j].nxt)
		{
			if (!vis[graph[j].to])
			{
				++tail;
				front[tail].number = graph[j].to;
				front[tail].length = front[head].length + graph[j].v;
				vis[front[tail].number] = 1;
				prt[front[tail].number] = front[head].number;
			}
		}

		if (front[head].number == last && front[head].length < ans)
		{
			ans = front[head].length;
			for (int i = 1; i <= n; i++)
			{
				prtAns[i] = prt[i];
			}
		}
		head++;
	}
	return ans;
}

int dijkstra(int s, int t, int n)
{
	int i;
	qCount = 0;
	for (i = 1; i <= n; i++)
	{
		dis[i] = INF;
	}

	dis[s] = 0;
	init(s);
	while (qCount)
	{
		int u = qHead[1];
		pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		int i;
		for (i = path[u]; i; i = graph[i].nxt)
		{
			int v = graph[i].to;
			if (!vis[v] && dis[v] > dis[u] + graph[i].v)
			{
				dis[v] = dis[u] + graph[i].v;
				init(v);
				prtAns[v] = u;
			}
		}
	}
	return dis[t];
}

int SPFA(int u, int v, int n)
{
	int L = 0, r = 0, i, j, p, v0 = u;

	for (i = 1; i <= n; i++)
		dis[i] = INF;
	dis[v0] = 0;
	r++;

	qHead[r] = v0;
	vis[v0] = 1;
	while (L != r)
	{
		L = (L + 1) % MOD;
		i = qHead[L];
		vis[i] = 0;
		for (p = path[i]; p != 0; p = graph[p].nxt)
		{
			j = graph[p].to;
			if (dis[j] > dis[i] + graph[p].v)
			{
				used[j]++;
				if (used[j] >= N)
				{
					return 0;
				}
				dis[j] = dis[i] + graph[p].v;
				prtAns[j] = i;
				if (!vis[j])
				{
					r = (r + 1) % MOD;
					qHead[r] = j;
					vis[j] = 1;
				}
			}
		}
	}
	return dis[v];
}

int Astar(int u, int v, int n)
{
	int ans;
	int head = 1, tail = 1;
	prtAns[u] = -1;
	ans = dijkstra(u, v, n);

	while (qCount)
	{
		int u = qHead[1];
		pop();
		if (vis[u])
		{
			continue;
		}

		vis[u] = 1;
		int i;
		for (i = path[u]; i; i = graph[i].nxt)
		{
			int v = graph[i].to;
			if (!vis[v] && dis[v] > dis[u] + graph[i].v)
			{
				dis[v] = dis[u] + graph[i].v;
				init(v);
				prt[v] = u;
			}
		}
	}

	return ans;
}

void DFS_START(int u, int v, int n)
{
	int ans = 0x3fffffff;
	prt[u] = -1;
	vis[u] = 1;
	DFS(u, v, 0, &ans, n);
	int k = v;
	printPath(v, v);
}

void BFS_START(int u, int v, int n)
{
	int ans;
	prt[u] = -1;
	vis[u] = 1;
	ans = BFS(u, v, n);
	printPath(v, v);
}

void DIJ_START(int u, int v, int n)
{
	int ans;
	prtAns[u] = -1;
	ans = dijkstra(u, v, n);

	printPath(v, v);
}

void SPFA_START(int u, int v, int n)
{
	int ans;
	prtAns[u] = -1;
	ans = SPFA(u, v, n);

	printPath(v, v);
}

void ASTAR_START(int u, int v, int n)
{
	int ans;
	prtAns[u] = -1;
	ans = Astar(u, v, n);
	printPath(v, v);
}

int *shortestPath(int u, int v, char algorithm[])
{
	if (algorithm[0] == 'D' && algorithm[1] == 'F')
		DFS_START(u, v, n);
	if (algorithm[0] == 'B' && algorithm[1] == 'F')
		BFS_START(u, v, n);
	if (algorithm[0] == 'D' && algorithm[1] == 'I')
		DIJ_START(u, v, n);
	if (algorithm[0] == 'S' && algorithm[1] == 'P')
		SPFA_START(u, v, n);
	if (algorithm[0] == 'A' && algorithm[1] == 'S')
		ASTAR_START(u, v, n);
}
