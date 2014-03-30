#include "../includes/utilities.h"

#include <iostream>
#include <vector>

using namespace std;

typedef std::vector<int> IntVec;

struct RotatedIndex {
  RotatedIndex(IntVec const& vec) {
    size = vec.size();
    shift = findRotatedIndex(vec);
  }

  int getRotatedIndex (int index) const {
    return ( index + shift ) % size;
  }

  static int findRotatedIndex(IntVec const& vec) {
    if (vec.size() < 1) return 0;
    int prev_val = vec[0];
    for (int i=1; i<vec.size(); ++i) {
      int curr_val = vec[i];
      if (prev_val > curr_val) return i;
      prev_val = curr_val;
    }

    return 0;
  }

  int size;
  int shift;
};

bool binarySearch(IntVec const& vec, int left, int right, int target, RotatedIndex const& rotation) {
  if (left < right) {
    int mid = (left + right ) / 2;  

    int rotated_ind = rotation.getRotatedIndex(mid);
    if (target < vec[rotated_ind]) {
      return binarySearch(vec, left, mid, target, rotation);
    }
    else if (target > vec[rotated_ind]) {
      return binarySearch(vec, mid+1, right, target, rotation);
    }

    return true;
  }
  else if (left == right) {
    int rotated_ind = rotation.getRotatedIndex(left);
    return target == vec[rotated_ind];
  }

  return false;
}

bool findNum(IntVec const& vec, int target) {
  RotatedIndex rotation(vec);
  cout << "Rotation shift: " << rotation.shift << endl;

  return binarySearch(vec, 0, vec.size()-1, target, rotation);
}

int main() {
  //int nums[] = {1, 3, 4, 5, 7, 10, 14, 15, 16, 19, 20, 25};
  int nums[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
  int nums_len = sizeof(nums) / sizeof(int);
  //int nums2_len = sizeof(nums2) / sizeof(int);

  IntVec vec(nums, nums + nums_len);
  CTCI::printVec(vec);

  int input_num;
  cout << "Enter a num to find in the above raneg:";
  cin >> input_num;
  bool ret = findNum(vec, input_num);

  if (ret) cout << "Found it!" << endl;
  else cout << "Not Found" << endl;

  return 0;
}
