#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isRotation(string rotated, string original) {
  int i=0, rot_ind = 0, num_matched = 0, mismatch = 0, len = rotated.length();

  while (num_matched < len &&  mismatch < len) {
    if (original[i] == rotated[rot_ind]) {
      num_matched++;
      ++i;
    }
    else {
      if (num_matched > 0) --rot_ind;
      num_matched = 0;
      mismatch++;
      i = 0;
    }

    ++rot_ind;
    rot_ind = rot_ind  % len;
  };

  if (num_matched == original.length()) return true;
  return false;
}

int main() {
  const char* sentence = "WATERWAT";

  cout << isRotation("WATWATER", sentence) << endl;
  cout << isRotation("WATERWAT", sentence) << endl;
  cout << isRotation("WATWATE!", sentence) << endl;

  return 0;
}
