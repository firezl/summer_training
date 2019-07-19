#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

#define MaxN 5005
#define MaxM 500005
#define oo 0x3fffffff
#define eps 0.000000000001
struct Edge{
    int to;
    int v;
    int next;
    char way;
}e[MaxM];
int h[MaxN]={0},q[MaxN],s[MaxN]={0},used[MaxN]={0};
int ht[2005][2005];
int d[MaxN];
int N,M,cnt=0;
struct node_{
    int prt;
    char dir;
}path[MaxM];
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

int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
char dc[]={'W','E','N','S'};
int S,t;
int sum;
int SPFA(int v0)
{  
    int L=0,r=0,i,j,p;
    for(i=1;i<=sum;i++)d[i]=oo;d[v0]=0;
    r++;q[r]=v0;s[v0]=1;//源点v0入队
    while(L!=r)
    {  
        L=(L+1)%MaxN;//用循环队列
        i=q[L];s[i]=0; //出队并标记当前点不在队列中
        //printf("%d %d\n",i,d[i]);
        //system("pause");
        for(p=h[i];p!=0;p=e[p].next)
        {  
            j=e[p].to;
            if(d[j]>d[i]+e[p].v)
            {  
                used[j]++;
                if(used[j]>=sum){printf("error");return 0;}
                d[j]=d[i]+e[p].v;
                path[j].prt=i;
                path[j].dir=e[p].way;
                if(!s[j]){r=(r+1)%MaxN;q[r]=j;s[j]=1;}
            }
        }
   }
   return 1;
}
/*
int printPath(int x)
{
    if(path[x].prt!=S)
    {
        printPath(path[x].prt);
    }
    printf("%c",path[x].dir);
}
*/

typedef struct queue {
    int data[305];
    char dir[305];
    int l, r;
} queue;


typedef struct node {
    int v, g, h;     
    queue path;     
} node;

typedef struct priority_queue {
    node data[10005];
    int size;
} priority_queue;

void pq_init(priority_queue* q) {
    q->size = 0;
}

void swap(node *x, node *y) {
    struct node tmp = *x;
    *x = *y;
    *y = tmp;
}

bool pq_cmp(node a, node b) {
        return a.g + a.h < b.g + b.h;
}

void pq_push(priority_queue *q, node val) {/*{{{*/
   /* if (q->size >= N * N * 200) {
        printf("pq_push\n");
        exit(0);
    }*/
    int p = ++q->size;
    q->data[p] = val;
    while (p > 1 && pq_cmp(q->data[p], q->data[p / 2])) {
        swap(&q->data[p / 2], &q->data[p]);
        p /= 2;
    }
};/*}}}*/

node pq_pop(priority_queue *q) {
    if (q->size <= 0) {
        printf("pq_pop\n");
        exit(0);
    }
    node res = q->data[1];
    q->data[1] = q->data[q->size--];
    int p = 1, t;
    while (p * 2 <= q->size) {
        if (p * 2 + 1 > q->size || pq_cmp(q->data[p * 2], q->data[p * 2 + 1])) {
            t = p * 2;
        } else {
            t = p * 2 + 1;
        }
        if (pq_cmp(q->data[t], q->data[p])) {
            swap(&q->data[p], &q->data[t]);
            p = t;
        } else {
            break;
        }
    }
    return res;
}

int pq_size(priority_queue *q) {
    return q->size;
}

priority_queue pq;

bool ok(queue *q, int v) {/*{{{*/
	int i;
    for (i = q->l; i <= q->r; i++) {
        if (q->data[i] == v) {
            return true;
        }
    }
    return false;
}
void queue_init(queue *q) {
    q->l = 1;
    q->r = 0;
}

int queue_size(queue *q) {
    return q->r - q->l + 1;
}

void queue_print(queue* q) {/*{{{*/
	int i;
	/*
    for (i = q->l; i < q->r; i++) {
        printf("%d-", q->data[i]);
    }
    printf("%d\n", q->data[q->r]);
    */
    for (i = q->l+1; i <= q->r; i++) {
        printf("%c", q->dir[i]);
    }
}

void queue_push(queue *q, int val,char ch) {
  /*  if (q->r >= N) {
        printf("queue_push\n");
        exit(0);
    }*/
    q->data[++q->r] = val;
    q->dir[q->r]=ch;
}
void Astar(int src, int des, int k) { // src -> des k 鐭矾 /*{{{*/
    queue q; // 璺緞
    queue_init(&q);
    queue_push(&q, src,' ');

    node tmp = {src, 0, d[src], q};
    pq_init(&pq);
    pq_push(&pq, tmp);
	//printf("in");
    int cnt2 = 0;
    while (pq_size(&pq)) {
        tmp = pq_pop(&pq);
        if (tmp.v == des) {
            cnt2++;
            if (cnt2 == k) {
                queue_print(&tmp.path);
                return;
            }
            continue;
        }
        int i;
        for (i = h[tmp.v]; i; i = e[i].next) {
            if (ok(&tmp.path, e[i].to)) {
                continue;
            }
            node to = tmp;
            to.v = e[i].to;
            to.g += e[i].v; //to.g:s->u  e[i].w:u->v
            to.h = d[e[i].to];
            queue_push(&to.path, e[i].to,e[i].way);
            pq_push(&pq, to);
        }
    }
    puts("No");
}
int main(){ 
    memset(&map,0,sizeof(map));
    init(&map);
    N=map.n,M=map.m;
    int i,j,k;
    sum=0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            sum++;
            ht[i][j]=sum;
        }
    }
    int nx,ny;
	double co=1;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            if(i==map.start_x&&j==map.start_y)S=ht[i][j];
            if(i==map.goal_x&&j==map.goal_y)t=ht[i][j];
            if(map.grid[i][j]==0)
            {
                for(k=0;k<4;k++)
                {
                    nx=i+dx[k],ny=j+dy[k];
                    if(nx<0||nx>N||ny<0||ny>M||map.grid[nx][ny]==1)continue;
                    
                    add(ht[nx][ny],ht[i][j],1,dc[k]);
                }
            }
        }
    }
	/*

	*/
    SPFA(t);
	//printf("%d***\n",d[S]);
    //printPath(t);
    for(i=1;i<=cnt;i++)e[i].to=e[i].next=0,e[i].v=0,e[i].way=' ';
    cnt=0;
    for(i=1;i<=sum;i++)h[i]=0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            //if(i==map.start_x&&j==map.start_y)S=ht[i][j];
            //if(i==map.goal_x&&j==map.goal_y)t=ht[i][j];
            if(map.grid[i][j]==0)
            {
                for(k=0;k<4;k++)
                {
                    nx=i+dx[k],ny=j+dy[k];
                    if(nx<0||nx>N||ny<0||ny>M||map.grid[nx][ny]==1)continue;
                    add(ht[i][j],ht[nx][ny],1,dc[k]);
                }
            }
        }
    }
    /*
    for(i=1;i<=sum;i++)
	{
		printf("%d \n",i);
		for(j=h[i];j;j=e[j].next)
		{
			printf("	%d %d\n",e[j].to,e[j].v);
			}	
		printf("\n");
	} */
	Astar(S,t,1);
    return 0;
}

