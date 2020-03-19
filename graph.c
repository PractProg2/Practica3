/**
* @file graph.c
* @author Gonzalo Arcas & Ciro Alonso
* @date 19 February 2020
* @brief ADT graph
*
* @details Definicion de las funciones de graph.h
*
* @see
*/

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

#define MAX_NODES 1064
#define NAME_L 64 /*!< Maximum node name length */

struct _Graph
{
    Node *nodes[MAX_NODES];                 /*!<Array with the graph nodes */
    Bool connections[MAX_NODES][MAX_NODES]; /*!<Adjacency matrix */
    int num_nodes;                          /*!<Total number of nodes in te graph */
    int num_edges;                          /*!<Total number of connection in the graph */
};


//funciones privadas

int find_node_index(const Graph * g, long nId1);

int* graph_getConnectionsIndex (const Graph * g, int index);


// It returns the index of the node with id nId1
int find_node_index(const Graph *g, long nId1){
    int i;
    if (!g) return -1;

    for (i = 0; i < g->num_nodes; i++){

        if (node_getId(g->nodes[i]) == nId1) return i;
    }
    // ID not found
    return -1;
}

// It returns an array with the indices of the nodes connected to the node
// whose index is index
// It also allocates memory for the array.
int *graph_getConnectionsIndex(const Graph *g, int index)
{
    int *array = NULL, i, j = 0, size;

    if (!g) return NULL;

    if (index < 0 || index > g->num_nodes) return NULL;

    // get memory for the array
    size = node_getConnect(g->nodes[index]);
    array = (int *)malloc(sizeof(int) * size);
    if (!array){
        // print error message
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    // assign values to the array with the indices of the connected nodes
    for (i = 0; i < g->num_nodes; i++){
        if (g->connections[index][i] == TRUE){
            array[j++] = i;
        }
    }
    return array;
}

//Interfaz publica

Graph *graph_init(){
    Graph *g = NULL;
    int i, j;

    g = (Graph *) malloc (sizeof(Graph));
    if (!g) return NULL;

    g->num_nodes = 0;
    g->num_edges = 0;
    for (i=0; i<MAX_NODES; i++){
        g->nodes[i] = NULL;
        for (j=0; j<MAX_NODES; j++){
            g->connections[i][j] = FALSE;
        }
    }

    return g;
}

void graph_free(Graph *g){
    int i;

    for (i=0; i<MAX_NODES; i++){
        node_free(g->nodes[i]);
    }

    free(g);
}


Status graph_insertNode(Graph *g, const Node *n){
    Node *aux = NULL;
    int index = -1, connect;
    if (!g || !n || g->num_nodes >= MAX_NODES) return ERROR;

    index = find_node_index(g, node_getId(n));

    aux = node_copy(n);
    if (!aux) return ERROR;

    if (index == -1){

        g->nodes[g->num_nodes] = aux;
        node_setNConnect(g->nodes[g->num_nodes],0);
        g->num_nodes++;
        return OK;  

    }else{
        connect = node_getConnect(g->nodes[index]);
        node_free(g->nodes[index]);
        g->nodes[index] = aux;
         node_setNConnect(g->nodes[index],connect);
        return ERROR;
    }

    return ERROR;

}

Status graph_insertEdge(Graph *g, const long nId1, const long nId2){
    int ind1, ind2;
    int cont=0;

    if (!g || nId1 < 0 || nId2 < 0) return ERROR;

    ind1 = find_node_index(g, nId1);
    ind2 = find_node_index(g, nId2);

    if (g->connections[ind1][ind2]== TRUE){
        return ERROR;
    }

    g->connections[ind1][ind2] = TRUE;
    g->num_edges++;

    cont = node_getConnect(g->nodes[ind1]);
    cont ++;
    node_setNConnect(g->nodes[ind1], cont);

    return OK;
}

Node *graph_getNode(const Graph *g, long nId){
    Node *aux = NULL;
    int index = -1;

    if (!g) return NULL;
    
    index = find_node_index(g, nId);
    aux = node_copy(g->nodes[index]);
    return aux;
}

Status graph_setNode(Graph *g, const Node *n){
    int index = -1;
    Node *aux = NULL;

    if (!g || !n) return ERROR;

    index = find_node_index(g, node_getId(n));
    aux = node_copy(n);

    if (!aux) return ERROR;

    node_free(g->nodes[index]);
    g->nodes[index] = aux;

    return OK;
}

long *graph_getNodesId(const Graph *g){
    long *aux = NULL;
    int i;
    
    if (!g) return NULL;

    aux = (long *) malloc(g->num_nodes * sizeof(long));
    if (!aux) return NULL;
    
    for (i=0; i<g->num_nodes; i++){
        aux[i] = node_getId(g->nodes[i]);
    }

    return aux;
}

int graph_getNumberOfNodes(const Graph *g){
    if (!g) return -1;

    return g->num_nodes;
}

int graph_getNumberOfEdges(const Graph *g){
    if (!g) return -1;

    return g->num_edges;
}

Bool graph_areConnected(const Graph *g, const long nId1, const long nId2){
    int ind1, ind2;
    if (!g) return FALSE;

    ind1 = find_node_index(g, nId1);
    ind2 = find_node_index(g, nId2);

    return g->connections[ind1][ind2];
}

int graph_getNumberOfConnectionsFrom(const Graph *g, const long fromId){
    int index = -1;
    if (!g || fromId < 0) return -1;
    
    index = find_node_index(g, fromId);
    return node_getConnect(g->nodes[index]);
}

long *graph_getConnectionsFrom(const Graph *g, const long fromId){
    long *dev = NULL, aux=0;
    int *cast = NULL, size, index= -1, i;

    if (!g) return NULL;
    
    aux = fromId;
    index = find_node_index(g, aux);

    cast = graph_getConnectionsIndex(g, index);
    if (!cast) return NULL;
    
    size = node_getConnect(g->nodes[index]);
    dev = (long *)malloc(sizeof(long) *size);
    if (!dev){
        free(cast);
        return NULL;
    }

    for (i=0; i< size; i++){
        dev[i] = node_getId(g->nodes[cast[i]]);
    }

    free(cast);
    return dev;
}

int graph_print(FILE *pf, const Graph *g){
    int cont=0, i, j, numberC=0;
    long *array = NULL;

    if (!pf || !g){
        fprintf(stderr, "%s", strerror(errno)); 
        return -1;
    }
    
    for (i=0; i < g->num_nodes; i++){
        int suma = 0, cont1 = 0;
        cont1 = node_print(pf, g->nodes[i]);

        array = graph_getConnectionsFrom(g, node_getId(g->nodes[i]));
        if (!array) return cont;
        numberC = node_getConnect(g->nodes[i]);

        for (j=0; j < numberC; j++){
            suma = fprintf(pf, " %ld" ,array[j]);
        }
        fprintf(pf, "\n");
        free(array);
    }
    return  cont;
}


Status graph_readFromFile(FILE *fin, Graph *g){
    int i, numNodes = 0;
    char name[NAME_L];
    long id, id1, id2;
    Label label;
    Node *n = NULL;

    if (!fin || !g) return ERROR;

    

    n = node_init();
    if (!n) return ERROR;

    if(fscanf(fin, "%d", &numNodes) == 0) return -1;

    for (i=0; i<numNodes; i++){
        if(fscanf(fin, "%ld %s %d", &id, name, (int *)&label) != 0){
            node_setId(n, id);
            node_setName(n, name);
            node_setLabel(n, label);

            graph_insertNode(g, n);
        }
    }
    
    while (!feof(fin)){
        if(fscanf(fin, "%ld %ld", &id1, &id2) != 0){
            graph_insertEdge(g, id1, id2);
        }
    }

    node_free(n);
    
    return OK;
}
