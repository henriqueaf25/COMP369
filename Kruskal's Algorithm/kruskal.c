#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100

struct Edge
{
  int u, v, weight;
};

struct Graph
{
  struct Edge *edge;
};

struct Graph *newGraph(int Edges)
{
  struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
  graph->edge = (struct Edge *)malloc(sizeof(struct Edge) * Edges);
  return graph;
};
struct set
{
  int apro, level;
};
int findCicle(struct set sets[], int i)
{
  if (sets[i].apro != i)
    sets[i].apro = findCicle(sets, sets[i].apro);
  return sets[i].apro;
}
int higher(const void *x, const void *y)
{
  struct Edge *x1 = (struct Edge *)x;
  struct Edge *y1 = (struct Edge *)y;
  int result = x1->weight > y1->weight;
  return result;
}
void kruskal(struct Graph *graph, int numVertices, int numEdges, bool sort, char valid[])
{
  struct Edge mst[numVertices];
  int i = 0, j = 0, aux;
  qsort(graph->edge, numEdges, sizeof(graph->edge[i]), higher);
  struct set *sets = (struct set *)malloc(numVertices * sizeof(struct set));
  for (aux = 0; aux < numVertices; ++aux)
  {
    sets[aux].apro = aux;
    sets[aux].level = 0;
  }
  while (i < numVertices - 1 && j < numEdges)
  {
    struct Edge sucessor = graph->edge[j];
    int aux1 = findCicle(sets, sucessor.u), aux2 = findCicle(sets, sucessor.v);
    if (aux1 != aux2)
    {
      mst[i] = sucessor;
    }
    ++i;
    ++j;
  }
  if (sort)
  {
    struct Edge store;
    for (i = 0; i < numVertices - 1; ++i)
    {
      if (mst[i].u < mst[i].v)
      {
        j = mst[i].u;
        mst[i].u = mst[i].v;
        mst[i].v = j;
      }
    }
    for (i = 0; i < numVertices - 1; ++i)
    {
      for (j = 0; j < numVertices - 1; ++j)
      {
        if (mst[i].u < mst[j].u)
        {
          store = mst[i];
          mst[i] = mst[j];
          mst[j] = store;
        }
      }
    }
  }
  if (strcmp(valid, "none") != 0)
  {
    FILE *file = fopen(valid, "w");
    if (!file)
    {
      printf("Error creating output file\n");
      return;
    }
    for (aux = 0; aux < i; ++aux)
    {
      fprintf(file, "%d ---- %d: %d\n", mst[aux].u, mst[aux].v, mst[aux].weight);
      j += mst[aux].weight;
    }
    fprintf(file, "Total cost: %d\n", j);
  }
  else
  {
    for (aux = 0; aux < i; ++aux)
    {
      printf("%d ---- %d: %d\n", mst[aux].u, mst[aux].v, mst[aux].weight);
      j += mst[aux].weight;
    }
    printf("Total cost: %d\n", j);
  }
}

int main(int argc, char *argv[])
{
  if (argc == 1)
    printf("Please enter input instructions on the command line\n");
  else
  {
    if (argc == 2 && strcmp(argv[1], "-h") == 0)
    {
      printf("----------Kruskal's Algorithm----------\n");
      printf("Commands:\n");
      printf("-o <file> : write the output in a file named <file>\n");
      printf("-f <file> : indicates the input <file>\n");
      printf("-s : shows output in ascending order\n");
      printf("Every graph must have a 0 vertex and for all v in V, v belongs to [0, |V| - 1]\n");
      printf("e.g a graph with 5 vertices then V = {0,1,2,3,4}\n");
      printf("When -f is passed, the next acceptable input is <file> or -s\n");
      printf("If -s is the argument after -f, then <file> has to be next\n");
      printf("When -o is passed, the next input has to be the output file name\n");
    }
    else
    {
      int arqInput, source = -1, arqOutput;
      bool sort = false, valid = false;
      int i, aux = 0, arr[MAX];
      for (i = 1; i < argc; ++i)
      {
        if (strcmp(argv[i], "-h") == 0 && argc > 2)
        {
          printf("-h cannot be called with others input parameters\n");
          return 0;
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
          printf("Kruskal's algorithm does not accept final vertices\n");
          return 0;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
          if (strcmp(argv[i + 1], "-s") != 0)
            arqInput = i + 1;
          else if (strcmp(argv[i + 1], "-s") == 0 && i + 2 < argc)
            arqInput = i + 2;
        }
        if (strcmp(argv[i], "-s") == 0)
          sort = i;
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
          printf("Kruskal's algorithm does not accept initial vertices\n");
        }
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        {
          arqOutput = i + 1;
          valid = true;
        }
      }
      i = 0;
      FILE *file = fopen(argv[arqInput], "r");
      if (file)
      {
        while (!feof(file))
        {
          fscanf(file, "%d", &i);
          arr[aux] = i;
          ++aux;
        }
        fclose(file);
        int numVertices = arr[0], numEdges = arr[1];
        struct Graph *graph = newGraph(numEdges);
        aux = 0;
        for (i = 0; i < numEdges; ++i)
        {
          graph->edge[i].v = arr[aux + 2];
          graph->edge[i].u = arr[aux + 3];
          graph->edge[i].weight = arr[aux + 4];
          aux += 3;
        }
        //kruskal(graph, arr[0], arr[1]);
        if (valid && strcmp(argv[arqInput], argv[arqOutput]) != 0)
          kruskal(graph, arr[0], arr[1], sort, argv[arqOutput]);
        else if (valid && strcmp(argv[arqInput], argv[arqOutput]) == 0)
        {
          printf("The output and input file must have a different name\n");
          return 0;
        }
        else if (valid)
        {
          if (strcmp(argv[arqOutput], "none") == 0)
            kruskal(graph, arr[0], arr[1], sort, "None");
        }
        else
        {
          kruskal(graph, arr[0], arr[1], sort, "none");
        }
      }
      else
      {
        printf("Input file doesn't exists or cannot be opened. Please try a valid file name\n");
      }
    }
    return 0;
  }
}