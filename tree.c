#include "tree.h"

/*
 * Returns the height of the node
 */
static char getHeight(struct Node *node) {
  if (node == NULL) {
    return 0;
  }

  return node->height;
}

/*
 * Updates the maxiumum height of the tree adding one
 */
static char updateMaxHeightPlusOne(struct Node *node) {
  if (node == NULL) {
    return -1;
  }

  node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  return 0;
}

/*
 * Returns the balance factor of a node
 */
static char getBalanceFactor(struct Node *node) {
  if (node == NULL) {
    return 0;
  }

  return getHeight(node->left) - getHeight(node->right);
}

/*
 * Computes the minimum value node, that is the most left node
 */
static struct Node *getMinValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

/*
 * Rotates to the right the subtree rooted at x
 *     x -- y        x --- TODO
 *     |                |
 *     x ---   =>   --- y
 *         |        |
 *         z        z
 */
static struct Node *rotateLeft(struct Node *x) {
  if (x == NULL) {
    return NULL;
  }

  struct Node *y = x->right;
  struct Node *z = y->left;

  y->left = x;
  x->right = z;

  updateMaxHeightPlusOne(x);
  updateMaxHeightPlusOne(y);

  return y;
}

/*
 * Rotates to the right the subtree rooted at y
 *     x ---        --- y TODO
 *         |            |
 *      y   =>   x ---
 *         |            |
 *         z            z
 */
static struct Node *rotateRight(struct Node *y) {
  if (y == NULL) {
    return NULL;
  }

  struct Node *x = y->left;
  struct Node *z = x->right;

  x->right = y;
  y->left = z;

  updateMaxHeightPlusOne(y);
  updateMaxHeightPlusOne(x);

  return x;
}

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
  updateMaxHeightPlusOne(node);

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

struct Node *deleteNode(struct Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (key < root->key) {
    root->left = deleteNode(root->left, key);
  } else if (key > root->key) {
    root->right = deleteNode(root->right, key);
  } else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = getMinValueNode(root->right);

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

static void printNode(struct Node *node, char space) {}

void printTree(struct Node *root, char space) {
  int count = 1;
  if (root == NULL) {
    return;
  }
  space += count;
  printTree(root->right, space);

  for (int i = count; i < space; i++) {
    printf("\t");
  }
  printf("%d\n", root->key);
  printTree(root->left, space);
}
