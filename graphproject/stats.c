#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "search.h"
#ifndef N
#define N 5000005
#endif

int vFlag[N], FMCount[N], BCCount[N];
int map[105][105], tempMap[105][105];
int ECCount, m, n;
double EiValue[N], EiCount[N];
double CCCount[N];

int numberOfVertices(char name[])
{
	FILE *fp;
	int a, b, c;
	int sum = 0;

	if ((fp = fopen(name, "r")) == NULL)
		return -1;

	while (!feof(fp))
	{
		fscanf(fp, "%d%d%d", &a, &b, &c);
		if (vFlag[a] == 0)
			vFlag[a] = 1, sum++;
		if (vFlag[b] == 0)
			vFlag[b] = 1, sum++;
	}

	fclose(fp);
	return sum;
}

int numberOfEdges(char name[])
{
	FILE *fp;
	int a, b, c;
	int sum = 0;
	if ((fp = fopen(name, "r")) == NULL)
		return -1;

	while (!feof(fp))
	{
		fscanf(fp, "%d%d%d", &a, &b, &c);
		a++, b++;
		add(a, b, c);
		sum++;
	}

	fclose(fp);
	return sum;
}

double freemanNetworkCentrality(char name[])
{
	m = numberOfEdges(name);
	n = numberOfVertices(name);
	int ans = 0;
	int ans2 = 0;
	int i;

	for (i = 1; i <= n; i++)
	{
		int j;
		for (j = path[i]; j; j = graph[j].nxt)
		{
			FMCount[i]++;
		}
		if (FMCount[i] > ans)
			ans = FMCount[i];
	}

	for (i = 1; i <= n; i++)
	{
		ans2 += (ans - FMCount[i]);
	}
    long long longn=n;
    long long longResult=((longn - 1) * (longn - 2));

	return (ans2*1.0) / longResult;
}

double closenessCentrality(char name[],char node[])
{
	FILE *in;
	int mid, i, j;
	int a, b, c;
	double ans;
	double eps = 0.0000001;

	if ((in = fopen(name, "r")) == NULL)
		return -1;

	n = numberOfVertices(name);
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			map[i][j] = 0x3fffffff;
		map[i][i] = 0;
	}

	while (!feof(in))
	{
		fscanf(in, "%d%d%d", &a, &b, &c);
		a++, b++;
		map[a][b] = c;
	}
	fclose(in);

	for (mid = 1; mid <= n; mid++)
	{
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				if (map[i][mid] != 0x3fffffff && map[mid][j] != 0x3fffffff && map[i][mid] + map[mid][j] < map[i][j])
				{
					map[i][j] = map[i][mid] + map[mid][j];
				}
			}
		}
	}
	//char node[]
	if(node[0] == 'm' && node[1] == 'a' && node[2] == 'x')
	{
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				FMCount[i] += map[i][j];
			}
			CCCount[i] = FMCount[i];
			if (ans + eps < ((n - 1) / (CCCount[i] * 1.0)))
			{
				ans = ((n - 1) / (CCCount[i] * 1.0));
			}
		}
		return ans;
	}

	else
	{
		int x;
		int len=strlen(node);
		for(i=0;i<len;i++)
		{
			x=x*10+(node[i]-'0');
        }
		for (j = 1; j <= n; j++)
		{
			FMCount[x] += map[x][j];
		}
		CCCount[x] = FMCount[x];
		return (n - 1) / (CCCount[x] * 1.0);

	}

}

double eigenvectorCentrality(char name[],char node[])
{
	int ct = 0, fg = 1, i, j;
	double maxn = 0, sum = 0, eps = 0.0001;
	ECCount = 0;
	m = numberOfEdges(name);
	n = numberOfVertices(name);

	for (i = 1; i <= n; i++)
	{
		EiValue[i] = 1.0;
	}

	while (1)
	{
		fg = 1;
		ECCount++;
		for (i = 1; i <= n; i++)
		{
			sum = 0;
			maxn = 0;
			for (j = path[i]; j; j = graph[j].nxt)
			{
				sum += EiValue[graph[j].to];
			}
			if ((sum - EiValue[i] > eps) || (EiValue[i] - sum > eps))
			{
				EiCount[i] = sum;
			}
			if (EiCount[i] > maxn + eps)
			{
				maxn = EiCount[i];
			}
		}

		for (i = 1; i <= n; i++)
		{
			if (maxn != 0)
			{
				EiCount[i] /= maxn;
			}
			if ((EiCount[i] - EiValue[i] > eps) || (EiValue[i] - EiCount[i] > eps))
			{
				EiValue[i] = EiCount[i], fg = 0;
			}
		}

		if (fg == 1)
		{
			ct++;
		}
		else
		{
			ct = 0;
		}

		if (ct >= 2)
		{
			break;
		}

		if (ECCount == 1000)
		{
			return -1;
		}
	}
	if(node[0] == 'm' && node[1] == 'a' && node[2] == 'x')
	{
		for (i = 1; i <= n; i++)
		{
			if (EiValue[i] - maxn > eps)
			{
				maxn = EiValue[i];
			}
		}
		return maxn;
	}

	else
	{
		int x;
		int len=strlen(node);

		for(i=0;i<len;i++)
		{
			x=x*10+(node[i]-'0');
		}

		return EiValue[x];
	}

}

double betweennessCentrality(char name[], char node[])
{
	FILE *fp;
	int mid, i, j, a, b, c, count = 0, num;
	double ans;
	long long sumi = 0;

	if (strcmp(node, "max") == 0)
	{
		num = -1;
	}
	else
	{
		while (node[count] != '\0')
		{
			num *= 10;
			num += node[count] - '0';
			count++;
		}
	}

	if ((fp = fopen(name, "r")) == NULL)
	{
		return -1;
	}

	n = numberOfVertices(name);

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
			map[i][j] = 0x3fffffff;
		map[i][i] = 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d%d%d", &a, &b, &c);
		a++, b++;
		map[a][b] = c;
	}
	fclose(fp);

	for (i = 0; i < n + 1; i++)
	{
		BCCount[i] = 0;
	}

	for (mid = 1; mid <= n; mid++)
	{
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				tempMap[i][j] = map[i][j];
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (map[i][mid] != 0x3fffffff && map[mid][j] != 0x3fffffff && map[i][mid] + map[mid][j] <= map[i][j])
				{
					if (map[i][mid] + map[mid][j] < map[i][j])
					{
						map[i][j] = map[i][mid] + map[mid][j],
						BCCount[mid]++;
						sumi++;
					}
					else if (map[i][mid] + map[mid][j] == map[i][j])
					{
						BCCount[mid]++;
						sumi++;
					}
				}
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
			{
				if (tempMap[i][j] != map[i][j])
				{
					BCCount[mid]++;
				}
			}
	}

	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			if (map[i][j] != 0x3fffffff)
				sumi++;
		}

	ans = 0;
	if (num == -1)
	{
		for (i = 1; i <= n; i++)
		{
			ans = ans > BCCount[i] ? ans : BCCount[i];
		}
	}
	else
	{
		ans = BCCount[num];
	}

	return ans / sumi;
}
