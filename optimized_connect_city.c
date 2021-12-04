// Reference: MIN Heap implementation: https://www.geeksforgeeks.org/binary-heap/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE * out;

struct AdjListNode {
	int dest;
	double weight;
	struct AdjListNode* next;
};

struct AdjList {
	struct AdjListNode* head; 
};

struct Graph {
	int V;
	struct AdjList* array;
};

struct MinHeapNode {
	int v;
	int key;
};

struct MinHeap {
	int size; 
	int capacity; 
	int* pos; 
	struct MinHeapNode** array;
};

struct AdjListNode* new(int dest, double weight)
{
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;
	return graph;
}

void addEdge(struct Graph* graph, int src, int dest, double weight)
{
	struct AdjListNode* newNode = new(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
	newNode = new(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

struct MinHeapNode* newMinHeapNode(int v, int key)
{
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->key = key;
	return minHeapNode;
}

struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->pos = (int*)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
		smallest = right;

	if (smallest != idx) {
		struct MinHeapNode* smallestNode = minHeap->array[smallest];
		struct MinHeapNode* idxNode = minHeap->array[idx];
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;
	struct MinHeapNode* root = minHeap->array[0];
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;
	--minHeap->size;
	minHeapify(minHeap, 0);
	return root;
}

void decreaseKey(struct MinHeap* minHeap, int v, int key)
{
	int i = minHeap->pos[v];
	minHeap->array[i]->key = key;
	while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

bool isInMinHeap(struct MinHeap* minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;
}

int main(int argc, char* argv[]){
  if (argc == 3) {
    char* inputfile = argv[1];
    char* outputfile = argv[2];
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    double input[200000][3];
    int count = 0;
    int i;
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
    int V = max;
    struct Graph* graph = createGraph(V);
    for (i=0; i< count; i++){
      addEdge(graph, input[i][0], input[i][1], input[i][2]);
    }
    int parent[V];
    double key[V];
    double sum = 0;
	
    struct MinHeap* minHeap = createMinHeap(V);

    for (int v = 1; v < V; ++v) {
      parent[v] = -1;
      key[v] = INT_MAX;
      minHeap->array[v] = newMinHeapNode(v, key[v]);
      minHeap->pos[v] = v;
    }

    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0] = 0;
    minHeap->size = V;
    while (!isEmpty(minHeap)) {
      struct MinHeapNode* min = extractMin(minHeap);
      int u = min->v; 
      struct AdjListNode* cur = graph->array[u].head;
      while (cur != NULL) {
	int v = cur->dest;
	if (isInMinHeap(minHeap, v) && cur->weight < key[v]) {
	  key[v] = cur->weight;
	  parent[v] = u;
	  decreaseKey(minHeap, v, key[v]);
	}
	cur = cur->next;
      }
    }
	
    for (int i = 1; i < V; ++i) {
      sum += key[i];
      fprintf(out, "%d, %d, %f\n", parent[i], i, key[i]);
    }
    printf("sum of edges: %f\n", sum);
    return 0;
  }  
  else{
    printf("%s\n", "Usage: ./project inputfile outputfile");
    return 1;
  }
}
