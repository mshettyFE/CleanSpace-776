#include "List.h"
#include "player.h"
#include "Bullet.h"
#include "Meteor.h"
#include <stdlib.h>
#include <stdio.h>
#include "object.h"
#include "Death.h"
extern unsigned int OOOOOOOOOOOOOOOOOO;
extern unsigned int XXXXXXXXXXXXXXXXXX;
extern unsigned int YYYYYYYYYYYYYYYYYY;
extern void ZZZZZZZZZZZZZZZZZZZZZZZ();

struct List* initList(){
    struct List* out = malloc(sizeof(struct List));
    out->head = NULL;
    out->tail = NULL;
    out->size = 0;
    return out;
}

LNode* AddToHead(struct List* list, void* obj, unsigned char obj_type){
    LNode* temp;
    LNode* opt = malloc(sizeof(LNode));
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

LNode* AddToTail(struct List* list, void* obj, unsigned char obj_type){
    LNode* temporary;
    LNode* opt = malloc(sizeof(LNode));
    opt->obj_type = obj_type;
    opt->item = obj;
    list->size += 1;
    opt->next = NULL;
    if(list->tail == NULL){
        list->tail = opt;
        list->head = opt;
        opt->prev = NULL;
        return opt;
    }
    temporary = list->tail;
    list->tail = opt;
    temporary->next = opt;
    opt->prev = temporary;
    return list->tail;
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

LNode* AddNodeToTail(struct List* list, LNode* opt){
    LNode* temporary;
    if(!opt){return NULL;}
    list->size += 1;
    opt->next = NULL;
    if(list->tail == NULL){
        list->tail = opt;
        list->head = opt;
        opt->prev = NULL;
        return opt;
    }
    temporary = list->tail;
    list->tail = opt;
    temporary->next = opt;
    opt->prev = temporary;
    return list->tail;
}



LNode* getNext(LNode* node){
    if(node){
        return node->next;
    }
    return NULL;
}


// assumes that node exists in list. Returns next pointer
LNode* Remove(struct List* list, LNode* it, struct List* death, void(*freeItem)(LNode* cur) ){
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


LNode* RemoveDeath(struct List* list, LNode* it, void(*freeItem)(LNode* cur) ){
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

void ClearList(struct List* list, struct List* Death, void(*freeData)(LNode* cur)){
    LNode* tmp;
    LNode* cur;
    if(list==NULL){
        return;
    }
    cur = list->head;
    while(cur){
        cur = Remove(list,cur,Death, freeData);
    }
}

void freeListItem(LNode* cur){
    switch (cur->obj_type)
    {
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
    if(item){
        switch(item->obj_type){
            case OBJ_PLAYER_ID:
                return UpdatePlayer(list, item, Death);
                break;
            case OBJ_BULLET_ID:
                return UpdateBullet(list, item, Death);
                break;
            case OBJ_METEOR_ID:
                return UpdateMeteor(list, item, Death);
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
