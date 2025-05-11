#ifndef TREASURE_ROOM_H
#define TREASURE_ROOM_H

#include <stdlib.h>
#include "labirynth.h"
#include "directions.h"

typedef struct {
    int size_x;
    int size_y;
    int x; //top left place of room
    int y; //top left place of room
    int length_of_corridor;
    Direction direction_of_corridor;
} TreasureRoom;

#endif