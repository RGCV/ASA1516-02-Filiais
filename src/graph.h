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

/* Enumerate values to identify graph type */
typedef enum { GRAPH_UNDIRECTED = 0, GRAPH_DIRECTED } graph_type_e;

/* Adjacency list node. */
typedef struct _graph_node graph_node_t;

/* Graph structure. */
typedef struct _graph      graph_t;

/* Function prototypes */
/* Create a new graph. */
graph_t     *graph_new       (int V, graph_type_e graph_type, bool weighted);

/* Free memory allocated associated with the given graph. */
void         graph_free      (graph_t *graph);

/* Returns the number of vertices in the graph. */
int          graph_vertices  (graph_t *graph);

/* Returns the number of edges in the graph. */
int          graph_edges     (graph_t *graph);

/* Returns true if the graph is weighted. Returns false, otherwise. */
bool         graph_weighted  (graph_t *graph);

/* Returns the graph's type (DIRECTED or UNDIRECTED) */
graph_type_e graph_type      (graph_t *graph);

/* Adds an edge to the graph. If the graph isn't weighted, w is ignored.
  If it is, then assigns a weight w to the edge (u,v). Furthermore, if the
  graph is undirected, the weight is clearly in both ways. */
void         graph_add_edge  (graph_t *graph, graph_vertex_t u, graph_vertex_t v,
                               int w);

/* Executes the Bellman-Ford shortest path-finding algorithm given a source
  vertex s. If reverse is true, the algorithm uses the edges in the opposite
  direction, simulating an application of the Bellman-Ford algorithm over the
  antigraph. */
void         bellman_ford    (graph_t *graph, graph_vertex_t s, int *d,
                               bool reverse);

#endif /* _GRAPH_H_ */