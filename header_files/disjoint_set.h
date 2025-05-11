#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <stdlib.h>

typedef struct{
    int size;
    int *arr;
} DisjointSet;

void initDisjointSet(DisjointSet*, const int);
int find(DisjointSet*, const int);
void unionize(DisjointSet*, const int, const int);
void deleteDisjointSet(DisjointSet*);

#endif