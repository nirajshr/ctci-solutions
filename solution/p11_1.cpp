#include <iostream>

using namespace std;

void printArray(int num[], int start_ind, int end_ind) {
  for (int i=start_ind; i<=end_ind; ++i) {
    cout << num[i] << "  ";
  }
  cout << endl;
}

void swap(int num_array[], int ind1, int ind2) {
  cout << "Swapping indices " << ind1 << " and " << ind2 << endl;
  int temp = num_array[ind1];
  num_array[ind1] = num_array[ind2];
  num_array[ind2] = temp;
}

void mergeSortedArrays(int array1[], int len1, int array2[], int len2){
  if (len2 <= 0) return;

  int curr1 = len1-1;
  int curr2 = len2-1;
  for (int i=len1+len2-1; i>=0; --i) {
    if (curr2 >= 0 && curr1 >= 0) { 
      array1[i] = array2[curr2] > array1[curr1] ? array2[curr2--] : array1[curr1--];
    }
    else if(curr1 >= 0) {
      array1[i] = array1[curr1--];
    }
    else if(curr2 >= 0) {
      array1[i] = array2[curr2--];
    }
  }
}

int main() {
  int num1[] = { 1, 3, 5, 7, 9, 0, 0 ,0 ,0, 0, 0, 0 };
  int num2[] = { 2, 4, 6, 8, 10, 12, 14};

  int len1 = sizeof(num1) / sizeof(int);
  int len2 = sizeof(num2) / sizeof(int);

  printArray(num1, 0, len1-1);
  printArray(num2, 0, len2-1);
  mergeSortedArrays(num1, 5,
                    num2, len2);
  printArray(num1, 0, len1-1);

  return 0;
}
