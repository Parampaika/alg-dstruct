It is necessary to create a program that implements breadth-first traversal of the graph. A direct traversal (pre-order) should be implemented. The graph is given by a list of edges. The code is implemented only in the C language, when submitting, you should select the C language. After submitting, press the orange Play button to find out the result. The input is fed into the stdin stream. The first line contains the number of vertices in the graph. Then, line by line, the edges given by a pair of vertices incident to it. The vertices are numbered starting from 0. It is not guaranteed that the graph is connected. It is necessary to start traversing the graph from the vertex with number 0. When choosing the next vertex from adjacent to the current one, the vertex with the smallest number should be selected. The output is expected to be a list of vertices in space-separated order.
The code is implemented only in the C language, when submitting, you should select the C language.
After submitting, press the orange Play button to find out the result.
The input is fed into the stdin stream. The first line contains
the number of vertices in the graph. Then, line by line, the edges given by a pair of vertices incident to it.
The vertices are numbered starting from 0. It is not guaranteed that the graph is connected.
It is necessary to start traversing the graph from the vertex with the number 0.
When choosing the next vertex from adjacent to the current one, you should select the vertex with the smallest
number.
The output is expected to be a list of vertices in space-separated order.
Examples of inputs and outputs
Example 1
stdin
5
0 4
13
fourteen

stdout
0 4 1 3

Example 2
stdin
ten
0 1
0 6
0 8
12
13
16
2 8
2 9
3 7
4 6
4 7
4 8
5 6
7 8

stdout
0 1 6 8 2 3 4 5 7 9