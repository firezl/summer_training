#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "search.h"

void printHelp();
void printError();
void printSTJ();
int readInt(char *);

int main(int argc, char **argv)
{
    if (argc != 2 && argc != 5 && argc != 9 && argc != 7)
    {
        printError();
        return 0;
    }

    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
    {
        printHelp();
        return 0;
    }

    if (argc == 2 && (strcmp(argv[1], "-j") == 0))
    {
        printSTJ();
        return 0;
    }

    if (argc == 5 && (strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph") == 0) && (strcmp(argv[3], "-s") == 0 || strcmp(argv[3], "--stats") == 0))
    {
        if (strcmp(argv[4], "edges") == 0)
        {
            int edges = numberOfEdges(argv[2]);
            printf("%d\n", edges);
            return 0;
        }
        else if (strcmp(argv[4], "vertices") == 0)
        {
            int vertices = numberOfVertices(argv[2]);
            printf("%d\n", vertices);
            return 0;
        }
        else if (strcmp(argv[4], "freeman") == 0)
        {
            double freeman = freemanNetworkCentrality(argv[2]);
            printf("%g\n", freeman);
            return 0;
        }
        else
        {
            printError();
        }
    }
    if (argc == 7 && (strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph") == 0) && (strcmp(argv[3], "-s") == 0 || strcmp(argv[3], "--stats") == 0)&&(strcmp(argv[5],"-u")==0))
    {
        if (strcmp(argv[4], "betweenness") == 0)
        {
            double betweenness = betweennessCentrality(argv[2],argv[6]);
            printf("%g\n", betweenness);
            return 0;
        }
        else if (strcmp(argv[4], "closeness") == 0)
        {
            double closeness = closenessCentrality(argv[2],argv[6]);
            printf("%g\n", closeness);
            return 0;
        }
        else if (strcmp(argv[4], "eigenvector") == 0)
        {
            double eigenvector = eigenvectorCentrality(argv[2],argv[6]);
            if (ECCount == 1000)
            {
                printf("It does not converge\n");
            }
            else
            {
                printf("%g\n", eigenvector);
            }
            return 0;
        }
        else
        {
            printError();
        }

    }

    if (argc == 9 && (strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph") == 0) && (strcmp(argv[3], "-sp") == 0 || strcmp(argv[3], "--shortestpath") == 0) && (strcmp(argv[5], "-u") == 0) && (strcmp(argv[7], "-v") == 0))
    {
        FILE *fp;
        int u = readInt(argv[6]);
        int v = readInt(argv[8]);
        u++, v++;
        n = numberOfVertices(argv[2]);
        m = numberOfEdges(argv[2]);

        if (n == -1 || m == -1)
        {
            printf("Error, can not open the file\n");
            return 0;
        }
        int len = strlen(argv[4]);
        int i;
        for (i = 0; i < len; i++)
        {
            if (argv[4][i] >= 'a' && argv[4][i] <= 'z')
                argv[4][i] = argv[4][i] - 'a' + 'A';
        }

        shortestPath(u, v, argv[4]);
    }
    else
    {
        printError();
    }

    return 0;
}

void printHelp()
{
    printf("search-cli.exe\
\n-g/--graph FILE_PATH -s/--stats STATS_PARAMS\
\n\tFILE_PATH accept the filename of the graph. \
STATS_PARAMS only accept these parameters: \
\n\tedges (print the number of edges)\
\n\tvertices (print the number of vertices)\
\n\tfreeman (print the value of Freeman's Network Centrality)\
\n\tbetweenness (print the value of Closeness Centrality)\
\n\teigenvector (print the largeset value of Eigenvector Centrality)\
\n-g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT\
\n\tdispaly the shortset path from starting point u to target point v in the graph which is from the FILE_PATH\
\n\tSEARCH_PARAM only accept DFS, BFS, Dijkstra, SPFA, ASTAR\n");
    return;
}

void printError()
{
    printf("Error Input, use -h/--help to read more\n");
    return;
}

int readInt(char *num)
{
    int n = 0;
    int count = 0;
    while (num[count] != '\0')
    {
        n *= 10;
        n += num[count] - '0';
        count++;
    }
    return n;
}

void printSTJ()
{
    printf("                                          X\n\
                                              XX     XX\n\
                                             XX   XXX\n\
                                            XX XX\n\
                                            X X\n\
                           XXXXXXX    XXXXXXXXXXXXXXXXXXX\n\
                        XXXX     XXXXX     XX\n\
                        X    XXXXXX        XXXX\n\
                         XXXXX  XXX     XXXX  X\n\
                           XXXXXX      XX     X\n\
                         XXX         XXX       X\n\
                        XX        XXX     XX   X\n\
               XXXXXX  XX       XXX     XXX    X\n\
            XXX     XXXXX     XXX     XX   XX  X\n\
            X           XXXXXXX     XXX    XX XX\n\
            XX            XX        X         XXXXXX\n\
             XX                                X   XX\n\
        XXXXXXXX                                XXXX\n\
   XXXXX XXX XXXXXX                               XXX\n\
 XX XXXXXX  XXXXX XXXXXXXX                  X       XX\n\
XXXXX    XXXXXX          XX               XX         X\n\
 X      XX XX             X              XXXX       XX\n\
       XX XX              XX                XXXXXXXX\n\
       X X                 X                   XXX\n\
                           XX       XXXXXXXXXXXX\n\
                            X    XXXX\n\
                            X   XX\n\
                            X   X\n\
              XXXXXXXXXXX   X   XXX\n\
               XXX      XXXXXX    XXXX               XXXX\n\
                 XXXXXXXXXXXXX      XXXXXXXXXXXXXXXXXX  XXXX\n\
                  X   XXXXX  X       XXXXX                 XX\n\
                  XX       XXXX       X  XXX                X\n\
                   X          XXX     XX       XXXXXX       X\n\
                   X            XXX   XXX     XXX   XXX    XX\n\
                   X              XXX  XX    XX XXXXX XXXXXX\n\
                   X                 XX XX  X       XXXXX   XXXXXXXXXXXX\n\
                  XX     XXXX         XXXXXXX        XX       XX       XXXXX\n\
                 XX         XXXX       XXXX        XXXXX       XX          XXX\n\
                XX             XXX    XXX         XX   XXX      XX           XX\n\
               XX                XXXXX           XXXX    XXXX    X            X\n\
              X                   XX           XX   XXX XX   XX  X            X\n\
             X                               XXX      XXX      XXX           XX\n\
             X                             XXXXX    XXX  X        XXX        X\n\
             X                          XXXX  X XXXXX     XX        XX      X\n\
             XX                      XXXXX    X            XX         XX   XX\n\
               XX                 XXXX  X     X          XXX X          XXX\n\
                 XXXXXX     XXXXXX X   XX     X       XXXX    X X           XX\n\
                     XXXXXXX        XXXX      X   XXXX           X             XXX\n\
                 XXXX                 X       XXXXX               XXXX           XXX\n\
               XX                    X        X                    XXXX           XX\n\
              XX                    X         X                  XX    XXX       XX\n\
              X                    XX         X               XXX        XXXXXX X\n\
              X                    X         XX            XXX                XXX\n\
              XX                  XX         X          XXXX\n\
                XX                X          X      XXXXX\n\
                  XXXXX          XX         XXXXXXXXX\n\
                      XXXXXXXXXXXX          X\n\
                                 X    XX   XX\n\
                                 X XXX X  X\n\
                                XXX    X X\n\
                                X      XX\n\n");
    return;
}
