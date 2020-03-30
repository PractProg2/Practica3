#include "queue_fp.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_QUEUE 1024

struct _Queue{
    int front;
    int rear;
    void *items[MAX_QUEUE];

    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
};

extern int errno;

Queue* queue_init(destroy_element_function_type f1,copy_element_function_type f2, print_element_function_type f3){
    Queue *aux = NULL;
    int i;

    if (!f1 || !f2 || !f3) return NULL;

    aux = (Queue *) malloc (sizeof(Queue));
    if (!aux){
        fprintf(stderr, "%s", strerror(errno));
        return NULL;
    }

    aux->destroy_element_function = f1;
    aux->copy_element_function = f2;
    aux->print_element_function = f3;

    for (i=0; i<MAX_QUEUE; i++){
        aux->items[i] = NULL;
    }

    aux->front = aux->rear = 0;

    return aux;
}

void queue_free(Queue *q){
    int i;

    for (i= 0;i<MAX_QUEUE; i++){
        q->destroy_element_function(q->items[i]);
    }

    free(q);
}

Bool queue_isEmpty(const Queue *q){
    if (!q) return FALSE;

    if (q->front == q->rear) return TRUE;

    return FALSE;
}

Status queue_insert(Queue *q,const void* pElem){

    if (!q || !pElem || (q->front == (q->rear +1) % MAX_QUEUE)) return ERROR;

    q->items[q->rear] = q->copy_element_function(pElem);
    if (!q->items[q->rear]) return ERROR;
    
    q->rear = (q->rear+1)%MAX_QUEUE;

    return OK;
}

void *queue_extract(Queue *q){
    void *aux = NULL;
    if (!q || queue_isEmpty(q) == TRUE) return NULL;

    aux = q->items[q->front];
    q->items[q->front] = NULL;
    q->front = (q->front + 1)%MAX_QUEUE;

    return aux;
}

int queue_size (const Queue *q){
    if (!q) return -1;

    if (q->rear >= q->front) return q->rear - q->front;

    return (MAX_QUEUE - (q->front - q->rear));
}

int queue_print(FILE*pf,const Queue *q){
    int i, cont = 0;

    if (!pf || !q){
        fprintf(stderr, "%s", strerror(errno));
        return -1;
    }

    for (i=0; i<queue_size(q); i++){
        cont += q->print_element_function(pf,q->items[i]);
    }
    return cont;
}