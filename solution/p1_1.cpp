#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef std::string String;

bool hasUniqueChars(String str) {
  sort(str.begin(), str.end());
  for (String::const_iterator it = str.begin(), prev = str.begin(); it != str.end(); ++it) {
    if (it != str.begin()) {
      if (*it == *prev) return false;
    }

    prev = it;
  }
  
  return true;
}

int main() {

  const char* str = "A quick brown fox jumped.";
  const char* str2 = "Mot pin";

  std::cout << str << endl << hasUniqueChars(str) << endl << endl;
  std::cout << str2 << endl << hasUniqueChars(str2) << endl << endl;

  return 0;
}
