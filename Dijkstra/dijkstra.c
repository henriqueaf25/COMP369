#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100

void dijkstra(int source, int numVertices, int matrix[numVertices][numVertices], int finalVertex, char valid[], bool sort)
{
  int i, j, k, min, dist[numVertices], minInf;
  bool tree[numVertices];
  for (i = 0; i < numVertices; ++i)
  {
    dist[i] = 99999;
    tree[i] = false;
  }
  dist[source] = 0;
  for (k = 0; k < numVertices - 1; ++k)
  {
    minInf = 99999;
    for (i = 0; i < numVertices; ++i)
    {
      if (tree[i] == false && dist[i] <= minInf)
      {
        minInf = dist[i];
        min = i;
      }
    }
    minInf = 99999;
    tree[min] = true;
    for (i = 0; i < numVertices; ++i)
    {
      if (!tree[i] && matrix[min][i] && dist[min] != minInf && dist[min] + matrix[min][i] < dist[i])
      {
        dist[i] = dist[min] + matrix[min][i];
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
    else
    {
      if (!finalVertex)
      {
        j = 0;
        for (i = 0; i < numVertices; ++i)
        {
          fprintf(file, "Shortest path from source vertex to %dº: %d\n", i, dist[i]);
        }
      }
      else
      {
        int cost = 0;
        for (i = source; i <= finalVertex; ++i)
        {
          cost += dist[i];
        }
        fprintf(file, "%d\n", cost);
      }
    }
  }
  else
  {
    if (!finalVertex)
    {
      j = 0;
      for (i = 0; i < numVertices; ++i)
      {
        printf("Shortest path from source vertex to %dº: %d\n", i, dist[i]);
      }
    }
    else
    {
      int cost = 0;
      for (i = source; i <= finalVertex; ++i)
      {
        cost += dist[i];
      }
      printf("%d\n", cost);
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
      printf("----------Dijkstra's Algorithm----------\n");
      printf("Commands:\n");
      printf("-o <file> : write the output in a file named <file>\n");
      printf("-f <file> : indicates the input <file>\n");
      printf("-i : indicates source vertex\n");
      printf("-l : indicates final vertex\n");
      printf("Every graph must have a 0 vertex and for all v in V, v belongs to [0, |V| - 1]\n");
      printf("e.g a graph with 5 vertices then V = {0,1,2,3,4}\n");
      printf("When -f is passed, the next acceptable input is <file> or -s\n");
      printf("If -s is the argument after -f, then <file> has to be next\n");
      printf("When -o is passed, the next input has to be the output file name\n");
    }
    else
    {
      int arqInput, source = 0, arqOutput, final = 0;
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
          final = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        {
          if (strcmp(argv[i + 1], "-s") != 0)
            arqInput = i + 1;
          else if (strcmp(argv[i + 1], "-s") == 0 && i + 2 < argc)
            arqInput = i + 2;
        }
        if (strcmp(argv[i], "-s") == 0)
          sort = true;
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
      if (source > final && final != 0)
      {
        printf("Source vertex cannot be larger than final vertex\n");
        return 0;
      }
      FILE *file = fopen("graph.txt", "r");
      int j = 0, k = 2;
      i = 0;
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
        int numEdges = arr[1], numVertices = arr[0];
        int G[numEdges][3], adj[numVertices][numVertices];
        for (i = 0; i < numEdges; ++i)
        {
          for (j = 0; j < 3; ++j)
          {
            G[i][j] = arr[k];
            ++k;
          }
        }
        for (i = 0; i < numVertices; ++i)
        {
          for (j = 0; j < numVertices; ++j)
          {
            adj[i][j] = 0;
          }
        }
        for (i = 0; i < numEdges; ++i)
        {
          adj[G[i][0]][G[i][1]] = G[i][2];
          adj[G[i][1]][G[i][0]] = G[i][2];
        }
        //dijkstra(0, numVertices, adj);
        if (final)
        {
          if (valid && strcmp(argv[arqInput], argv[arqOutput]) != 0)
            dijkstra(source, numVertices, adj, final, argv[arqOutput], sort);
          else if (valid && strcmp(argv[arqInput], argv[arqOutput]) == 0)
          {
            printf("The output and input file must have a different name\n");
            return 0;
          }
          else if (valid)
          {
            if (strcmp(argv[arqOutput], "none") == 0)
              dijkstra(source, numVertices, adj, final, "None", sort);
          }
          else
          {
            dijkstra(source, numVertices, adj, final, "none", sort);
          }
        }
        else
        {
          if (valid && strcmp(argv[arqInput], argv[arqOutput]) != 0)
            dijkstra(source, numVertices, adj, 0, argv[arqOutput], sort);
          else if (valid && strcmp(argv[arqInput], argv[arqOutput]) == 0)
          {
            printf("The output and input file must have a different name\n");
            return 0;
          }
          else if (valid)
          {
            if (strcmp(argv[arqOutput], "none") == 0)
              dijkstra(source, numVertices, adj, 0, "None", sort);
          }
          else
          {
            dijkstra(source, numVertices, adj, 0, "none", sort);
          }
        }
      }
      else
      {
        printf("File doesn't exists or cannot be opened. Please try a valid file name\n");
      }
    }
  }
  return 0;
}