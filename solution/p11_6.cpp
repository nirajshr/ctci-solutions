/*
 *  Not completed ...just rough idea placement
 */
#include "../includes/utilities.h"

#include <iostream>
#include <vector>

using namespace std;

typedef std::vector<int> IntVec;
typedef std::vector<IntVec> Matrix;

void printMatrix(Matrix const& matrix) {
  for (int i=0; i<matrix.size(); ++i) {
    CTCI::printVec(matrix[i]);
  }
}

bool binarySearch(IntVec const& vec, int left, int right, int target) {
  if (left < right) {
    int mid = (left + right ) / 2;  

    int rotated_ind = mid;
    if (target < vec[rotated_ind]) {
      return binarySearch(vec, left, mid, target);
    }
    else if (target > vec[rotated_ind]) {
      return binarySearch(vec, mid+1, right, target);
    }

    return true;
  }
  else if (left == right) {
    int rotated_ind = left;
    return target == vec[rotated_ind];
  }

  return false;
}

int findRow(Matrix const& matrix, int top, int bottom, int target) {
  cout << "findRow top: " << top << ", bottom: " << bottom << endl;
  if (top > bottom) return -1;

  int row_size = matrix[0].size();

  int mid = ( top + bottom ) / 2;
  cout << "mid: " << mid << endl;
  if (target < matrix[mid][0]) {
    return findRow(matrix, top, mid, target);
  }
  else if (target > matrix[mid][row_size-1]) {
    return findRow(matrix, mid+1, bottom, target);
  }
  return mid;
}

void findTarget(Matrix const& matrix, int target) {
  int row = findRow(matrix, 0, matrix.size()-1, target);

  cout << "Row: " << row << endl;
}

int main() {
  Matrix matrix;

  int nums[][4] = {
    { 1,   2,  3,  4 },
    { 5,   6,  7,  8 },
    { 10, 11, 20, 25 },
    { 15, 16, 21, 26 }
  };

  for (int row=0; row < sizeof(nums) / sizeof(nums[0]); ++row) {
    IntVec vec(nums[row], nums[row] + sizeof(nums[row]) / sizeof(int));
    matrix.push_back(vec);
  }

  int input_num;
  cout << "Input a num: ";
  cin >> input_num;

  printMatrix(matrix);
  findTarget(matrix, input_num);

  return 0;
}
