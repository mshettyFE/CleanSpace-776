#ifndef SPATIAL
#define SPATIAL

#include "List.h"
#include "object.h"

#define CELLS_X_SIZE 20
#define CELLS_Y_SIZE 20
#define TOTAL_CELLS (unsigned char)((128/CELLS_X_SIZE)*(128/CELLS_Y_SIZE))

typedef struct HashTable{
    struct List* table[TOTAL_CELLS];
    unsigned char* size;
} HashTable;

HashTable* initHash();

void ClearTable(HashTable* table);

void FillTable(HashTable* table, struct List* objList);

unsigned char genHash(const signed char a_x, const signed char a_y);
unsigned char* genHashes(LNode* cur);
#endif