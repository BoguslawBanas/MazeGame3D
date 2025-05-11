#ifndef LABIRYNTH_H
#define LABIRYNTH_H
#include <stdlib.h>

typedef struct{
    int start_point_x;
    int start_point_y;
    int end_point_x;
    int end_point_y;
    int size;
    char **labirynth;
}Labirynth;

void createStartPoint(Labirynth*);
void createEndPoint(Labirynth*);
void createPathInLabirynth(Labirynth*);
Labirynth* createLabirynth(const int);
void printLabirynth(Labirynth*);
void deleteLabirynth(Labirynth*);

#endif