#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

int main() {
  int V, E, S, i, j;
  int total_cost, meeting_point;
  int *sources, **d;
  graph_t *graph;
  
  /* Initialization. */
  assert(scanf("%d %d %d", &V, &S, &E) == 3);
  assert(V > 1 && S > 1 && E > 0);
  
  graph = graph_new(V, E);
  assert(graph != NULL);
  
  sources = (int*)malloc(S * sizeof(int));
  assert(sources != NULL);
  
  for(i = 0; i < S; ++i)
    assert(scanf("%d", &sources[i]) == 1);

  /* Construction. */
  while(E-- > 0) {
    int u, v, w;
    assert(scanf("%d %d %d", &u, &v, &w) == 3);
    graph_add_edge(graph, u, v, w);
  }
  
  d = (int**)malloc(S * sizeof(int*));
  assert(d != NULL);
  for(i = 0; i < S; ++i)
    assert((d[i] = (int*)malloc(V * sizeof(int))) != NULL);
  
  /* Caminhos mais curtos a partir das filiais. */
  for(i = 0; i < S; ++i)
    BellmanFord(graph, sources[i], d[i]);
  
  total_cost = INT_MAX;
  for(i = 0; i < V; ++i) {
    int sum = 0;
    
    for(j = 0; j < S; ++j) {
      if (d[j][i] == INT_MAX) {
        sum = INT_MAX;
        break;
      }
      sum += d[j][i];
    }
    if (sum < total_cost){
      total_cost = sum;
      meeting_point = i + 1;
    }
  }
  
  if(total_cost == INT_MAX){
    printf("N");
  }
  else {
    printf("%d %d\n", meeting_point, total_cost);
    for(i = 0; i < S; ++i){
      printf("%d ", d[i][meeting_point - 1]);
    }
  }
  printf("\n");
  
  /* FREEDOM! */
  for(i = 0; i < S; ++i)
    free(d[i]);
  
  free(d);
  free(sources);
  graph_free(graph);
  
  return EXIT_SUCCESS;
}