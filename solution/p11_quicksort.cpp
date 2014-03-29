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

int partition(int num_array[], int left_ind, int right_ind) {
  int pivot = num_array[(left_ind + right_ind) / 2];

  while (left_ind <= right_ind) {
    while (num_array[left_ind] < pivot) left_ind++;
    while (num_array[right_ind] > pivot) right_ind--;

    if (left_ind <= right_ind) {
      swap(num_array, left_ind, right_ind);
      left_ind++;
      right_ind--;
    }
  }

  return left_ind;
}

void quick_sortR(int num_array[], int left_ind, int right_ind) {
  int index = partition(num_array, left_ind, right_ind);
  cout << "Mid: " << index << endl;
  if (left_ind < index - 1) {
    quick_sortR(num_array, left_ind, index-1);
  }

  if (index < right_ind) {
    quick_sortR(num_array, index, right_ind);
  }
}

void quick_sort(int num_array[], int len) {
  quick_sortR(num_array, 0, len-1);
}


int main() {
  int num[] = {2, 0, 1, 20, 7, 5, 9, 6, 18};
  int len = sizeof(num) / sizeof(int);

  printArray(num, 0, len-1);
  quick_sort(num, len);
  printArray(num, 0, len-1);


  return 0;
}
