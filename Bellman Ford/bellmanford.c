#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

struct Edge
{
  int v; //vertex 1
  int u; //vertex 2
  int d; //weight between vertex 1 and vertex 2
};
struct G
{
  int V;             //|V| of G
  int E;             //|E| of G
  struct Edge *edge; //E of G
};

void bellmanFord(struct G *graph, int initialVertex, char valid[], bool sort)
{
  int i, j, numVertices = graph->V, numEdges = graph->E, inf = 100000, u, v, d;
  int dist[numVertices];
  for (i = 0; i < numVertices; ++i)
  {
    dist[i] = inf;
  }
  dist[initialVertex] = 0;
  for (i = 0; i < numVertices - 1; ++i)
  {
    for (j = 0; j < numEdges; ++j)
    {
      //with u,v and d variables we avoid segmentation fault issues
      v = graph->edge[j].v;
      u = graph->edge[j].u;
      d = graph->edge[j].d;
      if (dist[v] > dist[u] + d && dist[u] != inf)
      {
        dist[v] = dist[u] + d;
      }
    }
  }
//with this loop, we check if there is any cycle with a negative weight
  for (i = 0; i < numEdges; ++i)
  {
    v = graph->edge[i].v;
    u = graph->edge[i].u;
    d = graph->edge[i].d;
    if (dist[v] > dist[u] + d && dist[u] != inf)
    {
      printf("A negative weight cycle has been found. Please, try another graph\n");
      return;
    }
  }
  //if -s parameter was passed then we'll sort dist array and store vertex in index
  if (sort)
  {
    int index[numVertices], valueStore;
    for (i = 0; i < numVertices; ++i)
    {
      index[i] = i;
    }
    for (i = 0; i < numVertices; ++i)
    {
      for (j = i + 1; j < numVertices; ++j)
      {
        if (dist[i] < dist[j])
        {
          valueStore = dist[i];
          dist[i] = dist[j];
          dist[j] = valueStore;
          valueStore = index[i];
          index[i] = index[j];
          index[j] = valueStore;
        }
      }
    }
    //If -o parameters was passed, create a file named as *valid then write output in it
    if (strcmp(valid, "none") != 0)
    {
      FILE *file = fopen(valid, "w");
      if (!file)
      {
        printf("Error creating output file\n");
        return;
      }
      else
      {
        for (i = 0; i < numVertices; ++i)
        {
          fprintf(file, "The distance of the source vertex %d to vertex %d is %d\n", initialVertex, index[i], (-1) * dist[i]);
        }
      }
    }
    else
    {
      for (i = 0; i < numVertices; ++i)
      {
        printf("The distance of the source vertex %d to vertex %d is %d\n", initialVertex, index[i], (-1) * dist[i]);
      }
    }
  }
  else
  {
    if (strcmp(valid, "none") != 0)
    {
      FILE *file = fopen(valid, "w");
      if (!file)
      {
        printf("Error creating output file\n");
        return;
      }
      else
      {
        for (i = 0; i < numVertices; ++i)
        {
          fprintf(file, "The distance of the source vertex %d to vertex %d is %d\n", initialVertex, i, (-1) * dist[i]);
        }
      }
    }
    else
    {
      for (i = 0; i < numVertices; ++i)
      {
        printf("The distance of the source vertex %d to vertex %d is %d\n", initialVertex, i, (-1) * dist[i]);
      }
    }
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
      printf("---------- Bellman-Ford Algorithm ----------\n");
      printf("Commands:\n");
      printf("-o <file> : write the output in a file named <file>\n");
      printf("-f <file> : indicates the input <file>\n");
      printf("-s : shows output in ascending order\n");
      printf("-i : indicates source vertex\n");
      printf("Every graph must have a 0 vertex and for all v in V, v belongs to [0, |V| - 1]\n");
      printf("e.g a graph with 5 vertices then V = {0,1,2,3,4}\n");
      printf("When -f is called, the next acceptable input is <file> or -s\n");
      printf("If -s is the argument after -f, then <file> has to be next\n");
    }
    else
    {
      int arqInput, source, arqOutput;
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
          printf("Bellman-Ford algorithm only accepts initial vertices\n");
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
          source = atoi(argv[i + 1]);
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
        //creating an array with file values
        while (!feof(file))
        {
          fscanf(file, "%d", &i);
          arr[aux] = i;
          ++aux;
        }
        fclose(file);
        //creating a graph
        struct G *graph = (struct G *)malloc(sizeof(struct G));
        graph->V = arr[0];
        graph->E = arr[1];
        graph->edge = (struct Edge *)malloc(graph->E * sizeof(struct Edge));
        aux = 0;
        //filling graph
        for (i = 0; i < graph->E; ++i)
        {
          graph->edge[i].v = arr[aux + 2];
          graph->edge[i].u = arr[aux + 3];
          graph->edge[i].d = arr[aux + 4];
          aux += 3;
        }
        //output file cannot has the same name of input file
        if (valid && strcmp(argv[arqInput], argv[arqOutput]) != 0)
          bellmanFord(graph, source, argv[arqOutput], sort);
        else if (valid && strcmp(argv[arqInput], argv[arqOutput]) == 0)
        {
          printf("The output and input file must have a different name\n");
          return 0;
        }
        else if (valid)
        {
          if (strcmp(argv[arqOutput], "none") == 0)
            bellmanFord(graph, source, "None", sort);
        }
        else
        {
          bellmanFord(graph, source, "none", sort);
        }
      }
      else
      {
        printf("Input file doesn't exists or cannot be opened. Please try a valid file name\n");
      }
    }
  }
  return 0;
}
