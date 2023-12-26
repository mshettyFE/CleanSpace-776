#include "List.h"
#include "player.h"
#include "Bullet.h"
#include "Meteor.h"
#include <stdlib.h>
#include "gametank.h"
#include <stdio.h>
#include "object.h"
#include "Death.h"

extern unsigned char meteor_present;

#define USE_COL

struct List* initList(){
    struct List* out = malloc(sizeof(struct List));
    if(!out){return NULL;}
    out->head = NULL;
    out->tail = NULL;
    out->size = 0;
    return out;
}

LNode* AddToHead(struct List* list, void* obj, unsigned char obj_type){
    LNode* temp;
    LNode* opt = malloc(sizeof(LNode));
    if(!opt){return NULL;}
    opt->obj_type = obj_type;
    opt->item = obj;
    list->size += 1;
    opt->prev = NULL;
    if(list->head == NULL){
        list->head = opt;
        list->tail = opt;
        opt->next = NULL;
        return opt;
    }
    temp = list->head;
    list->head = opt;
    opt->next = temp;
    temp->prev = opt;
    return opt;
}

LNode* AddNodeToHead(struct List* list, LNode* opt){
    LNode* temp;
    if(!opt){return NULL;}
    list->size += 1;
    opt->prev = NULL;
    if(list->head == NULL){
        list->head = opt;
        list->tail = opt;
        opt->next = NULL;
        return opt;
    }
    temp = list->head;
    list->head = opt;
    opt->next = temp;
    temp->prev = opt;
    return opt;
}

LNode* getNext(LNode* node){
    if(node){
        return node->next;
    }
    return NULL;
}

LNode* RemoveDeath(struct List* list, LNode* it, void(*freeItem)(LNode* cur) ){
    return Remove(list, it, &freeItem);
}


// assumes that node exists in list. Returns next pointer
LNode* Remove(struct List* list, LNode* it, void(*freeItem)(LNode* cur) ){
    LNode* previous;
    LNode* next_one;
    if(it){
        list->size -= 1;
        if(list->head == it){
            next_one = list->head->next;
            freeItem(it);
            list->head = next_one;
            return next_one;
        }
        else if(list->tail == it){
            previous = list->tail->prev;
            previous->next = NULL;
            freeItem(it);
            it = NULL;
            return NULL;
        }
        else{
            previous = it->prev;
            next_one = it->next;
            freeItem(it);
            it = NULL;
            previous->next = next_one;
            next_one->prev = previous;
            return next_one;
        }
    }

    return NULL;
}


void ClearList(struct List* list, void(*freeData)(LNode* cur)){
    LNode* tmp;
    LNode* cur;
    if(list==NULL){
        return;
    }
    cur = list->head;
    while(cur){
        cur = Remove(list,cur, freeData);
    }
}

void freeListItem(LNode* cur){
    switch (cur->obj_type)
    {
    case OBJ_DEATH_ID:
        freeDeath(cur->item);
        break;
    case OBJ_PLAYER_ID:
        freePlayer(cur->item);
        break;
    case OBJ_BULLET_ID:
        freeBullet(cur->item);
        break;
    case OBJ_METEOR_ID:
        freeMeteor(cur->item);
    }
    free(cur);
}


void TraverseList(struct List* list, struct List* Death){
    LNode* cur = list->head;
    while(cur){
        cur =ListItemAction(list, cur, Death);
    }
}

void TraverseDeathList(struct List* list){
    LNode* cur = list->head;
    while (cur)
    {
        cur = UpdateDeath(list, cur);
    }
        
}


LNode* ListItemAction(struct List* list, LNode* item, struct List* Death){
    LNode* original;
    LNode* postCollisions;
    if(item){
#ifdef USE_COL
        original = item;
        postCollisions =  DealWithCollisions(list, item, Death, UPDATE_DEATH);
        if(postCollisions != original){
            return postCollisions;
        }
#endif
        switch(item->obj_type){
            case OBJ_PLAYER_ID:
                return UpdatePlayer(list, item);
                break;
            case OBJ_BULLET_ID:
                return UpdateBullet(list, item);
                break;
            case OBJ_METEOR_ID:
                meteor_present = 1;
                return UpdateMeteor(list, item);
                break;
        }
    }
    return NULL;
}

struct Object* extractObj(LNode* item){
    struct Object* out = NULL;
    if(!item){return NULL;}
    switch (item->obj_type)
    {
        case OBJ_DEATH_ID:
            out = ((struct DeathAnim*) item->item)->obj;
            break;
        case OBJ_PLAYER_ID:
            out = ((struct Player*) item->item)->obj;
            break;
        case OBJ_BULLET_ID:
            out = ((struct Bullet*) item->item)->obj;
            break;
        case OBJ_METEOR_ID:
            out = ((struct Meteor*) item->item)->obj;
            break;    
    }
    return out;
}

unsigned char cmp(LNode* node1, LNode* node2){
    struct Object* ob1;
    struct Object* ob2;
    unsigned int dx,dy, size;
    if(node1 == node2){
        return 0;
    }
    ob1 = extractObj(node1);
    ob2 = extractObj(node2);
    if(!ob1 || !ob2){
        return 0;
    }
    dx = ob1->x.b.msb - ob2->x.b.msb;
    dy = ob1->y.b.msb - ob2->y.b.msb;
    size  = ob1->size.b.msb+ ob2->size.b.msb;
    if(dx & 128) dx = -dx;
    if(dy & 128) dy = -dy;
    return (dx < size) && (dy < size);
}

// returns current node if no collisions detected. Returns next node if collisions were detected
// populates Death with dying animations
LNode* DealWithCollisions(struct List* list, LNode* cur, struct List* Death, unsigned char update_death ){
    LNode * og;
    LNode* itr;
    LNode* output;
    unsigned char collision_maybe;
    unsigned int x;
    output = cur;
    og = cur;
    itr = cur->next;
    while(itr){
// collision found. 
        PROFILER_START(x)
        collision_maybe = cmp(og,itr);
        PROFILER_END(x)
        if(collision_maybe){
// check if both are bullets. If so, then continue iterating through list
            if((og->obj_type==OBJ_BULLET_ID) && (itr->obj_type==OBJ_BULLET_ID)){
                itr = itr->next;
                continue;
            }
// check if both are meteors. If so, then continue iterating through list
            if((og->obj_type==OBJ_METEOR_ID) && (itr->obj_type==OBJ_METEOR_ID)){
                itr = itr->next;
                continue;
            }
//check if one if PLAYER and the other is BULLET. If Bullet came from that Player, continue on. Do for both ways
            if((og->obj_type==OBJ_BULLET_ID) && (itr->obj_type==OBJ_PLAYER_ID)){
                if(  ((struct Bullet*)og->item)->origin == ((struct Player*)itr->item)->player_num ){
                    itr = itr->next;
                    continue;
                }
            }
            if((og->obj_type==OBJ_PLAYER_ID) && (itr->obj_type==OBJ_BULLET_ID)){
                if(  ((struct Player*)og->item)->player_num == ((struct Bullet*)itr->item)->origin ){
                    itr = itr->next;
                    continue;
                }
            }

// if update_death, then add objects to Death queue. Don't add bullets to Death
            if(update_death){
                if(og->obj_type!=OBJ_BULLET_ID){
                    AddNodeToHead(Death, initDeathAnim(og));
                }                
                if(itr->obj_type!=OBJ_BULLET_ID){
                    AddNodeToHead(Death, initDeathAnim(itr));
                }
            }
// Regardless of update_death, remove both og and the current iterator from the queue. Return value of itr (this is next valid node)
                Remove(list,og,freeListItem);
                output = Remove(list,itr,freeListItem);
                output;
            return output;
        }
        else{
// No collision found (yet). simply increment itr to next;
            itr = itr->next;
        }

    }
// No collisions detected. Return og to indicate nothing changed
    return output;
}
