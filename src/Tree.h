#ifndef BINARY_TREE
#define BINARY_TREE

#include "object.h"

extern unsigned int counter;

#define OBJ_ID 0
#define OBJ_PLAYER_ID 1
#define OBJ_METEOR_ID 2
#define OBJ_BULLET_ID 3
#define OBJ_DEATH_ID 4

#define DONT_CLEAR_DATA 0
#define CLEAR_DATA 1

struct Node{
  void* obj;
  unsigned char obj_id;
  unsigned int node_id;
  unsigned char height;
  struct Node* left;
  struct Node* right;
};

int height(struct Node *N);

struct Node *newNode(void* obj, unsigned char a_obj_id );
void freeNode(struct Node* node);

struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);

int getBalance(struct Node *N);

struct Node *minValueNode(struct Node *node);

struct Head{
    struct Node* root;
    unsigned int size;
};

struct Head* initHead();

int get_depth(struct Head* tree);

int max(int a, int b);

struct Node *insert(struct Head* tree,void* a_obj, unsigned char a_obj_id);
struct Node *insertDirect(struct Head* tree, struct Node* node);
struct Node *insertWork(struct Node *node, struct Node *new_node);

struct Node* search(struct Head* tree,void* a_obj, unsigned char a_obj_id);
struct Node* searchWork(struct Node* cur_node, struct Node* search_node);

void clearAll(struct Head* tree, unsigned char clear_data);
void clearAllWork(struct Head* tree, struct Node* cur, unsigned char clear_data);

struct Node* delete(struct Head* tree, unsigned int id);
struct Node *deleteWork(struct Node *cur_node, struct Node* del_node);

void pollObjects(struct Head* tree, struct Head* old, struct Head* new);
void pollObjectsWork(struct Node* cur, struct Head* old, struct Head* new);

void TransferNodes(struct Head* dest, struct Head* src);
void TransferNodesWork(struct Head* dest, struct Node* cur);

#endif