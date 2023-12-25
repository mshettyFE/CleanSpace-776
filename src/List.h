#ifndef LIST
#define LIST

extern unsigned int counter;

#define OBJ_ID 0
#define OBJ_PLAYER_ID 1
#define OBJ_METEOR_ID 2
#define OBJ_BULLET_ID 3
#define OBJ_DEATH_ID 4

#define DONT_CLEAR_DATA 0
#define CLEAR_DATA 1

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
LNode* AddToTail(struct List* list, void* obj, unsigned char obj_type);

void ClearList(struct List* list, struct List* Death, void(*freeData)(LNode* cur));

LNode* Remove(struct List* list, LNode* it, struct List* death, void(*freeItem)(LNode* cur) );

void freeListItem(LNode* cur);

void TraverseList(struct List* list, struct List* Death);
LNode* ListItemAction(struct List* list, LNode* item, struct List* Death);

//void PrintList(struct List* list, void(*print)(void* data));
//void printItem(LNode* cur);

#endif