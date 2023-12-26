#ifndef LIST
#define LIST

#define OBJ_DEATH_ID  0 
#define OBJ_PLAYER_ID 1
#define OBJ_BULLET_ID 2
#define OBJ_METEOR_ID 3

#define DONT_UPDATE_DEATH 0
#define UPDATE_DEATH 1

#include "object.h"

typedef struct ListNode{
// linked list containing bounding boxes of objects in scene
    void* item;
    unsigned char obj_type;
    struct ListNode* prev;
    struct ListNode* next;
} LNode;

struct List{
// beginning of list
    struct ListNode* head;
    struct ListNode* tail;
// number of objects in the list
    unsigned char size;
} ;

struct List* initList();


LNode* getNext(LNode* node);

LNode* AddToHead(struct List* list, void* obj, unsigned char obj_type);
//LNode* AddToTail(struct List* list, void* obj, unsigned char obj_type);

//LNode* AddNodeToTail(struct List* list, LNode* opt);
LNode* AddNodeToHead(struct List* list, LNode* opt);


void ClearList(struct List* list);

LNode* Remove(struct List* list, LNode* it );

void freeListItem(LNode* cur);

void TraverseList(struct List* list, struct List* Death);

void TraverseDeathList(struct List* list);

LNode* ListItemAction(struct List* list, LNode* item, struct List* Death);

struct Object* extractObj(LNode* item);

unsigned char cmp(LNode* node1, LNode* node2);

// returns current node if no collisions detected. Returns next node if collisions were detected
// populates Death with dying animations
LNode* DealWithCollisions(struct List* list, LNode* cur, struct List* Death, unsigned char update_death );

#endif