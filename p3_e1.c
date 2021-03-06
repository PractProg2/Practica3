#include "queue_fp.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    Queue *colaNodos = NULL;
    Graph *grafo = NULL;
    Node *nodo = NULL;
    FILE *fin = NULL;
    int tam = 0;
    int i;
    long *array = NULL;
    Status st = OK;

    if (argc < 1 || argv[1] == NULL){
        fprintf(stderr, "<Falta introducir el nombre del fichero que se quiere leer>\n");
        return -1;
    }
    /* Inicializamos los TAD's*/
    colaNodos = queue_init(node_free, node_copy, node_print);
    if (!colaNodos) return -1;

    grafo = graph_init();
    if(!grafo){
        queue_free(colaNodos);
        return -1;
    }
    /* Abrimos el fichero */
    fin = fopen(argv[1], "r");
    if (!fin ){
        queue_free(colaNodos);
        graph_free(grafo);
        return -1;
    }
    /* Leemos del fichero */
    graph_readFromFile(fin, grafo);

    /* Insertamos los nodos del grafo en una cola */
    array = graph_getNodesId(grafo);
    if (!array){
        queue_free(colaNodos);
        graph_free(grafo);
        fclose(fin);
        return -1;
    }
    for (i=0; i<graph_getNumberOfNodes(grafo) && st == OK; i++){
        nodo = graph_getNode(grafo, array[i]);
        st = queue_insert(colaNodos, nodo);
        node_free(nodo);
    }

    /* Actualizamos label en los nodos del grafo a BLACK */
    for (i=0; i<graph_getNumberOfNodes(grafo) && st == OK; i++){
        nodo = graph_getNode(grafo, array[i]);
        node_setLabel(nodo, BLACK);
        st = graph_setNode(grafo, nodo);
        node_free(nodo);
    }

    /* Imprimimos el grafo y el tamanio de la cola y la cola */
    printf("Nodes in graph: \n\n");
    graph_print(stdout, grafo);

    printf("Queue size: %d\n", queue_size(colaNodos));

    printf("\nNodes in queue: \n\n");
    queue_print(stdout, colaNodos);

    /* Extraemos de la cola todos los nodos y los imprimimos */
    tam = queue_size(colaNodos);
    printf("\n");
    for (i=0; i<tam; i++){
        nodo = (Node *)queue_extract(colaNodos);
        printf("\nExtract Node: \n");
        node_print(stdout, nodo);
        node_free(nodo);
    }

    printf("\nQueue size: %d\n", queue_size(colaNodos));

    free(array);
    graph_free(grafo);
    queue_free(colaNodos);
    fclose(fin);
    return 0;
}