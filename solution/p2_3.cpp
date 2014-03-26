#include "linked_list.h"

#include <iostream>
#include <map>

using namespace std;

typedef std::map<char, int> CharMap;

void pullNodeOut(Node* node) {
  Node* next = node->next;

  if (next) {
    node->val = next->val;
    node->next = next->next;
  }
  else {
    delete node;
  }
}

int main() {
  Node node1('F');
  node1.appendToTail('!');
  node1.appendToTail('O');
  node1.appendToTail('L');
  node1.appendToTail('L');
  node1.appendToTail('L');
  node1.appendToTail('O');
  node1.appendToTail('W');
  node1.appendToTail(' ');
  node1.appendToTail('U');
  node1.appendToTail('P');
  node1.appendToTail('!');

  printLinkedList(&node1);

  pullNodeOut(node1.next->next->next->next->next->next->next->next->next->next);
  printLinkedList(&node1);
  return 0;
}
