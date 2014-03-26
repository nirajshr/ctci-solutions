#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> Path;

void printVec(Path const& path) {
  for (int i=0; i<path.size(); ++i) {
    cout << path[i] << " ";
  }

  cout << endl;
}

void climbStairsImpl(int total_steps, vector<int> strides, Path& path_log, vector<Path>& agg_success_paths) {
  if (total_steps == 0) {
    agg_success_paths.push_back(path_log);
  }

  for (int i=0; i<strides.size(); ++i) {
    Path curr_path(path_log);
    if (total_steps - strides[i] >= 0) {
      curr_path.push_back(strides[i]);
      climbStairsImpl(total_steps-strides[i], strides, curr_path, agg_success_paths);
    }
  }
}

void climbStairs(int total_steps, vector<int> const& strides) {
  vector<Path> agg_success_paths;;
  Path empty_path;

  climbStairsImpl(total_steps, strides, empty_path, agg_success_paths);

  cout << "Possible steps:" << endl;
  for (int i=0; i<agg_success_paths.size(); ++i) {
    printVec(agg_success_paths[i]);
  }
}

int countStairsSteps(int n) {
  if (n < 0) {
    return 0;
  }
  else if (n == 0) {
    return 1;
  }
  else {
    return countStairsSteps(n - 3) + countStairsSteps(n - 2) + countStairsSteps(n -1);
  }
}

int main() {
  int total_steps = 15;
  int strides_arr [] = {1, 7, 10};
  vector<int> strides(strides_arr, strides_arr + sizeof(strides_arr) / sizeof(int));

  climbStairs(total_steps, strides);

  cout << "countStairsSteps(4) " << countStairsSteps(4) << endl;

  return 0;
}
