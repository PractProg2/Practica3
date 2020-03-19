/** File:   element.h* Author: Profesores de PROG2*/
#ifndef ELEMENT_H
#define ELEMENT_H
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Element Element;

Element * element_init();

void element_free(Element *e);

Element * element_setInfo(Element *ele,void* info);

void* element_getInfo(Element *ele);

Element * element_copy(const Element *ele);

Bool element_equals(const Element *ele1,const Element *ele2);

int element_print(FILE *pf, const Element *ele);

#endif
/* ELESTACK_H */