#include "data_structures.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>

using namespace std;

void printTree (BinaryTree<char>* tree) {
  cout << tree->data << endl;
}

int findHeight (BinaryTree<char>* tree) {
  if (tree) {
    int left_tree_cnt = findHeight(tree->left);
    int right_tree_cnt = findHeight(tree->right);
    return std::max(left_tree_cnt, right_tree_cnt) + 1;
  }

  return 0;
}

int isBalancedImpl (BinaryTree<char>* tree, bool* balanced) {
  if (tree) {
    int left_tree_cnt = findHeight(tree->left);
    int right_tree_cnt = findHeight(tree->right);
    if (abs(left_tree_cnt - right_tree_cnt) > 1) {
      *balanced = false;
    }
    return std::max(left_tree_cnt, right_tree_cnt) + 1;
  }

  return 0;
}

bool isBalanced (BinaryTree<char>* tree) {
  bool balanced = true;
  isBalancedImpl(tree, &balanced);
  return balanced;
}

int main() {

  BinaryTree<char>* tree = new BinaryTree<char>('M');
  tree->left = new BinaryTree<char>('I');
  tree->right = new BinaryTree<char>('T');
  tree->right->left = new BinaryTree<char>('Q');
  tree->left->left = new BinaryTree<char>('B');

  insert_tree<char>(&tree, 'E', tree);

  cout << "Height: " << findHeight(tree) << endl;
  cout << "isBalanced: " << isBalanced(tree) << endl;

  insert_tree<char>(&tree, 'D', tree);
  cout << "isBalanced: " << isBalanced(tree) << endl;


  return 0;
}
