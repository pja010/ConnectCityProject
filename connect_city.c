/*
 * connect_city.c -- program that   computes shortest set of edges in graph 
*
* Input: data file, each line      representing edge in graph, composed of edgeID, startNodeID, endNodeID, length.
* 
* Output: shortest set of connected edges.
*
* Reference:
* https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
*/

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc == 3) {
    char* inputfile = argv[1];
    char* outputfile = argv[2];
    FILE * fp;
    FILE * out;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    double input[200000][3];
    int count = 0;
    int i;
    int j;
    char * token;
    fp = fopen(inputfile, "r");
    out = fopen(outputfile, "w");
    while  ((read = getline(&line, &len, fp)) != -1) {
      token = strtok(line, " ");
      token = strtok(NULL, " ");
      input[count][0] = atof(token);
      token = strtok(NULL, " ");
      input[count][1] = atof(token);
      token = strtok(NULL, " ");
      input[count][2] = atof(token);
      count += 1;
    }
    double cm = 0;
    for (i=0; i< count; i++){
      if (input[i][0] > cm) {
	cm = input[i][0];
      }
      if (input[i][1] > cm) {
	cm = input[i][1];
      }
    }
    int max;
    max = (int)cm;
    max += 1;
    double *matrix[max];
    for (i=0; i< max; i++) {
      matrix[i] = (double*)malloc(sizeof(double) * max);
    }
    for (i=0; i< max; i++) {
      for (j=0; j<max; j++) {
	matrix[i][j] = 0;
      }
    }
    for (i=0; i< count; i++){
      matrix[(int)input[i][0]][(int)input[i][1]] = input[i][2];
      matrix[(int)input[i][1]][(int)input[i][0]] = input[i][2];
    }
    
    int V=max;
    int parent[V];
    int key[V];
    bool mstSet[V];
    int min, min_index;
    int u;
    double sum = 0;
    for (i=0;i<V;i++){
      key[i] = INT_MAX, mstSet[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;
    for( int count = 0; count < V-1; count++) {
      min = INT_MAX;
      for(int v = 0 ; v< V; v++){
	if (mstSet[v] == false && key[v] < min){
	  min= key[v], min_index = v;
	}
      }
      u = min_index;
      mstSet[u] = true;
      for ( int v= 0; v< V; v++) {
	if (matrix[u][v] && mstSet[v] == false && matrix[u][v] < key[v]){
	  parent[v] = u;
	  key[v] = matrix[u][v];
	}
      }
    }
    for(i = 1; i< V; i++){
      sum += matrix[i][parent[i]];
      fprintf(out,"%d, %d, %f\n", parent[i], i, matrix[i][parent[i]]);
    }
    printf("sum of weighted: %f\n", sum);
    fclose(fp);
    fclose(out);
    return 0;
  }
  else{
    printf("%s\n", "Usage: ./project inputfile outputfile");
    return 1;
  }
}
 
