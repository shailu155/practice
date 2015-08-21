// A union-find algorithm to detect cycle in a graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a structure to represent an edge in graph
struct Edge
{
    int src, dest, wt;
};

// a structure to represent a graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
    // graph is represented as an array of edges
    struct Edge* edge;
};

struct Graph* createGraph(int V , int E)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// a utility function to find the subset of an element i
int find(int parent[], int i)
{
    if(parent[i] == -1)
        return i;
    return find(parent, parent[i]);    
}

// a utility function to do union of two subsets
void Union(int parent[] , int x , int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int kruskalMST(struct Graph *graph)
{
    int i;
    //step 1: sort the edges in the ascending order

    //allocate memory for creating subsets
    int *parent = (int*)malloc(sizeof(int)*graph->V);
    memset(parent, -1 , sizeof(int)*graph->V);

    for(i=0 ; i < graph->E ; ++i)
    {
        int x = find(parent, graph->edge[i].src);
        int y = find(parent, graph->edge[i].dest);
        if(x == y)
            return 1;
        
        Union(parent, x , y);
    }

    return 0;

}

    // Driver program to test above functions
    int main()
    {
        int i, src, dst, wt;
        // Let us create following graph

        freopen("kruskal.txt","r",stdin);

        scanf("%d %d", &V, &E);
        struct Graph* graph = createGraph(V, E);

        for(i=0; i<E ; i++)
        {
            scanf("%d %d %d", &src, &dst, &wt);
            graph->edge[i].src = src;
            graph->edge[i].dst = dst;
            graph->edge[i].wt = wt;


        }

        if (kruskalMST(graph))

        return 0;
    }
