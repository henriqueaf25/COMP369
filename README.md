# Graph Theory Algorithms :
### Every single program has a "./namesourcefile -h" command that shows a guide to execute
## Bellman-Ford Algorithm
The Bellman–Ford algorithm is an algorithm that computes shortest paths from a single source vertex to all of the other vertices in a weighted digraph even with a negative weight.
### Input file used as example: [graph.txt](https://github.com/henriqueaf25/Teoria_dos_Grafos-COMP369/blob/master/Bellman%20Ford/graph.txt);
 ```
5 10
0 1 6
0 2 7
1 2 8
1 4 -4
1 3 5
2 4 9
2 3 -3
3 1 -2
4 3 7
4 0 2
  ```
## Prim's Algorithm
Prim's algorithm is a greedy algorithm that finds a minimum spanning tree for a weighted undirected graph.
### Input file used as example: [graph.txt](https://github.com/henriqueaf25/Teoria_dos_Grafos-COMP369/blob/master/Prim/graph.txt)
 ```
6 8
0 1 5
0 2 4
0 3 2
0 5 6
1 3 1
1 4 7
2 4 6
3 5 1
  ```
## Dijkstra's Algorithm
Dijkstra's algorithm is an algorithm for finding the shortest paths between nodes in a graph. Differente from Bellman-Ford algorithm, Dijkstra's don't accept negative weighted edges but in the other hand it's more efficient. 
### Input file used as example: [graph.txt](https://github.com/henriqueaf25/Teoria_dos_Grafos-COMP369/blob/master/Dijkstra/graph.txt)
 ```
4 6
0 1 4
0 2 3
1 3 3
2 1 2
3 2 9
3 0 3
  ```
## Kruskal's Algorithm
Kruskal's algorithm finds a minimum spanning forest of an undirected edge-weighted graph. If the graph is connected, it finds a minimum spanning tree.
