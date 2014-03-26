#include "data_structures.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

void printTree (BinaryTree<int>* tree) {
  cout << tree->data << " ";
}

BinaryTree<int>* createBinaryTree(int nums[], int left, int right) {
  if (left <= right) {
    int mid = (left + right) / 2;
    BinaryTree<int>* tree = new BinaryTree<int>(nums[mid]);
    tree->left = createBinaryTree(nums, left, mid-1);
    tree->right = createBinaryTree(nums, mid+1, right);

    return tree;
  }

  return 0;
}

bool twoSameTree(BinaryTree<int>* tree1, BinaryTree<int>* tree2) {
  cout << "twoSameTree :" << (tree1 ? tree1->data : -1) << ", ";
  cout << (tree2 ? tree2->data : -1) << endl;

  if (tree1 && tree2) {
    bool nodeSame = tree1->data == tree2->data;
    if (nodeSame) {
      bool leftTreeSame = twoSameTree(tree1->left, tree2->left);
      bool rightTreeSame = twoSameTree(tree1->right, tree2->right);

      return leftTreeSame && rightTreeSame;
    }
    return false;
  }
  else if (!tree1 && !tree2) {
    return true;
  }

  return false;
}

int main() {
  int nums[] = {1, 2, 3, 4, 5, 6, 7};

  BinaryTree<int>* tree = 
    createBinaryTree(nums, 0, sizeof (nums) / (sizeof(int))-1);

  BinaryTree<int>* tree2 = 
    createBinaryTree(nums, 0, sizeof (nums) / (sizeof(int))-1);

  traverse_tree<int>(tree, printTree); cout << endl;
  traverse_tree<int>(tree2, printTree); cout << endl;

  bool is_same = twoSameTree(tree, tree2);
  cout << "Same: " << is_same << endl;

  insert_tree(&tree, 33, tree);
  is_same = twoSameTree(tree, tree2);
  cout << "Same: " << is_same << endl;

  return 0;
}
