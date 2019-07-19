#pragma once
#define _CRT_SECURE_WARNINGS

#ifndef SEARCH_H
#define SEARCH_H
#ifndef N
#define N 5000005
#endif

typedef struct node_
{
	int to, nxt;
	int v;
} node_;

typedef struct Queue
{
	int number, length;
	int father;
} queue;

extern int mapcount, path[N], used[N], prt[N], prtAns[N], dis[N], vis[N];//用于图算法的全局变量
extern int qHead[2 * N], locate[2 * N];//用于队列操作的全局变量
extern int qCount, n, m;//用于队列操作的全局变量
extern queue front[N];//用于队列操作的全局变量
extern node_ graph[N];//用于图算法的全局变量

//用于构建和处理图的函数
void add(int x, int y, int v);
void init(int x);
void pop();
int read();
void printPath(int x, int v);
int *shortestPath(int u, int v, char algorithm[]);

//用于计算最短路径的函数
int DFS(int now, int last, int len, int *ans, int n);
int BFS(int now, int last, int n);
int dijkstra();
int SPFA(int u, int v, int n);

//同于和main函数交互的函数
void DFS_START(int u, int v, int n);
void BFS_START(int u, int v, int n);
void DIJ_START(int u, int v, int n);
void SPFA_START(int u, int v, int n);

#endif
