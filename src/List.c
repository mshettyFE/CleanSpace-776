#include "List.h"
#include "player.h"
#include "Bullet.h"
#include <stdlib.h>
#include <stdio.h>

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
    if(list->tail ==NULL && list->head == NULL){
        list->head = opt;
        list->tail = opt;
        opt->next = NULL;
    }
    if(list->head == NULL){
        list->head = opt;
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
    if(list->tail ==NULL && list->head == NULL){
        list->head = opt;
        list->tail = opt;
        opt->prev = NULL;
        return opt;
    }
    else if(list->tail == NULL){
        list->tail = opt;
        opt->prev = NULL;
        return opt;
    }
    temporary = list->tail;
    list->tail = opt;
    temporary->next = opt;
    opt->prev = temporary;
    return list->tail;
}

// assumes that node exists in list
LNode* Remove(struct List* list, LNode* it, void(*freeItem)(LNode* cur) ){
    LNode* temp;
    LNode* previous;
    LNode* next_one;
    if(it == NULL){
        return NULL;
    }
    if(list->head == it && list->tail==it){
        freeItem(it);
        list->head = NULL;
        list->tail = NULL;
        return NULL;
    }
    if(list->head == it){
        list->size -= 1;
        temp = list->head->next;
        freeItem(it);
        list->head = temp;
        return temp;
    }
    if(list->tail == it){
        list->size -= 1;
        temp = list->tail->prev;
        freeItem(it);
        list->tail = temp;
        return NULL;
    }
        previous = it->prev;
        next_one = it->next;
        freeItem(it);
        it = NULL;
        previous->next = next_one;
        next_one->prev = previous;
        list->size -= 1;
        return next_one;
}

void ClearList(struct List* list, void(*freeData)(LNode* cur)){
    LNode* tmp;
    LNode* cur;
    if(list==NULL){
        return;
    }
    cur = list->head;
    while(cur){
        cur = Remove(list,cur,freeData);
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
    }
    free(cur);
}

void TraverseList(struct List* list){
    LNode* cur = list->head;
    while(cur){
        ListItemAction(list, cur);
        cur = cur->next;
    }
}

LNode* ListItemAction(struct List* list, LNode* item){
    switch(item->obj_type){
        case OBJ_PLAYER_ID:
            UpdatePlayer(list, item->item);
            break;
        case OBJ_BULLET_ID:
            break;
    }
}


/*
void PrintList(struct List* list, void(*print)(void* data, unsigned char type)){
    if(list==NULL){
        printf("\n");
        return;
    }
    if(list->head == NULL){
        printf("\n");
        return;
    }
    LNode* it = list->head;
    while(it != NULL){
        print(it->item, it->obj_type);
        it = it->next;
    }
    printf("\n");
}
*/

/*
void printItem(LNode* cur){
  switch(cur->obj_type){
    case OBJ_ID:
        break;
    case OBJ_PLAYER_ID:
        break;
    case OBJ_METEOR_ID:
        break;
    case OBJ_BULLET_ID:
        break;
    case OBJ_DEATH_ID:
        break;
    }
  }
*/
