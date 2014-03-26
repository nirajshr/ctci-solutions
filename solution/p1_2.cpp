#include <iostream>
#include <string>
#include <vector>

using namespace std;

void reverse(char* str) {
  size_t len = 0;
  char* start = str;
  while (*(start++) != '\0') {
    ++len;
  };

  if (len < 1) return;

  size_t l = 0;
  size_t r = len - 1;

  while (l < r) {
    char temp = str[l];
    str[l] = str[r];
    str[r] = temp;

    ++l; --r;
  };
}

int main() {
  const char* sentence = "A sample string";
  string str(sentence);

  reverse(&str[0]);

  cout << "Reverse of :" << sentence << endl;
  cout << "is" << endl << str << endl;

  return 0;
}
