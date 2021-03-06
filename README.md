# Euclidean-Minimum-Spanning-Tree
 A C program that determines a Euclidean Minimum Spanning Tree for set of 2D points interpreted as the vertices of a weighted undirected graph.

- Input is read from a standard input (the first line is one integer value: n (the number of points), and the remaining n lines will each contain two ints defning a point as an x-coordinate and a y-coordinate)
- While reading the input, each point is echoed (in the original input sequence), x-coordinate, and y-coordinate. 
- The edges are generated by computing the distance between each pair of points as a double. 
- While executing Kruskal's method, the positions of the two points for each edge, the distance between them, and wheter the edge is included in the EMST or discarded will all be indicated. 
- The code may terminate as soon as n-1 edges have been included. 
- The last ouput line will give the total weight of the EMST.
