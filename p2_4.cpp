#include "linked_list.h"

#include <iostream>
#include <map>

using namespace std;

typedef std::map<char, int> CharMap;


Node* partitionAround(Node* node, char pivot) {
  Node* gt_head = 0;
  Node* gt_tail = 0;
  Node* lt_head = 0;
  Node* lt_tail = 0;

  Node* n = node;
  do {
    Node* next_node = n->next;

    if (n->val > pivot) {
      if (!gt_head) gt_head = n;
      else gt_tail->next = n;

      gt_tail = n;
      n->next = 0;
    }
    else {
      if(!lt_head) lt_head = n;
      else lt_tail->next = n;

      lt_tail = n;
      n->next = 0;
    }

    n = next_node;
  } while(n);

  lt_tail->next = gt_head;
  return lt_head;
}

int main() {
  Node node1('F');
  node1.appendToTail('O');
  node1.appendToTail('L');
  node1.appendToTail('L');
  node1.appendToTail('L');
  node1.appendToTail('O');
  node1.appendToTail('W');
  node1.appendToTail('M');
  node1.appendToTail('Y');
  node1.appendToTail('B');
  node1.appendToTail('E');
  node1.appendToTail('S');
  node1.appendToTail('T');

  printLinkedList(&node1);

  Node* head = partitionAround(&node1, 'N');

  printLinkedList(head);

  return 0;
}
