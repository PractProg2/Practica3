#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_fp.h"
#include "graph.h"


#define MAXSTRING 65536


Status graph_breadthFirst (Graph *pg,long ini_id,long end_id,char *nodestraversed){
    Queue *cola = NULL, *colaAux = NULL;
    Node *aux = NULL, *comp_nodo = NULL;
    int i, num, t, CFLAG;
    long *array = NULL;

    if (!pg || ini_id < 0 || end_id < 0 || !nodestraversed) return ERROR;

    cola = queue_init(node_free, node_copy, node_print);
    if (!cola ) return ERROR;

    colaAux = queue_init(node_free, node_copy, node_print);
    if (!colaAux ){
        queue_free(cola);
        return ERROR;
    }

    for(i=0; i<graph_getNumberOfNodes(pg); i++){
        aux = graph_getNodeFromPosition(pg, i);
        if (node_getId(aux) == ini_id){
            node_setLabel(aux, BLACK);
            queue_insert(colaAux, aux);
            strcat(nodestraversed, node_getName(aux));
        }else{
            node_setLabel(aux, WHITE);
        }
        graph_setNode(pg, aux);
        node_free(aux);
    }

    for (i=0; i<graph_getNumberOfNodes(pg); i++){
        aux = graph_getNodeFromPosition(pg, i);
        queue_insert(cola, aux);
        node_free(aux);
    }

    
    while (queue_isEmpty(colaAux) == FALSE){
        comp_nodo = queue_extract(colaAux);
        aux = queue_extract(cola);

        while (node_cmp(comp_nodo, aux) != 0 ){
            queue_insert(cola, aux);
            node_free(aux);
            aux = queue_extract(cola);
        }
        if (end_id == node_getId(aux)){
            node_free(aux);
            queue_free(cola);
            node_free(comp_nodo);
            queue_free(colaAux);
            return END;
        }

        array = graph_getConnectionsFrom(pg, node_getId(aux));
        num = graph_getNumberOfConnectionsFrom(pg, node_getId(aux));
        for (i=0; i<num; i++){
            node_free(aux);
            aux = queue_extract(cola);
            t = CFLAG = 0;
            while (node_getId(aux) != array[i] && CFLAG != 1){
                t++;
                if(!(t<queue_size(cola))){
                    CFLAG = 1;
                }
                queue_insert(cola, aux);
                node_free(aux);
                aux = queue_extract(cola);
                            
            }

            if ( node_getLabel(aux) != BLACK && CFLAG != 1){
                strcat(nodestraversed, "    ");
                strcat(nodestraversed, node_getName(aux));
                node_setLabel(aux, BLACK);

                if (array[i] == end_id){
                    free(array);                           
                    queue_free(cola);
                    node_free(aux);
                    queue_free(colaAux);
                    node_free(comp_nodo);
                    return END;
                }
                queue_insert(cola, aux);
                queue_insert(colaAux, aux);

            }else{
                queue_insert(cola, aux);
            }
        }
        free(array);

        node_free(aux);
        node_free(comp_nodo);
    }
    


    queue_free(colaAux);
    queue_free(cola);
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




