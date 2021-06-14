#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numChar 256
typedef struct trienode {
  struct trienode *children[numChar];
  bool terminal;
} trienode;

trienode *createnode() {
  trienode *temp = (trienode *)malloc(sizeof(trienode));
  for (int i = 0; i < numChar; i++) {
    temp->children[i] = NULL;
  }
  temp->terminal = false;
  return temp;
}
bool trieinsert(trienode **root, const char *textvalue) {
  if (*root == NULL) {
    *root = createnode();
  }
  unsigned const char *text = (unsigned const char *)textvalue;
  trienode *temp = *root;
  int length = strlen(textvalue);
  for (int i = 0; i < length; i++) {
    if (temp->children[text[i]] == NULL) {
      temp->children[text[i]] = createnode();
    }
    temp = temp->children[text[i]];
  }
  if (temp->terminal) {
    return false;
  } else {
    temp->terminal = true;
    return true;
  }
}
void printTrieAgain(trienode *curnode, unsigned const char *prefix,
                    int length) {
  unsigned char newprefix[length + 2];
  memcpy(newprefix, prefix, length);
  newprefix[length + 1] = 0;
  if (curnode->terminal) {
    printf("Word : %s\n", prefix);
  }
  for (int i = 0; i < numChar; i++) {
    if (curnode->children[i] != NULL) {
      newprefix[length] = i;
      printTrieAgain(curnode->children[i], newprefix, length + 1);
    }
  }
}
void printTrie(trienode *root) {
  if (root == NULL) {
    printf("Your Trie is empty\n");
    return;
  }
  printTrieAgain(root, NULL, 0);
}
int main() {
  trienode *root = NULL;
  trieinsert(&root, "PEE");
  trieinsert(&root, "BIG");
  trieinsert(&root, "CHUNGUS");
  trieinsert(&root, "POO");
  trieinsert(&root, "PEU");
  printTrie(root);
  return 0;
}
