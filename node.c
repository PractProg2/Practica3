/**
* @file node.c
* @author Gonzalo Arcas & Ciro Alonso
* @date 12 February 2020
* @brief ADT Node
*
* @details definicion de las funciones node.h
*
* @see
*/
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

#define NAME_L 64 /*!< Maximum node name length */

struct _Node{
    char name[NAME_L]; /*!<Node name */
    long id;           /*!<Node id */
    int nConnect;      /*!<Node number of connections */
    Label label;       /*!<Node state */
};

Node *node_init()
{
    Node *n;
    n = (Node *)malloc(sizeof(Node));
    if (!n){
        fprintf(stderr, "%s", strerror(errno));
        return NULL;
    }
    strcpy(n->name, " ");
    n->id = -1;
    n->nConnect = 0;
    n->label = WHITE;

    return n;
}

void node_free(void *n)
{

    free(n);
}

long node_getId(const Node *n)
{
    if (!n)
        return -1;

    return n->id;
}

const char *node_getName(Node *n)
{
    if (!n)
        return NULL;

    return n->name;
}

int node_getConnect(const Node *n)
{
    if (!n)
        return -1;

    return n->nConnect;
}

Label node_getLabel(const Node *n)
{
    if (!n)
        return -1;

    return n->label;
}

Status node_setLabel(Node *n, Label l)
{
    if (!n)
        return ERROR;

    n->label = l;

    if(n->label != l){
        return ERROR;
    }

    return OK;
}

Status node_setId(Node *n, const long id)
{
    if (!n || id < 0)
        return ERROR;

    n->id = id;
    return OK;
}

Status node_setName(Node *n, const char *name)
{
    if (!n || !name)
        return ERROR;

    strcpy(n->name, name);

    if(!n->name){
        return ERROR;
    }
    return OK;
}

Status node_setNConnect(Node *n, const int cn)
{
    if (!n || cn < 0) return ERROR;

    n->nConnect = cn;
    return OK;
}

/* En caso de error devolvemos 27*/
int node_cmp(const void *n1, const void *n2)
{
    if (!n1 || !n2)
        return 27;
    Node *aux1 = (Node *)n1;
    Node *aux2 = (Node *)n2;

    if (aux1->id < aux2->id)
        return -1;
    else if (aux1->id > aux2->id)
        return 1;
    else
    {
        return strcmp(aux1->name, aux2->name);
    }
}

void *node_copy(const void *src)
{
    if (!src)
        return NULL;

    Node *n = (Node *)src;
    Node *aux;
    aux = (Node *)malloc(sizeof(Node));
    if (!aux)
        return NULL;

    strcpy(aux->name, n->name);
    aux->id = n->id;
    aux->label = n->label;
    aux->nConnect = n->nConnect;

    return aux;
}

int node_print(FILE *pf, const void *n)
{

    if (!pf || !n){
        fprintf(stderr, "%s", strerror(errno));
        return -1;
    }
    Node *aux = (Node *)n;
    return fprintf(pf, "[%s, %ld, %d, %d]", aux->name, aux->id, aux->label, aux->nConnect);
}
