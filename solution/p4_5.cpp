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
    tree->left->parent = tree;

    tree->right = createBinaryTree(nums, mid+1, right);
    tree->right->parent = tree;

    return tree;
  }

  return 0;
}


bool isBinaryTreeSearchTree(BinaryTree<int>* tree) {

  if (tree) {
    if (tree->left && tree->right) {
      if (tree->left->data < tree->data < tree->right->data) {
        bool is_lt_bst = isBinaryTreeSearchTree(tree->left);
        bool is_rt_bst = isBinaryTreeSearchTree(tree->right);
        return is_lt_bst && is_rt_bst;
      }
      return false;
    }
    else if (tree->left) {
      if (tree->left->data < tree->data) {
        return isBinaryTreeSearchTree(tree->left);
      }
      return false;
    }
    else if (tree->right) {
      if (tree->data < tree->right->data) {
        return isBinaryTreeSearchTree(tree->right);
      }
      return false;
    }
  }

  return true;
}

int main() {
  int nums[] = {1, 2, 3, 4, 5, 6, 7};

  BinaryTree<int>* tree = 
    createBinaryTree(nums, 0, sizeof (nums) / (sizeof(int))-1);

  traverse_tree<int>(tree, printTree);
  cout << endl;

  cout << "Is binary tree a BST: " << isBinaryTreeSearchTree(tree) << endl;

  tree->left->left->left = new BinaryTree<int>(99);
  cout << "Is binary tree a BST: " << isBinaryTreeSearchTree(tree) << endl;

  return 0;
}
