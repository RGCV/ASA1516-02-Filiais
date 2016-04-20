/*
  Define a basic implementation of a weighted digraph.
  Uses a list of edges. It inserts the edges in the order
  of insertion and examined in that order.

  Being a basic implementation, it isn't meant for generic
  applications given the specific type definition, for example.
*/

#ifndef _GRAPH_H_
#define _GRAPH_H_

/* Type definitions */
/* Defines the type of a vertex (simple int). */
typedef int                graph_vertex_t;

/* Graphs' edge. */
typedef struct _graph_edge graph_edge_t;

/* Graph structure. */
typedef struct _graph      graph_t;

/* Function prototypes */
/* Create a new graph. */
graph_t     *graph_new       (int V, int E);

/* Free memory allocated associated with the given graph. */
void         graph_free      (graph_t *graph);

/* Returns the number of vertices in the graph. */
int          graph_vertices  (graph_t *graph);

/* Returns the number of edges in the graph. */
int          graph_edges     (graph_t *graph);

/* Adds an edge to the graph. If the graph isn't weighted, w is ignored.
  If it is, then assigns a weight w to the edge (u,v). Furthermore, if the
  graph is undirected, the weight is clearly in both ways. */
void         graph_add_edge  (graph_t *graph, graph_vertex_t u, graph_vertex_t v,
                               int w);

/* Executes the Bellman-Ford shortest path-finding algorithm given a source
  vertex s. */
void         BellmanFord     (graph_t *graph, graph_vertex_t s, int *d);

#endif /* _GRAPH_H_ */