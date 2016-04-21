#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

int main() {
  int V, E, S, i, j;
  int *d, *x;
  int total_cost;
  graph_vertex_t *sources, meeting_point;
  graph_t *graph = NULL;
  
  /* Input processing / Initialization. */
  assert(scanf("%d %d %d", &V, &S, &E) == 3);
  assert(V > 1 && S > 1 && E > 0);
  
  graph = graph_new(V, GRAPH_DIRECTED, true);
  assert(graph != NULL);
  
  sources = (graph_vertex_t*)malloc(S * sizeof(graph_vertex_t));
  assert(sources != NULL);
  
  for(i = 0; i < S; ++i)
    assert(scanf("%d", &sources[i]) == 1);

  while(E-- > 0) {
    int u, v, w;
    assert(scanf("%d %d %d", &u, &v, &w) == 3);
    graph_add_edge(graph, u, v, w);
  }

  d = (int*)malloc(V * sizeof(int));
  assert(d != NULL);
  x = (int*)malloc(V * sizeof(int));
  assert(x != NULL);
  memset(x, 0, V);

  /* Bellman-Ford application to the sources. */
  for(i = 0; i < S; ++i) {
    bellman_ford(graph, sources[i], d);
    for(j = 0; j < V; ++j) {
      if(d[j] == INT_MAX) x[j] = INT_MAX;
      else if(x[j] != INT_MAX) x[j] += d[j];
    }
  }

  /* Finding the meeting point. */
  total_cost = INT_MAX;
  for(i = 0; i < V; ++i) {
    if(x[i] < total_cost) {
      total_cost = x[i];
      meeting_point = i + 1;
    }
  }

  /* Output data. */
  if(total_cost == INT_MAX) {
    printf("N\n");
  }
  else {
    printf("%d %d\n", meeting_point, total_cost);
    antibellman_ford(graph, meeting_point, d);
    for(i = 0; i < S; ++i) {
      printf("%d ", d[sources[i] - 1]);
    }
    printf("\n");
  }
  
  /* Free previously allocated resources. */
  free(d);
  free(x);
  free(sources);
  graph_free(graph);
  
  return EXIT_SUCCESS;
}
