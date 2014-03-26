#include "data_structures.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printTree (BinaryTree<char>* tree) {
  cout << tree->data << endl;
}


int main() {

  BinaryTree<char>* tree = new BinaryTree<char>('M');
  tree->left = new BinaryTree<char>('I');
  tree->right = new BinaryTree<char>('T');
  tree->right->left = new BinaryTree<char>('Q');
  tree->left->left = new BinaryTree<char>('A');

  insert_tree<char>(&tree, 'D', tree);

  BinaryTree<char>* search = searchTree(tree, 'Q');
  cout << "search: " << (search ? search->data : ' ') << endl;

  search = 0;
  search = findMin(tree);
  cout << "findMin: " << (search ? search->data : ' ') << endl;

  search = 0;
  search = findMax(tree);
  cout << "findMax: " << (search ? search->data : ' ') << endl;

  traverse_tree(tree, printTree);
  return 0;
}
