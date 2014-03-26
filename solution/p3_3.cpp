#include "data_structures.h"

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct StackWithCount {
  StackWithCount () : stack(0), count(0) {};
  StackWithCount (Stack<T>* stk, int size=0) : stack(stk), count(size) {};

  Stack<T>* stack;
  int count;
};

template <typename T>
class SetOfStacks {
  public:
    enum { MAX_HEIGHT = 5 };

    SetOfStacks() {
      Stack<T>* stack = new Stack<T>();
      stacks.push_back(stack);
      curr_stack = 0;
    }

    void push(T const& value) {
      StackWithCount<T>& stack_info = stacks[curr_stack];
      if (stack_info.count >= MAX_HEIGHT-1) createNewStack();
      
      stacks[curr_stack].stack->push(value);
      stacks[curr_stack].count++;
    }

    T pop() {
      StackWithCount<T>& stack_info = stacks[curr_stack];
      T val = stack_info.stack->pop();
      stack_info.count--;

      if (stack_info.count == 0) popStack();

      return val;
    }

    bool empty() {
      return stacks[curr_stack].stack->empty();
    }

    T popAt(int i) {
      stacks[i].count--;
      return stacks[i].stack->pop();
    }

  private:
    void popStack() {
      if (curr_stack > 0) {
        cout << "removing stack: " << curr_stack << endl;
        stacks.pop_back();
        curr_stack--;
      }
    }
    void createNewStack() {
      Stack<T>* stack = new Stack<T>();
      stacks.push_back(stack);
      ++curr_stack;
      cout << "createing stack: " << curr_stack << endl;
    }

  private:
    std::vector<StackWithCount<T> > stacks;
    int curr_stack;
};

int main() {
  SetOfStacks<char> stack;
  int start = 'A';
  int end = 'Z';
  for (int i=start; i<end; ++i) {
    stack.push(i);
  }

  stack.popAt(4);
  
  while (!stack.empty()) {
    cout << stack.pop() << endl;
  }

  return 0;
}
