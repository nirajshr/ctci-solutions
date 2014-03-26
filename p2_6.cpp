#include "linked_list.h"

#include <iostream>
#include <map>

using namespace std;

typedef std::map<char, int> CharMap;


bool hasCycle(Node* head) {
  Node* hare = head;
  Node* turtoise  = head;


  while(hare && hare->next && turtoise && turtoise->next) {
    cout << (char)turtoise->val << ", ";
    cout << (char)hare->val << "-->";
    turtoise = turtoise->next;
    hare = hare->next->next;

    if (turtoise == hare) return true;
  };

  return false;
}

int main() {
  Node num1('A');
  num1.appendToTail('B');
  Node* node = new Node('C');

  num1.next->next = node;
  num1.appendToTail('D');
  num1.appendToTail('E');

  node->next->next->next = node;

  cout << hasCycle(&num1) << endl;

  return 0;
}
