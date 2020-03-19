#include "element.h"
#include <errno.h>

extern int errno;

struct _Element{
    char *a;
};

Element *element_init(){
    Element *aux = NULL;

    aux = (Element *)malloc(sizeof(Element));
    if (!aux) return NULL;

    aux->a = (char *)malloc(sizeof(char));
    if (!aux->a){
        free(aux);
        return NULL;
    }
    return aux;
}

void element_free(Element *e){
    if (!e) return;

    free(e->a);
    free(e);
}

Element * element_setInfo(Element *ele,void* info){
    char data;

    if (!ele || !info) return NULL;

    data = *(char *)info;
    
    *ele->a = data;
    return ele;
}

void* element_getInfo(Element *ele){
    if (!ele) return NULL;

    return ele->a;
}

Element * element_copy(const Element *ele){
    Element *aux = NULL;

    if (!ele) return NULL;

    aux = element_init();
    if (!aux) return NULL;

    element_setInfo(aux, ele->a);
    return aux;
}

Bool element_equals(const Element *ele1,const Element *ele2){
    if (!ele1 || !ele2) return FALSE;

    if (*ele1->a == *ele2->a) return TRUE;

    return FALSE;
}

int element_print(FILE *pf, const Element *ele){
    if (!pf || !ele){
        fprintf(stderr, "%s", strerror(errno));
        return -1;
    }

    return fprintf(pf, "%c\n", *ele->a);
}