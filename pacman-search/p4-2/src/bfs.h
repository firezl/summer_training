#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

game_state_t state;
typedef struct Point 
{
    int x, y;
} point;

typedef struct Queue
{
    int x, y;
    int parent;
} queue;
int n, m;
int bfs(game_state_t*, int, int, int, int, int);
int countpath(queue[], char[], int);
void printpath(queue q[], char dir[], int f);