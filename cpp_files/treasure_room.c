#include "../header_files/treasure_room.h"

inline int is_Treasure_Room_Valid(Labirynth *l, TreasureRoom *tr){
    if(tr->x<1 || tr->y<1 || tr->y+tr->size_y>l->size-1 || tr->x+tr->size_x>l->size-1) return 0;
    if(tr->direction_of_corridor==LEFT && tr->x-tr->length_of_corridor-2<0) return 0;
    else if(tr->direction_of_corridor==RIGHT && tr->x+tr->size_x+tr->length_of_corridor+2>l->size) return 0;
    else if(tr->direction_of_corridor==UP && tr->y-tr->length_of_corridor-2<0) return 0;
    else if(tr->direction_of_corridor==DOWN && tr->y+tr->size_y+tr->length_of_corridor+2>l->size) return 0;
    return 1;
}

void generate_Treasure_Room(TreasureRoom *tr){
    tr->length_of_corridor=rand()%8+2;
    
}

void write_Treasure_Room_Into_Labirynth(Labirynth *l, TreasureRoom *tr){

}