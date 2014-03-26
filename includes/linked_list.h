#include <iostream>

class Node {
  public:
    Node (int value) : next(0), val(value) {
    }
    ~Node() {
      std::cout << "Remove Node: " << (char)val << std::endl;
      //if (next) delete next;
    }

    void appendToTail(int value) {
      Node* end = new Node(value);

      Node* n = this;
      while(n->next) {
        n = n->next;
      }
      n->next = end;
    }


    Node* next;
    int val;
};

Node* removeNode(Node* head, int value) {
  Node* n = head;

  while(n && n->next) {
    if (n->next->val == value) {
      Node* to_be_deleted = n->next;
      n->next = to_be_deleted->next;

      to_be_deleted->next = 0;
      delete to_be_deleted;
    }
    n = n->next;
  }

  if (head->val == value) {
    Node* temp = head->next;
    delete head;
    head = temp;
  }

  return head;
}
void printNumLinkedList(Node* node) {
  Node* n = node;
  while(n->next) {
    std::cout << n->val << "->";
    n = n->next;
  }
  std::cout << n->val;
  std::cout << std::endl;
}

void printLinkedList(Node* node) {
  Node* n = node;
  while(n->next) {
    std::cout << (char)n->val << "->";
    n = n->next;
  }
  std::cout << (char)n->val;
  std::cout << std::endl;
}

