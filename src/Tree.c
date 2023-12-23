#include "Tree.h"
#include <stdlib.h>

#include "player.h"
#include "Bullet.h"
#include "globals.h"

unsigned int counter = 0;

// AVL tree implementation in C. Adapted from https://www.programiz.com/dsa/avl-tree

struct Head* initHead(){
    struct Head *output = malloc(sizeof(struct Head));
    output->root = NULL;
    output->size = 0;
    return output;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int get_depth(struct Head* tree){
  if(tree == NULL){
    return 0;
  }
  if(tree->root == NULL){
    return 0;
  }
  return tree->root->height;
}

struct Node *newNode(void* obj, unsigned char a_obj_id) {
  struct Node *node = malloc(sizeof(struct Node));
  node->obj = obj;
  node->obj_id = a_obj_id;
  node->node_id = counter;
  counter++;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}


struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

struct Node *insert(struct Head* tree,void* a_obj, unsigned char a_obj_id){
    struct Node* new_node = newNode(a_obj, a_obj_id);
    tree->root = insertWork(tree->root, new_node);
    tree->size += 1;
    return new_node;
}

struct Node *insertWork(struct Node *node, struct Node *new_node) {
  int balance;
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL){
    node = new_node;
    return node;
  }
  if(new_node==NULL){
    return new_node;
  }
  
  if(new_node->node_id == node->node_id){
    counter++;
    new_node->node_id++;
  }

  if (new_node->node_id < node->node_id)
    node->left = insertWork(node->left, new_node);
  if (node->node_id < new_node->node_id)
    node->right = insertWork(node->right, new_node);

  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));

  balance = getBalance(node);
  if (balance > 1 && new_node->node_id < node->left->node_id)
    return rightRotate(node);

  if (balance < -1 && new_node->node_id > node->right->node_id)
    return leftRotate(node);

  if (balance > 1 && new_node->node_id > node->left->node_id) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && new_node->node_id < node->right->node_id) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *insertDirect(struct Head* tree, struct Node* node){
    tree->root = insertWork(tree->root, node);
    tree->size += 1;
    return node;
}

void freeNode(struct Node* node){
    if(node == NULL){
        return;
    }
    switch (node->obj_id)
    {
    case OBJ_PLAYER_ID:
        freePlayer((struct Player * ) node->obj);
        break;    
    case OBJ_BULLET_ID:
        freeBullet((struct Bullet * ) node->obj);
        break;    
    default:
        freeObj( (struct Object *)  node->obj);
        break;
    }
    free(node);
}

struct Node* search(struct Head* tree, void* a_obj, unsigned char a_obj_id){
    struct Node* tempNode;
    struct Node* result;

    if(tree==NULL){
      return NULL;
    }

    if(tree->root==NULL){
      return NULL;
    }

    tempNode = newNode(a_obj, a_obj_id);
    result = searchWork(tree->root, tempNode);
    // only freeing Node, not the underlying data.
    // This is fine, since the node is temporary, but the data is persistent
    free(tempNode);

    return result;
}

struct Node* searchWork(struct Node* cur_node, struct Node* search_node){
    struct Node* left;
    struct Node* right;
    if(cur_node==NULL){
      return NULL;
    }

    if((cur_node->obj == search_node->obj)){
        return cur_node;
    }
    
    left = searchWork(cur_node->left, search_node);
    right = searchWork(cur_node->right, search_node);
    if(left != NULL){
        return left;
    }
    if(right != NULL){
        return right;
    }
    return NULL;
}

void clearAll(struct Head* tree, unsigned char clear_data){
  clearAllWork(tree, tree->root, clear_data);
}

void clearAllWork(struct Head* tree, struct Node* cur, unsigned char clear_data){
  if(cur != NULL){
    clearAllWork(tree, cur->left, clear_data);
    clearAllWork(tree, cur->right, clear_data);
    if(clear_data==DONT_CLEAR_DATA){
    // only clear 
      free(cur);     
    }
    else{
      freeNode(cur);
    }
    tree->size -= 1;
  }
}

struct Node* delete(struct Head* tree, unsigned int id){
    struct Node* search_Node;
    struct Node* result;
    if(tree==NULL){
        return NULL;
    }
    if(tree->root ==NULL){
        return NULL;
    }
    search_Node = newNode(NULL, OBJ_PLAYER_ID);
    search_Node->node_id = id;
    result = deleteWork(tree->root, search_Node);
    if(result != NULL){
      tree->size -= 1;
    }
    free(search_Node);
    return result;
}

struct Node *deleteWork(struct Node *cur_node, struct Node* del_node) {
  int balance;
  if (cur_node == NULL)
    return cur_node;
  if (del_node == NULL)
    return del_node;

  if (del_node->node_id < cur_node->node_id){
    cur_node->left = deleteWork(cur_node->left, del_node);
  }
  else if (del_node->node_id > cur_node->node_id){
    cur_node->right = deleteWork(cur_node->right, del_node);
  }
  else {
    if ((cur_node->left == NULL) && (cur_node->right == NULL)) {
      // both left and right are NULL
      // Hence, can just set cur_node to null (temp variable needed to free memory)
        freeNode(cur_node);
        cur_node = NULL;
    }
    else if ((cur_node->left == NULL) || (cur_node->right == NULL)) {
      struct Node *temp = cur_node->left ? cur_node->left : cur_node->right;
      freeNode(cur_node);
      cur_node = temp;
    }
    else {
      struct Node *temp = minValueNode(cur_node->right);
      cur_node = temp;
      cur_node->right = deleteWork(cur_node->right, del_node);
    }
  }

  if (cur_node == NULL)
    return cur_node;

  // Update the balance factor of each node and
  // balance the tree
  cur_node->height = 1 + max(height(cur_node->left),
               height(cur_node->right));

  balance = getBalance(cur_node);
  if (balance > 1 && getBalance(cur_node->left) >= 0)
    return rightRotate(cur_node);

  if (balance > 1 && getBalance(cur_node->left) < 0) {
    cur_node->left = leftRotate(cur_node->left);
    return rightRotate(cur_node);
  }

  if (balance < -1 && getBalance(cur_node->right) <= 0)
    return leftRotate(cur_node);

  if (balance < -1 && getBalance(cur_node->right) > 0) {
    cur_node->right = rightRotate(cur_node->right);
    return leftRotate(cur_node);
  }

  return cur_node;
}

void pollObjects(struct Head* tree, struct Head* new, struct Head* old){
  pollObjectsWork(tree->root, new, old);
}

void pollObjectsWork(struct Node* cur, struct Head* new, struct Head* old){
  if(cur != NULL){
    pollObjectsWork(cur->left, new, old);
    pollObjectsWork(cur->right, new, old);
    switch (cur->obj_id)
    {
      case OBJ_PLAYER_ID:
        UpdatePlayer((struct Player *) cur->obj, new, old);
        break;
      case OBJ_BULLET_ID:
        UpdateBullet((struct Bullet *) cur->obj, new, old);
        break;
      default:
        break;
    }
  }
}

void TransferNodes(struct Head* dest, struct Head* src){
  TransferNodesWork(dest, src->root);
}
void TransferNodesWork(struct Head* dest, struct Node* cur){
  if(cur != NULL){
    TransferNodesWork(dest, cur->left);
    TransferNodesWork(dest, cur->right);
    insertDirect(dest,cur);
  }
}