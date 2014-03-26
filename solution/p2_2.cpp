#include "linked_list.h"

#include <iostream>
#include <map>

using namespace std;

typedef std::map<char, int> CharMap;


Node* findKNode(Node* node, int k) {
  Node* n = node;

  int count = 1;
  while(n->next) {
    count++;
    n = n->next;
  };

  int target_ind = count - k - 1;
  if (target_ind < 0) return 0;

  int i = 0;
  n = node;
  do {
    if (i == target_ind) return n;
    n = n->next;
    ++i;
  } while (n);

  return 0;
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

  cout << (char)findKNode(&node1, 4)->val << endl;
  cout << (char)findKNode(&node1, 9)->val << endl;
  cout << (char)findKNode(&node1, 0)->val << endl;
  return 0;
}
