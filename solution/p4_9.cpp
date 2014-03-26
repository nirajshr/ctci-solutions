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
    if (tree->left) tree->left->parent = tree;

    tree->right = createBinaryTree(nums, mid+1, right);
    if (tree->right) tree->right->parent = tree;

    return tree;
  }

  return 0;
}

BinaryTree<int>* ifTreeSumsToImpl(BinaryTree<int>* tree, int* sum) {
  if (tree) {
    *sum -= tree->data;

    if (*sum == 0) return tree;

    if (tree->left) {
      BinaryTree<int>* ret = ifTreeSumsToImpl(tree->left, sum);
      if(ret) return ret;
      else *sum += tree->left->data;
    }

    if (tree->right) {
      BinaryTree<int>* ret = ifTreeSumsToImpl(tree->right, sum);
      if(ret) return ret;
      else *sum += tree->right->data;
    }
  }

  return 0;
}

bool ifTreeSumsTo(BinaryTree<int>* tree, int sum) {
  return ifTreeSumsToImpl(tree, &sum);
}

void printSumToNum(BinaryTree<int>* tree, int sum) {
  int local_sum = sum;

  BinaryTree<int>* ret = ifTreeSumsToImpl(tree, &local_sum);

  if (ret) {
    cout << ret->data;
    while (ret && ret != tree) {
      ret = ret->parent;
      if (ret)
        cout << " + " << ret->data;
    };

    cout << " => " << sum << endl;
  }
}

void printAllPathThatSumToNum(BinaryTree<int>* tree, int sum) {
  if (tree) {
    printSumToNum(tree, sum);
    printAllPathThatSumToNum(tree->left, sum);
    printAllPathThatSumToNum(tree->right, sum);
  }
}

int main() {
  int input_num = 0;
  std::cout << "Input Num :";
  std::cin >> input_num;

  int nums[] = {-3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  BinaryTree<int>* tree = 
    createBinaryTree(nums, 0, sizeof (nums) / (sizeof(int))-1);

  traverse_tree<int>(tree, printTree); cout << endl;

  //cout << "Sums to :" << input_num << " ? => " << ifTreeSumsTo(tree, input_num) << endl;

  //printSumToNum(tree, input_num);

  cout << "All Path" << endl;
  printAllPathThatSumToNum(tree, input_num);

  return 0;
}
