#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_fp.h"
#include "graph.h"
#include "stack_fp.h"

#define MAXSTRING 65536

int printNode(FILE *pf, Graph *g, long actualid, long *predid){
    Node *aux = NULL;
    int cont = 0;
    
    if (!pf || !g || actualid < 0 || !predid) return -1;

    aux = graph_getNode(g, actualid);
    if (!aux) return -1;

    *predid = node_getPredecessorId(aux);
    cont = node_print(pf, aux);

    node_free(aux);
    return cont;
}

int printNode2(FILE *pf, Graph *g, long actualid){
    Node *aux = NULL;
    int cont = 0;
    
    if (!pf || !g || actualid < 0) return -1;

    aux = graph_getNode(g, actualid);
    if (!aux) return -1;

    cont = node_print(pf, aux);

    node_free(aux);
    return cont;
}

int pathToFrom(FILE *dev, Graph *g, long orignid, long toid){
    long *pred = NULL;
    int cont = 0;
    Node *nodo = NULL;

    if (!dev || !g || orignid < 0 || toid < 0) return -1;

    pred = (long *)malloc(sizeof(long));
    if (!pred) return -1;

    *pred = toid;
    while (*pred > 0){
        nodo = graph_getNode(g, *pred);
        if (*pred == orignid){
            cont += printNode(dev, g, node_getId(nodo), pred);
            node_free(nodo);
            free(pred);
            return cont;
        } 
        cont += printNode(dev, g, node_getId(nodo), pred);
        node_free(nodo);

        
    }
    free(pred);
    return -1;
}

int pathFromTo(FILE *dev, Graph *g, long orignid, long toid){
    int cont = 0;
    long predid = 0;
    Node *nodo = NULL;

    if (!dev || !g || orignid < 0 || toid < 0) return -1;

    if (orignid == toid){
        cont = printNode2(dev, g, toid);
        return cont;
    }

    nodo = graph_getNode(g, toid);
    if (!nodo) return -1;

    predid = node_getPredecessorId(nodo);

    cont = pathFromTo(dev, g, orignid, predid);
    if (cont == 1) return -1;

    cont += node_print(dev, nodo);
    node_free(nodo);

    return cont;
}

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
    long id_ini, id_end;
    Graph *grafo = NULL;
    FILE *fin = NULL;
    Status st = OK;

    if (argc < 4){
        printf("./p3_e3 <nombre_fichero> <Id entrada> <Id salida>.\n");
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

    printf("\n%s\n", salida);


    fprintf(stdout, "\nFrom Origin to End:\n");

    pathFromTo(stdout, grafo, id_ini, id_end);

    fprintf(stdout, "\n");

    fprintf(stdout, "\nFrom End to Origin:\n");

    pathToFrom(stdout, grafo, id_ini, id_end);

    fprintf(stdout, "\n");

    fclose(fin);
    free(salida);
    graph_free(grafo);
    return 0;
}