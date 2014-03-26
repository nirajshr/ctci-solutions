#include "data_structures.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  Node<int> node1(23);
  Node<std::string> node2("Testing");

  cout << node1.val << endl;
  cout << node2.val << endl;

  //Stack<char> int_stack;
  Queue<char> int_stack;

  int_stack.enqueue('E');
  int_stack.enqueue('L');
  int_stack.enqueue('P');
  int_stack.enqueue('P');
  int_stack.enqueue('A');

  while (!int_stack.empty()) {
    cout << int_stack.dequeue() << endl;
  }
  return 0;
}
