#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_fp.h"
#include "graph.h"


#define MAXSTRING 65536


Status graph_breadthFirst (Graph *pg,long ini_id,long end_id,char *nodestraversed){
    Queue *colaAux = NULL;
    Node *aux = NULL, *comp_nodo = NULL;
    int i, num;
    long *array = NULL, predId = -1, *graphArray = NULL;

    if (!pg || ini_id < 0 || end_id < 0 || !nodestraversed) return ERROR;


    colaAux = queue_init(node_free, node_copy, node_print);
    if (!colaAux ) return ERROR;
    
    graphArray = graph_getNodesId(pg);
    for(i=0; i<graph_getNumberOfNodes(pg); i++){
        aux = graph_getNode(pg, graphArray[i]);
        if (node_getId(aux) == ini_id){
            node_setLabel(aux, BLACK);
            queue_insert(colaAux, aux);
        }else{
            node_setLabel(aux, WHITE);
        }
        graph_setNode(pg, aux);
        node_free(aux);
    }

    free(graphArray);
  
    while (queue_isEmpty(colaAux) == FALSE){

        comp_nodo = queue_extract(colaAux);
        aux = graph_getNode(pg, node_getId(comp_nodo));

        
        strcat(nodestraversed, node_getName(aux));
        strcat(nodestraversed, "    ");

        if (end_id == node_getId(aux)){
            node_free(aux);
            node_free(comp_nodo);
            queue_free(colaAux);
            return END;
        }

        array = graph_getConnectionsFrom(pg, node_getId(aux));
        predId = node_getId(aux);
        num = graph_getNumberOfConnectionsFrom(pg, node_getId(aux));
        for (i=0; i<num; i++){
            node_free(aux);
            
            aux = graph_getNode(pg, array[i]);

            if (node_getLabel(aux) != BLACK){
                node_setLabel(aux, BLACK);
                node_setPredecessorId(aux, predId);

                graph_setNode(pg, aux);
                queue_insert(colaAux, aux);
            }
        }
        
        free(array);

        node_free(aux);
        node_free(comp_nodo);
    }

    queue_free(colaAux);
    return OK;
}

int main(int argc, char *argv[]){
    char *salida = NULL;
    char *f = NULL;
    long id_ini, id_end;
    Graph *grafo = NULL;
    FILE *fin = NULL;
    Status st = OK;

    if (argc < 4){
        printf("./p3_e2 <nombre_fichero> <Id entrada> <Id salida>.\n");
        return -1;
    }


    grafo = graph_init();
    if(!grafo) return -1;

    fin = fopen(argv[1], "r");
    if (!fin ){
        graph_free(grafo);
        return -1;
    }

    st = graph_readFromFile(fin, grafo);
    
    id_ini = atol(argv[2]);

    id_end = atol(argv[3]);

    salida = (char *)calloc (MAXSTRING, sizeof(char));
    if (!salida) return -1;

    graph_breadthFirst(grafo, id_ini, id_end, salida);

    printf("%s\n", salida);

    fclose(fin);
    free(salida);
    graph_free(grafo);
    return 0;
}




