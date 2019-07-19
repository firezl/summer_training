#pragma once
#ifndef STATS_H
#define STATS_H
#ifndef N
#define N 5000005
#endif

extern int map[105][105], tempMap[105][105];
extern int ECCount;
extern int BCCount[N], FMCount[N], vFlag[N];
extern double CCCount[N];

int numberOfEdges(char name[]);               // 接受以文件名为图标识符的 char 数组，返回图中边的数量
int numberOfVertices(char name[]);            // 接受以文件名为图标识符的 char 数组，返回图中顶点的数量
double freemanNetworkCentrality(char name[]); // 接受以文件名为图标识符的 char 数组，返回图中 Freeman's Network Centrality 值
double betweennessCentrality(char name[],char node[]);    // 接受以文件名为图标识符的 char 数组，返回图中 Betweenness Centrality 值
double closenessCentrality(char name[],char node[]);      // 接受以文件名为图标识符的 char 数组，返回图中 Closeness Centrality 值
double eigenvectorCentrality(char name[],char node[]);    // 接受以文件名为图标识符的 char 数组，返回图中 Eigenvector Centrality 值

#endif
