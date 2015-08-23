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

struct subset
{
  int parent;
  int rank;
};

my_qsort(struct Edge* arr, int l , int h)
{
  int pivot, i , j;
  struct Edge temp;
  pivot = l;
  i = l;
  j = h;
  if(i < j)
  {
    while(i < j)
    {
      while(arr[i].wt <= arr[pivot].wt)
        i++;

      while(arr[j].wt > arr[pivot].wt)
        j--;

      if(i < j)
      {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }

    temp = arr[j];
    arr[j] = arr[pivot];
    arr[pivot] = temp;

    my_qsort(arr, l , j-1);
    my_qsort(arr, j+1, h);
  }

}
struct Graph* createGraph(int V , int E)
{
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
  graph->V = V;
  graph->E = E;
  graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
  return graph;
}

// a utility function to find the subset of an element i
int find(struct subset subsets[], int i)
{
  if(subsets[i].parent != i)
    subsets[i].parent = find(subsets, subsets[i].parent);

  return subsets[i].parent;    
}

// a utility function to do union of two subsets
void Union(struct subset subsets[] , int x , int y)
{
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);

  if(subsets[xroot].rank < subsets[yroot].rank)
    subsets[xroot].parent = yroot;
  if(subsets[xroot].rank > subsets[yroot].rank)
    subsets[yroot].parent = xroot;

  else
  {
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

void printfEdges(struct Edge *arr , int numEdges)
{
  int i;
   for(i = 0 ; i < numEdges ; i++)
     printf("%d  %d   %d\n", arr[i].src, arr[i].dest, arr[i].wt);
}
int kruskalMST(struct Graph *graph)
{
  int v;
  int V = graph->V;
  struct Edge result[V];
  int e = 0 ; // edge counter
  int i = 0 ;     // index for sorted edges
  //step 1: sort the edges in the ascending order
  my_qsort(graph->edge, 0 ,graph->E-1); 
  printfEdges(graph->edge, graph->E);
  //allocate memory for creating subsets
  struct subset *subsets = (struct subset*)malloc(sizeof(struct subset)*V);
  for(v = 0 ; v < V ; v++)
  {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  while(e < V-1)
  {
    struct Edge next_edge = graph->edge[i++];

    int x = find(subsets, next_edge.src);
    int y = find(subsets, next_edge.dest);
    if(x !=  y)
    {
      result[e++] = next_edge;
      Union(subsets,x,y);
    }
  }

  // print the contents of result[] to display the built MST
  printf("Following are the edges in the constructed MST\n");
  for (i = 0; i < e; ++i)
    printf("%d -- %d == %d\n", result[i].src, result[i].dest,
        result[i].wt);
  return 0;

}

// Driver program to test above functions
int main()
{
  int i, src, dst, wt , V , E;
  // Let us create following graph

  freopen("kruskal.txt","r",stdin);

  scanf("%d %d", &V, &E);
  struct Graph* graph = createGraph(V, E);

  for(i=0; i<E ; i++)
  {
    scanf("%d %d %d", &src, &dst, &wt);
    graph->edge[i].src = src;
    graph->edge[i].dest = dst;
    graph->edge[i].wt = wt;


  }

  kruskalMST(graph);

  return 0;
}
