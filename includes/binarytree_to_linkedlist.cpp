#include "data_structures.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printTree (BinaryTree<char>* tree) {
  cout << tree->data << endl;
}

Node<char> g_node(' ');

template <typename T>
void addToList(BinaryTree<T>* tree) {
  cout << "adding val: " << tree->data << endl;
  g_node.appendToTail(tree->data);
}

void convertBinaryTreetoLinkedList(BinaryTree<char>* tree) {
  traverse_tree(tree, &addToList);
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

  convertBinaryTreetoLinkedList(tree);
  Node<char>* n = &g_node;
  while (n) {
    cout << n->val << " ";
    n = n->next;
  };
  cout << endl;
  return 0;
}
