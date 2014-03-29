#include <iostream>
#include <stack>

using namespace std;

typedef stack<int> IntStack;

void printArray(int num[], int start_ind, int end_ind) {
  for (int i=start_ind; i<=end_ind; ++i) {
    cout << num[i] << "  ";
  }
  cout << endl;
}

void swap2(int num_array[], int ind1, int ind2) {
  num_array[ind1] |= num_array[ind2];
  num_array[ind2] |= num_array[ind1];
  num_array[ind1] |= num_array[ind2];
}

void swap(int num_array[], int ind1, int ind2) {
  cout << "Swapping indices " << ind1 << " and " << ind2 << endl;
  int temp = num_array[ind1];
  num_array[ind1] = num_array[ind2];
  num_array[ind2] = temp;
}

void copyArray(int source[], int start_ind, int end_ind, IntStack& stack) {
  for (int i=end_ind; i>=start_ind; --i) {
    stack.push(source[i]);
  }
}

void merge(int num_array[], int left_ind1, int right_ind1, int left_ind2, int right_ind2) {
  IntStack left_stack, right_stack;

  copyArray(num_array, left_ind1, right_ind1, left_stack);
  copyArray(num_array, left_ind2, right_ind2, right_stack);
  
  int curr=left_ind1;
  while (!left_stack.empty() && !right_stack.empty()) {
    if (left_stack.top() < right_stack.top()) {
      num_array[curr] = left_stack.top();
      left_stack.pop();
    }
    else {
      num_array[curr] = right_stack.top();
      right_stack.pop();
    }
    curr++;
  }

  while (!left_stack.empty()) {
    num_array[curr++] = left_stack.top();
    left_stack.pop();
  }
  //No need to do this. as its already in place
  /*
  while (!right_stack.empty()) {
    num_array[curr++] = right_stack.top();
    right_stack.pop();
  }
  */
}

void merge_sortR(int num_array[], int left_ind, int right_ind) {
  cout << "Looking at index " << left_ind << " to " << right_ind << ", Array "; 
  printArray(num_array, left_ind, right_ind);

  if (right_ind-left_ind == 1) {
    cout << "Two elem array" << endl;
    if (num_array[left_ind] > num_array[right_ind]) {
      swap(num_array, left_ind, right_ind);
    }
  }
  else if (right_ind-left_ind > 1){
    cout << "split array" << endl;
    int mid = (left_ind + right_ind+1 ) / 2;
    merge_sortR(num_array, left_ind, mid-1);
    merge_sortR(num_array, mid, right_ind);

    cout << "Merging segment (" << left_ind << "," << mid-1 << ") and (" << mid << "," << right_ind << ")" << endl;
    cout << "After Merge: ";
    merge(num_array, left_ind, mid-1, mid, right_ind);
    printArray(num_array, left_ind, right_ind);
  }
}

void merge_sort(int num_array[], int len) {
  merge_sortR(num_array, 0, len-1);
}


int main() {
  int num[] = {5, 1, 19, 3, 2, 9};
  int num2[] = {5, 1, 19, 3, 2, 9};
  int len = sizeof(num) / sizeof(int);

  printArray(num, 0, len-1);
  merge_sort(num, len);
  printArray(num, 0, len-1);


  return 0;
}
