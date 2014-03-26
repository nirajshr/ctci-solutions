#include "linked_list.h"

#include <iostream>
#include <map>

using namespace std;

typedef std::map<char, int> CharMap;


Node* sum(Node* num1, Node* num2) {
  Node* n1 = num1;
  Node* n2 = num2;

  Node* head_tot = 0, tail_tot = 0;
  int carry = 0;
  do {
    int tot = n1->val + n2->val;
    int lsb = tot % 10;

    if (!head_tot) {
      head_tot = new Node(lsb+carry);
    }
    else {
      head_tot->appendToTail(lsb+carry);
    }
    carry = tot > 9 ? 1 : 0;

    n1 = n1->next;
    n2 = n2->next;
  } while(n1 && n2);

  return head_tot;
}

int sumMsbImpl(Node* num1, Node* num2, Node* tot) {
  Node* n1 = num1;
  Node* n2 = num2;
  int carry = 0;
  int total = n1->val + n2->val;

  if (n1->next && n2->next) {
    Node* next_total = new Node(0);
    tot->next = next_total;

    int carry_frm_right = sumMsbImpl(n1->next, n2->next, next_total);
    total += carry_frm_right;
  }

  carry = total / 10;
  int lsb = total % 10;

  tot->val = lsb; 

  return carry;
}

Node*  sumMsb(Node* num1, Node* num2) {
  Node* total = new Node(0);
  sumMsbImpl(num1, num2, total);

  return total;
}


int main() {
  Node num1(7);
  num1.appendToTail(1);
  num1.appendToTail(6);

  Node num2(5);
  num2.appendToTail(9);
  num2.appendToTail(2);

  printNumLinkedList(&num1); 
  cout << " + " << endl;
  printNumLinkedList(&num2);

  printNumLinkedList(sum(&num1, &num2));


  Node num3(6);
  num3.appendToTail(1);
  num3.appendToTail(7);

  Node num4(2);
  num4.appendToTail(9);
  num4.appendToTail(5);

  printNumLinkedList(&num3); 
  cout << " + " << endl;
  printNumLinkedList(&num4);

  printNumLinkedList(sumMsb(&num3, &num4));



  return 0;
}
