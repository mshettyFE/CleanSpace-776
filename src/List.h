#ifndef LIST
#define LIST

/*

Generic Doubly Linked List with cursed polymorphism. Used as an object Queue.

I didn't implement adding/removing from the tail though.

It's doubly linked since if you are given a Node that is known to be in the list, you can remove it in O(1) time by flip flopping pointers around.

A singly linked list can't do this, since even if you know that your Node is in the list, you need the previous node as well to maintain topology of list.
You would need to search for node's position first.

*/

// identifiers of what is stored in each Node
#define OBJ_DEATH_ID  0 
#define OBJ_PLAYER_ID 1
#define OBJ_BULLET_ID 2
#define OBJ_METEOR_ID 3

// Weather to update death queue or not.
//Could be used to randomly generate objects on screen, check for collisions without generating animations. Didn't do this though.
#define DONT_UPDATE_DEATH 0
#define UPDATE_DEATH 1

#include "object.h"

typedef struct ListNode{
    void* item;
    char obj_type; // what object to cast void* to  
    struct ListNode* prev;
    struct ListNode* next;
} LNode;

struct List{
    struct ListNode* head;
    struct ListNode* tail;
    char size;
} ;

struct List* initList();


LNode* getNext(LNode* node);

LNode* AddToHead(struct List* list, void* obj, char obj_type);
LNode* AddNodeToHead(struct List* list, LNode* opt);

void ClearList(struct List* list);

// assumes that node exists in list. Returns next pointer in list
LNode* Remove(struct List* list, LNode* it );

void freeListItem(LNode* cur);

// Traverse List iterates through list, and adds animations to Death if needed
void TraverseList(struct List* list, struct List* Death);

// cycle through animations currently on screen
void TraverseDeathList(struct List* list);

// what to do when at each node while in TraverseList
LNode* ListItemAction(struct List* list, LNode* item, struct List* Death);

//get object from LNode
struct Object* extractObj(LNode* item);

// compare two nodes to see if their objects collide. No self collisions
unsigned char cmp(LNode* node1, LNode* node2);

// returns current node if no collisions detected. Returns next node if collisions were detected
// populates Death with dying animations
LNode* DealWithCollisions(struct List* list, LNode* cur, struct List* Death, unsigned char update_death );

#endif