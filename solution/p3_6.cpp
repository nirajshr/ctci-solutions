#include "data_structures.h"

#include <iostream>
#include <vector>

using namespace std;

bool  lessThanComparator(char a, char b) { return a<b; }
bool greaterThanComparator(char a, char b) { return a>b; }

void move(Stack<char>* source, Stack<char>* dest, bool (* compareFn)(char, char)  ) {
  while(!source->empty()) {
    char s_top = source->pop();
    if (dest->empty()) {
      dest->push(s_top);
    }
    else {
      char r_top = dest->peek();
      if (compareFn(s_top, r_top)) {
        r_top = dest->pop();
        dest->push(s_top);
        dest->push(r_top);
      }
      else {
        dest->push(s_top);
      }
    }
  }

}
void sort(Stack<char>* source) {
  Stack<char> temp_v;
  Stack<char>* temp = &temp_v;

  for (int i=0; i<20; ++i) {
    move(source, temp, greaterThanComparator);
    move(temp, source, lessThanComparator);
  }
}

int main() {
  string str("a quick brown fox jumped over the lazy dog");
  Stack<char> stack;

  for (int i=0; i<str.length(); ++i) {
    stack.push(str[i]);
  }

  sort(&stack);

  while(!stack.empty()) {
    cout << stack.pop() << " ";
  }

  cout << endl;
  return 0;
}
