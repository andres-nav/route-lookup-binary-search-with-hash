#include <stdlib.h>

#include "tree.h"
#include "utils.h"

/*
 * Creates a new node given the table
 */
struct Node *createNode(char key) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  if (node == NULL) {
    return NULL;
  }

  node->key = key;
  node->table = NULL;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;

  return node;
}

/*
 * Returns the height of the node
 */
char getHeight(struct Node *node) {
  if (node == NULL) {
    return 0;
  }

  return node->height;
}

char updateHeightAddingOne(struct Node *node) {
  if (node == NULL) {
    return -1;
  }

  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  return 0;
}

/*
 * Rotates to the right the subtree rooted at y
 * --- y              ---
 * |            =>    |
 * x ---
 *     |
 *     z
 */
struct Node *rotateRight(struct Node *y) {
  if (y == NULL) {
    return NULL;
  }

  struct Node *x = y->left;
  struct Node *z = x->right;

  x->right = y;
  y->left = z;

  updateHeightAddingOne(x);
  updateHeightAddingOne(y);

  return x;
}

/*
 * Rotates to the left the subtree rooted at y
 * --- y              ---
 * |            =>    |
 * x ---
 *     |
 *     z
 */
struct Node *rotateLeft(struct Node *x) {
  if (x == NULL) {
    return NULL;
  }

  struct Node *y = x->left;
  struct Node *z = y->right;

  y->left = x;
  x->right = z;

  updateHeightAddingOne(x);
  updateHeightAddingOne(y);

  return y;
}

char getBalanceFactor(struct Node *node) {
  if (node == NULL) {
    return 0;
  }

  return getHeight(node->left) - getHeight(node->right);
}

struct Node *insertNode(struct Node *node, char key) {
  if (node == NULL) {
    return createNode(key);
  }

  if (key < node->key) {
    node->left = insertNode(node->left, key);
  } else if (key > node->key) {
    node->right = insertNode(node->right, key);
  } else {
    return node;
  }

  // Update balance factor
  updateHeightAddingOne(node);

  char balance = getBalanceFactor(node);
  if ((balance > 1) && (key < node->left->key)) {
    return rotateRight(node);
  }

  if ((balance < -1) && (key > node->right->key)) {
    return rotateLeft(node);
  }

  if ((balance > 1) && (key > node->left->key)) {
    node->left = rotateLeft(node);
    return rotateRight(node);
  }

  if ((balance < -1) && (key < node->right->key)) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

struct Node *deleteNode(struct Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));

  int balance = getBalanceFactor(root);
  if (balance > 1 && getBalanceFactor(root->left) >= 0)
    return rotateRight(root);

  if (balance > 1 && getBalanceFactor(root->left) < 0) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }

  if (balance < -1 && getBalanceFactor(root->right) <= 0)
    return rotateLeft(root);

  if (balance < -1 && getBalanceFactor(root->right) > 0) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }

  return root;
}
