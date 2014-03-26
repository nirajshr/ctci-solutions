#include "data_structures.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

void printTree (BinaryTree<int>* tree) {
  cout << tree->data << endl;
}

BinaryTree<int>* createBinaryTree(int nums[], int left, int right) {
  cout << "CreateBinaryTree (" << left << "," << right << ")" << endl;
  if (left <= right) {
    int mid = (left + right) / 2;
    BinaryTree<int>* tree = new BinaryTree<int>(nums[mid]);
    tree->left = createBinaryTree(nums, left, mid-1);
    tree->right = createBinaryTree(nums, mid+1, right);

    return tree;
  }

  return 0;
}

int main() {
  int nums[] = {1, 2, 3, 4, 5, 6, 7};

  BinaryTree<int>* tree = 
    createBinaryTree(nums, 0, sizeof (nums) / (sizeof(int))-1);

  traverse_tree<int>(tree, printTree);
  cout << endl;

  return 0;
}
