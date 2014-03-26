#include "linked_list.h"

#include <iostream>
#include <map>

using namespace std;

typedef std::map<char, int> CharMap;

void removeDuplicates(Node* head) {
  CharMap map;
  Node* n = head;
  do {
    map[n->val]++;
    n = n->next;
  } while(n);


  for(CharMap::const_iterator it = map.begin(); it != map.end(); ++it) {
    int cnt = it->second;
    while(cnt > 1) {
      head = removeNode(head, it->first);
      --cnt;
    }
  }
}

void removeDuplicatesWithoutBuffer(Node* head) {
  Node* n = head;

  while(n->next) {
    n->next = removeNode(n->next, n->val);
    n = n->next;
  };
    
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

  //removeNode(&node1, '!');
  //removeDuplicates(&node1);
  removeDuplicatesWithoutBuffer(&node1);

  printLinkedList(&node1);

  return 0;
}
