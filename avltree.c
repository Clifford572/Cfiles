#include <stdio.h>
#include <stdlib.h>
void clrscr() { system("@cls|clear"); }
typedef struct avlnode {
  int value;
  int height;
  struct avlnode *right, *left;
} avlnode;
avlnode *root = NULL;
// Create Node
avlnode *createnode(int value) {
  avlnode *temp = (avlnode *)malloc(sizeof(avlnode));
  temp->value = value;
  temp->height = 1;
  temp->right = temp->left = NULL;
  return temp;
}

// Calculating Height
int findHeight(avlnode *root) {
  if (root == NULL) {
    return 0;
  }
  return root->height;
}

// Checking which side has more children
int max(int left, int right) {
  if (left < right) {
    return right;
  } else {
    return left;
  }
}
// Finding the minimum value in the tree
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
    return (findHeight(root->left) - findHeight(root->right));
  }
}
// Rotate Right
avlnode *rightRotate(avlnode *y) {
  avlnode *x = y->left;
  avlnode *x_child = x->right;

  x->right = y;
  y->left = x_child;

  y->height = max(findHeight(y->left), findHeight(y->right)) + 1;
  x->height = max(findHeight(x->left), findHeight(x->right)) + 1;

  return x;
}
// Rotate Left
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
void preOrder(avlnode *root) {
  if (root == NULL) {
    return;
  }
  printf("%d ", root->value);
  preOrder(root->left);
  preOrder(root->right);
}
void inOrder(avlnode *root) {
  if (root == NULL) {
    return;
  }
  inOrder(root->left);
  printf("%d ", root->value);
  inOrder(root->right);
}
void postOrder(avlnode *root) {
  if (root == NULL) {
    return;
  }
  postOrder(root->left);
  postOrder(root->right);
  printf("%d ", root->value);
}
int main() {
  while (1) {
    int number, temp;
    printf("1. Insertion\n2. Deletion\n3. Traversal\n4. Exit\nChoose: ");
    scanf("%d", &number);
    switch (number) {
    case 1:
      printf("Insert: ");
      scanf("%d", &temp);
      root = insertnode(root, temp);
      break;
    case 2:
      printf("Delete: ");
      scanf("%d", &temp);
      root = deletenode(root, temp);
      break;
    case 3:
      printf("Preorder: ");
      preOrder(root);
      printf("\n");
      printf("Inorder: ");
      inOrder(root);
      printf("\n");
      printf("Postorder: ");
      postOrder(root);
      printf("\n");
      getchar();
      getchar();
      break;
    case 4:
      printf("Thank You\n");
      return 0;
      break;
    }
    clrscr();
  }
  return 0;
}
