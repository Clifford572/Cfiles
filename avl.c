#include <stdio.h>
#include <stdlib.h>
typedef struct avlnode {
  int value;
  int height;
  struct avlnode *right, *left;
} avlnode;
// Create Node
avlnode *createnode(int value) {
  avlnode *newnode = (avlnode *)malloc(sizeof(avlnode));
  newnode->value = value;
  newnode->height = 1;
  newnode->left = newnode->right = NULL;
  return newnode;
}
// Calculating Height
int findHeight(avlnode *root) {
  if (root == NULL) {
    return 0;
  }
  return root->height;
}
// Comparing the size of the left and right side
int max(int left, int right) {
  if (left > right) {
    return left;
  } else {
    return right;
  }
}
avlnode *min(avlnode *node) {
  avlnode *cur = node;
  while (cur->left != NULL) {
    cur = cur->left;
  }
  return cur;
}
// Calculating Balance Factor
int balanceFactor(avlnode *root) {
  if (root == NULL) {
    return 0;
  } else {
    return findHeight(root->left) - findHeight(root->right);
  }
}
avlnode *rightRotate(avlnode *y) {
  avlnode *x = y->left;
  avlnode *x_child = x->right;

  x->right = y;
  y->left = x_child;

  y->height = max(findHeight(y->left), findHeight(y->right)) + 1;
  x->height = max(findHeight(x->left), findHeight(x->right)) + 1;

  return x;
}
avlnode *leftRotate(avlnode *x) {
  avlnode *y = x->right;
  avlnode *y_child = y->left;

  y->left = x;
  x->right = y_child;

  y->height = max(findHeight(y->left), findHeight(y->right)) + 1;
  x->height = max(findHeight(x->left), findHeight(x->right)) + 1;

  return y;
}
// Inserting Node
avlnode *insertnode(avlnode *root, int value) {
  if (root == NULL) {
    return createnode(value);
  }
  if (value < root->value) {
    root->left = insertnode(root->left, value);
  } else if (value > root->value) {
    root->right = insertnode(root->right, value);
  }
  root->height = max(findHeight(root->left), findHeight(root->right)) + 1;
  int bfactor = balanceFactor(root);
  if (bfactor > 1 && value < root->left->value) {
    return rightRotate(root);
  } else if (bfactor < -1 && value > root->right->value) {
    return leftRotate(root);

  } else if (bfactor > 1 && value > root->left->value) {
    root->left = leftRotate(root->left);
    return rightRotate(root);

  } else if (bfactor < -1 && value < root->right->value) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}
avlnode *deletenode(avlnode *root, int value) {
  if (root == NULL) {
    return NULL;
  } else if (value < root->value) {
    root->left = deletenode(root->left, value);
  } else if (value > root->value) {
    root->right = deletenode(root->right, value);
  } else {
    if (root->left == NULL || root->right == NULL) {
      avlnode *temp = NULL;
      if (root->left != NULL) {
        temp = root->left;
      } else {
        temp = root->right;
      }
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
        free(temp);
      }
    } else {
      avlnode *temp = min(root->right);
      root->value = temp->value;
      root->right = deletenode(root->right, temp->value);
    }
  }
  if (root == NULL) {
    return root;
  }
  root->height = max(findHeight(root->left), findHeight(root->right)) + 1;
  int bfactor = balanceFactor(root);
  if (bfactor > 1 && value < root->left->value) {
    return rightRotate(root);
  } else if (bfactor < -1 && value > root->right->value) {
    return leftRotate(root);

  } else if (bfactor > 1 && value > root->left->value) {
    root->left = leftRotate(root->left);
    return rightRotate(root);

  } else if (bfactor < -1 && value < root->right->value) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}
void printTree(avlnode *root) {
  if (root == NULL) {
    return;
  }
  printf("%d | %d\n", root->value, root->height);
  printTree(root->left);
  printTree(root->right);
}
int main() {
  avlnode *root = NULL;
  while (1) {
    if (root != NULL) {
      printTree(root);
    }
    printf("1. Insert\n2. Delete\n");
    int input;
    scanf("%d", &input);
    // Insert
    if (input == 1) {
      printf("Enter a number from 1 - 100\n");
      int insert;
      scanf("%d", &insert);
      if (insert <= 0 || insert > 100) {
        continue;
      } else {
        root = insertnode(root, insert);
      }
    }
    // Delete
    if (input == 2) {
      printf("Enter a number from 1 - 100\n");
      int erase;
      scanf("%d", &erase);
      if (erase <= 0 || erase > 100) {
        continue;
      } else {
        root = deletenode(root, erase);
      }
    }
  }
  return 0;
}
