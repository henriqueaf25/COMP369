#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

void Prim(int *graph, int numVertices, int numEdges, int source, bool sort, char valid[])
{
  /*the visited array represents vertices that has been visited; G represents our graph as a matrix; AdjG is the G adjacency matrix*/
  int visited[numVertices], G[numEdges][3], AdjG[numVertices][numVertices], i, j, k = 2, aux = 0, totalcost = 0, sorted[numVertices - 1][2], swap1, swap2;
  //set all visited positions to false except for the source
  memset(visited, false, sizeof(visited));
  visited[source] = true;
  //adding edges and their respective weight to G matrix
  for (i = 0; i < numEdges; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      G[i][j] = graph[k];
      ++k;
    }
  }
  //creating an adjacency matrix;

  for (i = 0; i < numVertices; ++i)
  {
    for (j = 0; j < numVertices; ++j)
    {
      AdjG[i][j] = 0;
    }
  }
  for (i = 0; i < numEdges; ++i)
  {
    AdjG[G[i][0]][G[i][1]] = G[i][2];
    AdjG[G[i][1]][G[i][0]] = G[i][2];
  }

  /*At this point, for every vertex we going to find all adjacent edges 
  and calculate the weight between the picked vertex and adjacents vertices,
  take the one with lowest weight, if it's already in visited vertices, take another
  */
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
      while (aux < numVertices - 1)
      {
        int minInf, vertex1 = 0, vertex2 = 0;
        minInf = 100000;

        for (i = 0; i < numVertices; ++i)
        {
          if (visited[i])
          {
            for (j = 0; j < numVertices; ++j)
            {
              if (!visited[j] && AdjG[i][j])
              {
                if (minInf > AdjG[i][j])
                {
                  minInf = AdjG[i][j];
                  vertex1 = i;
                  vertex2 = j;
                }
              }
            }
          }
        }
        if (sort)
        {
          sorted[aux][0] = vertex1;
          sorted[aux][1] = vertex2;
          if (sorted[aux][0] > sorted[aux][1])
          {
            swap1 = sorted[aux][0];
            sorted[aux][0] = sorted[aux][1];
            sorted[aux][1] = swap1;
          }
          if (aux == 0)
            fprintf(file, "Normal Solution:\n");
          if (aux == numVertices - 2)
            fprintf(file, "(%d, %d)\n", vertex1, vertex2);
          else
            fprintf(file, "(%d, %d), ", vertex1, vertex2);
        }
        totalcost += AdjG[vertex1][vertex2];
        ++aux;

        visited[vertex2] = true;
      }
      if (!sort)
      {
        fprintf(file, "Total cost: %d\n", totalcost);
      }
      else
      {
        for (i = 0; i < numVertices - 1; ++i)
        {
          for (j = i + 1; j < numVertices - 1; ++j)
          {
            if (sorted[i][0] > sorted[j][0])
            {
              swap1 = sorted[i][0];
              swap2 = sorted[i][1];
              sorted[i][0] = sorted[j][0];
              sorted[i][1] = sorted[j][1];
              sorted[j][0] = swap1;
              sorted[j][1] = swap2;
            }
            else if (sorted[i][0] == sorted[j][0])
            {
              if (sorted[i][1] > sorted[j][1])
              {
                swap1 = sorted[i][1];
                sorted[i][1] = sorted[j][1];
                sorted[j][1] = swap1;
              }
            }
          }
        }

        for (i = 0; i < numVertices - 1; ++i)
        {
          if (i == 0)
            fprintf(file, "Sorted Solution:\n");
          if (i == numVertices - 2)
            fprintf(file, "(%d, %d)\n", sorted[i][0], sorted[i][1]);
          else
            fprintf(file, "(%d, %d), ", sorted[i][0], sorted[i][1]);
        }
      }
      fclose(file);
    }
  }
  else
  {
    while (aux < numVertices - 1)
    {
      int minInf, vertex1 = 0, vertex2 = 0;
      minInf = 100000;

      for (i = 0; i < numVertices; ++i)
      {
        if (visited[i])
        {
          for (j = 0; j < numVertices; ++j)
          {
            if (!visited[j] && AdjG[i][j])
            {
              if (minInf > AdjG[i][j])
              {
                minInf = AdjG[i][j];
                vertex1 = i;
                vertex2 = j;
              }
            }
          }
        }
      }
      if (sort)
      {
        sorted[aux][0] = vertex1;
        sorted[aux][1] = vertex2;
        if (sorted[aux][0] > sorted[aux][1])
        {
          swap1 = sorted[aux][0];
          sorted[aux][0] = sorted[aux][1];
          sorted[aux][1] = swap1;
        }
        if (aux == 0)
          printf("Normal Solution:\n");
        if (aux == numVertices - 2)
          printf("(%d, %d)\n", vertex1, vertex2);
        else
          printf("(%d, %d), ", vertex1, vertex2);
      }
      totalcost += AdjG[vertex1][vertex2];
      ++aux;

      visited[vertex2] = true;
    }
    if (!sort)
    {
      printf("Total cost: %d\n", totalcost);
    }
    else
    {
      for (i = 0; i < numVertices - 1; ++i)
      {
        for (j = i + 1; j < numVertices - 1; ++j)
        {
          if (sorted[i][0] > sorted[j][0])
          {
            swap1 = sorted[i][0];
            swap2 = sorted[i][1];
            sorted[i][0] = sorted[j][0];
            sorted[i][1] = sorted[j][1];
            sorted[j][0] = swap1;
            sorted[j][1] = swap2;
          }
          else if (sorted[i][0] == sorted[j][0])
          {
            if (sorted[i][1] > sorted[j][1])
            {
              swap1 = sorted[i][1];
              sorted[i][1] = sorted[j][1];
              sorted[j][1] = swap1;
            }
          }
        }
      }

      for (i = 0; i < numVertices - 1; ++i)
      {
        if (i == 0)
          printf("Sorted Solution:\n");
        if (i == numVertices - 2)
          printf("(%d, %d)\n", sorted[i][0], sorted[i][1]);
        else
          printf("(%d, %d), ", sorted[i][0], sorted[i][1]);
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
      printf("----------Prim's Algorithm----------\n");
      printf("Commands:\n");
      printf("-o <file> : write the output in a file named <file>\n");
      printf("-f <file> : indicates the input <file>\n");
      printf("-s : shows output in ascending order\n");
      printf("-i : indicates source vertex\n");
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
          printf("Prim's algorithm only accepts initial vertices\n");
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
        if (i == argc - 1 && source == -1)
        {
          printf("Insert source vertex with -i to proceed\n");
          return 0;
        }
      }
      FILE *file = fopen(argv[arqInput], "r");
      if (file)
      {
        int aux = 0, graph[MAX];
        i = 0;
        //storing graph.txt data into an array
        while (!feof(file))
        {
          fscanf(file, "%d", &i);
          graph[aux] = i;
          ++aux;
        }
        fclose(file);
        if (valid && strcmp(argv[arqInput], argv[arqOutput]) != 0)
          Prim(graph, graph[0], graph[1], source, sort, argv[arqOutput]);
        else if (valid && strcmp(argv[arqInput], argv[arqOutput]) == 0)
        {
          printf("The output and input file must have a different name\n");
          return 0;
        }
        else if (valid)
        {
          if (strcmp(argv[arqOutput], "none") == 0)
            Prim(graph, graph[0], graph[1], source, sort, "None");
        }
        else
        {
          Prim(graph, graph[0], graph[1], source, sort, "none");
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