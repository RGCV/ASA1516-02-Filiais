#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

struct _graph_edge {
  graph_vertex_t u, v;
  int w;
};

struct _graph {
  int V, E;
  int size;
  graph_edge_t **edges;
};

graph_t *graph_new(int V, int E) {
  graph_t *graph = NULL;
  
  if(V > 0 &&
      (graph = (graph_t*)malloc(sizeof(struct _graph))) != NULL) {
    graph->V = V;
    graph->size = E;
    graph->E = 0;
    graph->edges = 
      (graph_edge_t**)malloc(E * sizeof(struct _graph_edge*));
  }
  
  return graph;
}

void graph_free(graph_t *graph) {
  int i;
  
  for(i = 0; i < graph->E; ++i)
    free(graph->edges[i]);
  
  free(graph->edges);
  free(graph);
}

int graph_vertices(graph_t *graph) {
  return graph->V;
}

int graph_edges(graph_t *graph) {
  return graph->E;
}

void graph_add_edge(graph_t *graph, graph_vertex_t u, graph_vertex_t v,
    int w) {
  if(graph->E < graph->size) {
    graph_edge_t *edge = (graph_edge_t*)malloc(sizeof(struct _graph_edge));
    if(edge != NULL) {
      edge->u = u;
      edge->v = v;
      edge->w = w;
      
      graph->edges[graph->E++] = edge;
    }
    else {
      free(edge);
    }
  }
}

void BellmanFord(graph_t *graph, graph_vertex_t s, int *d) {
  int i, j;
  int V = graph->V, E = graph->E;
  
  for(i = 0; i < V; ++i) {
    d[i] = INT_MAX;
  }
  d[s - 1] = 0;
  
  for(i = 0 ; i < V - 1; ++i) {
    bool changes = false;
    
    for(j = 0; j < E; ++j) {
      graph_vertex_t u = graph->edges[j]->u;
      graph_vertex_t v = graph->edges[j]->v;
      int w = graph->edges[j]->w;
      
      if(d[u - 1] != INT_MAX && d[v - 1] > d[u - 1] + w) {
        changes = true;
        d[v - 1] = d[u - 1] + w;
      }
    }
    
    if(!changes) break;
  }
}