#include "linked_list.h"

#include <iostream>

using namespace std;

void printLinkedList(Node* node) {
  Node* n = node;
  while(n->next) {
    cout << (char)n->val << "->";
    n = n->next;
  }
  cout << (char)n->val;
  cout << endl;
}

int main() {
  Node node1('A');
  node1.appendToTail('B');
  node1.appendToTail('A');
  node1.appendToTail('C');
  node1.appendToTail('U');
  node1.appendToTail('S');

  printLinkedList(&node1);

  Node* head = removeNode(&node1, 'Z');
  head = removeNode(head, 'S');
  printLinkedList(head);

  return 0;
}
