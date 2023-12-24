#include "SpatialHash.h"
#include "object.h"
#include "List.h"
#include "player.h"
#include "Bullet.h"
#include <stdlib.h>

extern unsigned int XXXXXXXXXXXXXXXXXX;
extern ZZZZZZZZZZZZZZZZZZZZZZZ();

HashTable* initHash(){
    char i;
    HashTable* output = malloc(sizeof(HashTable));
    for(i=0; i<TOTAL_CELLS; ++i){
        output->table[i] = initList();
    }
    output->size = 0;
    return output;
}

void ClearTable(HashTable* table){
    char i;
    for(i=0; i<TOTAL_CELLS; ++i){
        ClearList(table->table[i], &freeListItem);
    }
    table->size = 0;
}

void FillTable(HashTable* table, struct List* objList){
    char i;
    char* data;
    LNode* cur = objList->head;
    while(cur){
        data = genHashes(cur);
        if(data){
                for(i=0; i<4; ++i){
                    AddToHead(table->table[data[i]], cur->item, cur->obj_type);
                    table->size += 1;
                }
        }
        free(data);
        cur = cur->next;
    }
}


unsigned char genHash(const signed char a_x, const signed char a_y){
    unsigned char width = abs(a_x)/CELLS_X_SIZE;
   return width + width*(abs(a_y)/CELLS_Y_SIZE);
}

unsigned char* genHashes(LNode* cur){
    struct Object* obj;
    char half_width;
    unsigned char* hashes;
    if(cur==NULL){
        return NULL;
    }
    switch (cur->obj_type)
    {
        case OBJ_PLAYER_ID:
            obj = ((struct Player*) cur->item)->obj;
            break;
        case OBJ_BULLET_ID:
            obj = ((struct Bullet*) cur->item)->obj;
            break;
    }
    if(obj==NULL){
        return NULL;
    }
    hashes =  malloc(sizeof(unsigned char)*4);
    half_width = obj->size.b.msb>>1;
    if(half_width < 1){
        half_width = 1;
    }

    hashes[0] =  genHash(obj->x.b.msb-half_width, obj->y.b.msb-half_width);
    hashes[1] =  genHash(obj->x.b.msb+half_width, obj->y.b.msb-half_width);
    hashes[2] =  genHash(obj->x.b.msb-half_width, obj->y.b.msb+half_width);
    hashes[3] =  genHash(obj->x.b.msb+half_width, obj->y.b.msb+half_width);
    
    return hashes;
}