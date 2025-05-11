#include "../header_files/disjoint_set.h"

void initDisjointSet(DisjointSet *ds, const int size){
    ds->arr=(int*)malloc(sizeof(int)*size);
    for(int i=0;i<size;++i){
        ds->arr[i]=-1;
    }
    ds->size=size;
}

int find(DisjointSet *ds, const int index){
    int tmp1=index;
    int tmp2=ds->arr[index];
    while(tmp2!=-1){
        tmp1=tmp2;
        tmp2=ds->arr[tmp1];
    }
    return tmp1;
}

void unionize(DisjointSet *ds, const int index1, const int index2){
    int fi1=find(ds, index1);
    int fi2=find(ds, index2);
    if(fi1<fi2){
        ds->arr[index2]=fi1;
    }
    else{
        ds->arr[index1]=fi2;
    }
}

void deleteDisjointSet(DisjointSet *ds){
    free(ds->arr);
    free(ds);
    ds=NULL;
}