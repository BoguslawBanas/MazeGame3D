#include <stdio.h>
#include "../header_files/labirynth.h"
#include "../header_files/disjoint_set.h"
#include "../header_files/permutations.h"
#include "../header_files/directions.h"
#include "../header_files/treasure_room.h"

void createStartAndEndPoint(Labirynth *l){
    int x=0;
    int y=0;
    do{
        x=rand()%l->size;
    }while(x%4==0);

    do{
        y=rand()%l->size;
    }while(y%4==0);
    l->labirynth[y][x]='P';
    l->start_point_x=x;
    l->start_point_y=y;

    do{
        x=rand()%l->size;
    }while(x%4==0 || x==l->start_point_x);

    do{
        y=rand()%l->size;
    }while(y%4==0 || y==l->start_point_y);

    l->labirynth[y][x]='E';
    l->end_point_x=x;
    l->end_point_y=y;
}

static void dfs(Labirynth *l, char *is_visited, DisjointSet *ds, const int x, const int y, const Direction d){
    if(x<=0 || y<=0 || x>=l->size || y>=l->size || is_visited[x*l->size+y]){
        return;
    }
    is_visited[x*l->size+y]=1;

    // if(find(ds, prev_x*l->size+prev_y)!=find(ds, x*l->size+y)){
        // l->labirynth[(prev_x+x)/2][(prev_y+y)/2]=' ';

    switch(d){
        case LEFT:{
            if(find(ds, x*l->size+y)!=find(ds, x*l->size+y+4)){
                for(int i=0;i<3;++i){
                    l->labirynth[x/4*4+i+1][y/4*4+4]=' ';
                }
                unionize(ds, x*l->size+y+4, x*l->size+y);
            }

        }break;
        case RIGHT:{
            if(find(ds, x*l->size+y)!=find(ds, x*l->size+y-4)){
                for(int i=0;i<3;++i){
                    l->labirynth[x/4*4+i+1][y/4*4]=' ';
                }
                unionize(ds, x*l->size+y-4, x*l->size+y);
            }
        }break;
        case UP:{
            if(find(ds, x*l->size+y)!=find(ds, (x+4)*l->size+y)){
                for(int i=0;i<3;++i){
                    l->labirynth[x/4*4+4][y/4*4+i+1]=' ';
                }
                unionize(ds, (x+4)*l->size+y, x*l->size+y);
            }
        }break;
        case DOWN:{
            if(find(ds, x*l->size+y)!=find(ds, (x-4)*l->size+y)){
                for(int i=0;i<3;++i){
                    l->labirynth[x/4*4][y/4*4+i+1]=' ';
                }
                unionize(ds, (x-4)*l->size+y, x*l->size+y);
            }
        }break;
        return;
    }

    int permutation=createPermutation();
    for(int i=0;i<4;++i){
        switch(permutation%10){
            case LEFT: dfs(l, is_visited, ds, x, y-4, LEFT); break;
            case RIGHT: dfs(l, is_visited, ds, x, y+4, RIGHT); break;
            case UP: dfs(l, is_visited, ds, x-4, y, UP); break;
            case DOWN: dfs(l, is_visited, ds, x+4, y, DOWN); break;
        }
        permutation/=10;
    }
}

void createPathInLabirynth(Labirynth *l){
    DisjointSet *ds=(DisjointSet*)malloc(sizeof(DisjointSet));
    initDisjointSet(ds, (l->size)*(l->size));

    char *is_visited=(char*)(calloc(sizeof(char), (l->size)*(l->size)));

    is_visited[l->start_point_x*l->size+l->start_point_y]=1;

    int permutation=createPermutation();
    for(int i=0;i<4;++i){
        switch(permutation%10){
            case LEFT: dfs(l, is_visited, ds, l->start_point_x, l->start_point_y-4, LEFT); break;
            case RIGHT: dfs(l, is_visited, ds, l->start_point_x, l->start_point_y+4, RIGHT); break;
            case UP: dfs(l, is_visited, ds, l->start_point_x-4, l->start_point_y, UP); break;
            case DOWN: dfs(l, is_visited, ds, l->start_point_x+4, l->start_point_y, DOWN); break;
        }
        permutation/=10;
    }

    deleteDisjointSet(ds);
}

Labirynth *createLabirynth(const int size){
    Labirynth *maze=(Labirynth*)malloc(sizeof(Labirynth));
    maze->size=size;
    maze->labirynth=(char**)(malloc(sizeof(char*)*size));
    for(int i=0;i<size;++i){
        maze->labirynth[i]=(char*)(malloc(sizeof(char)*size));
        for(int j=0;j<size;++j){
            if(i%4==0 || j%4==0){
                maze->labirynth[i][j]='#';
            }
            else{
                maze->labirynth[i][j]=' ';
            }
        }
    }

    createStartAndEndPoint(maze);

    createPathInLabirynth(maze);

    return maze;
}

void printLabirynth(Labirynth *l){
    for(int i=0;i<l->size;++i){
        for(int j=0;j<l->size;++j){
            printf("%c", l->labirynth[i][j]);
        }
        printf("\n");
    }
}

void deleteLabirynth(Labirynth *l){
    for(int i=0;i<l->size;++i){
        free(l->labirynth[i]);
    }
    free(l->labirynth);
}