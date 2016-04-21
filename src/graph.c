#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"

struct _graph_node {
  graph_vertex_t vertex;
  int weight;
  struct _graph_node *next;
};

struct _graph {
  int V, E;
  bool weighted;
  graph_type_e type;
  graph_node_t **adjlist;
};

graph_t *graph_new(int V, graph_type_e graph_type, bool weighted) {
  graph_t *graph = NULL;
  
  if(V > 0 &&
      (graph = (graph_t*)malloc(sizeof(struct _graph))) != NULL) {
    graph->V = V;
    graph->E = 0;
    graph->type = graph_type;
    graph->weighted = weighted;
    graph->adjlist = 
      (graph_node_t**)malloc(V * sizeof(struct _graph_node*));
  }
  
  return graph;
}

void graph_free(graph_t *graph) {
  int i;
  
  for(i = 0; i < graph->V; ++i) {
    graph_node_t *head = graph->adjlist[i];
    while(head != NULL) {
      graph_node_t *temp = head;
      head = head->next;
      free(temp);
    }
  }
  free(graph->adjlist);
  free(graph);
}

int graph_vertices(graph_t *graph) {
  return graph->V;
}

int graph_edges(graph_t *graph) {
  return graph->E;
}

bool graph_weighted(graph_t *graph) {
  return graph->weighted;
}

graph_type_e graph_type(graph_t *graph) {
  return graph->type;
}

void graph_add_edge(graph_t *graph, graph_vertex_t u, graph_vertex_t v,
    int w) {
  if((u > 0 && u <= graph->V) && (v > 0 && v <= graph->V)) {
    graph_node_t *x = (graph_node_t*)malloc(sizeof(struct _graph_node));

    if(x != NULL) {
      x->vertex = v;
      x->weight = graph->weighted ? w : 0;
      x->next = graph->adjlist[u - 1];
      graph->adjlist[u - 1] = x;
      
      if(graph->type == GRAPH_UNDIRECTED) {
        graph_node_t *y = (graph_node_t*)malloc(sizeof(struct _graph_node));
        
        if(y != NULL) {
          y->vertex = u;
          y->weight = graph->weighted ? w : 0;
          y->next = graph->adjlist[u - 1];
          graph->adjlist[u - 1] = y;
        }
      }
    }
    else {
      exit(EXIT_FAILURE);
    }
    
    graph->E++;
  }
}

void bellman_ford(graph_t *graph, graph_vertex_t s, int *d, bool reverse) {
  int i, j, e;

  for(i = 0; i < graph->V; ++i)
    d[i] = INT_MAX;
  d[s - 1] = 0;

  for(i = 0; i < graph->V; ++i) {
    bool changes = false;

    for(j = 0, e = 0; j < graph->V && e < graph->E; ++j) {
      graph_node_t *node = graph->adjlist[j];
      
      while(node) {
        graph_vertex_t u = (reverse ? node->vertex : j + 1);
        graph_vertex_t v = (reverse ? j + 1 : node->vertex);
        
        if(d[u - 1] != INT_MAX && d[v - 1] > d[u - 1] + node->weight) {
          changes = true;
          d[v - 1] = d[u - 1] + node->weight;
        }
        ++e;
        node = node->next;
      }
    }

    if(!changes) break;
  }
}
