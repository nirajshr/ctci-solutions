#include "data_structures.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

void printTree (BinaryTree<int>* tree) {
  cout << tree->data;
}

BinaryTree<int>* nextNodeInOrder(BinaryTree<int>* tree) {
  if (tree) {
    if (tree->right) return tree->right;
    else {
      if (tree->parent) {
        if(tree->parent->left == tree) {
          return tree->parent;
        }
        else {
          return nextNodeInOrder(tree->parent);
        }
      }
    }
  }

  return 0;
}

int main() {
  int nums[] = {1, 2, 3, 4, 5, 6, 7};

  BinaryTree<int>* tree =  new BinaryTree<int>(4);
  tree->left = new BinaryTree<int>(2);
  tree->left->left = new BinaryTree<int>(1);
  tree->left->right = new BinaryTree<int>(3);
  tree->right = new BinaryTree<int>(6);
  tree->right->left = new BinaryTree<int>(5);
  tree->right->right = new BinaryTree<int>(6);

  traverse_tree<int>(tree, printTree);
  cout << endl;

  BinaryTree<int>* search = searchTree(tree, 4);
  cout << "Next of 4: " << nextNodeInOrder(search)->data << endl;

  search = searchTree(tree, 1);
  cout << "Next of 1: " << nextNodeInOrder(search)->data << endl;
  return 0;
}
