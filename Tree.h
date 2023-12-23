#ifndef BINARY_TREE
#define BINARY_TREE

#include "object.h"
#include "player.h"

extern unsigned int counter;

#define OBJ_ID 0
#define OBJ_PLAYER_ID 1
#define OBJ_METEOR_ID 2
#define OBJ_BULLET_ID 3
#define OBJ_DEATH_ID 4

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


void traverseTree(struct Head* tree);
void viewBranch(struct Node* node);

void clearAll(struct Head* tree);
void clearAllWork(struct Head* tree, struct Node* cur);

int get_depth(struct Head* tree);

int max(int a, int b);

struct Node *insert(struct Head* tree,void* a_obj, unsigned char a_obj_id);
struct Node *insertNode(struct Node *node, struct Node *new_node);

struct Node* search(struct Head* tree,struct Player* plyr);
struct Node* searchNode(struct Node* cur_node, struct Node* search_node);

struct Node* delete(struct Head* tree, unsigned int id);
struct Node *deleteNode(struct Node *cur_node, struct Node* del_node);

#endif