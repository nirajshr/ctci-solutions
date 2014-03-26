#include <iostream>
#include <string>
#include <vector>

using namespace std;

const char SPACE = ' ';

size_t countCharOccurance(string const& str, char c) {
  size_t count = 0;
  for (string::const_iterator it=str.begin(); it != str.end(); ++it) {
    if (*it == c) ++count;
  }
  return count;
}

void replaceSpaces(string& str, size_t len) {
  int space_cnt = countCharOccurance(str.substr(0, len), ' ');

  for (int i=len-1; i>=0; --i) {
    size_t movement_cnt = space_cnt * 2;
    size_t target_ind = i + movement_cnt;

    char char_at_pos = str[i];
    if (char_at_pos == SPACE) {
      str[target_ind] = '0'; 
      str[target_ind-1] = '2'; 
      str[target_ind-2] = '%'; 

      --space_cnt;
      if (space_cnt < 0) space_cnt = 0;
    }
    else {
      str[target_ind] = char_at_pos;
    }
  }

}

int main() {
  const char* sentence = " Mr John Smith";

  string buffer(sentence);
  size_t len = buffer.length();

  buffer.append("       ");

  cout << "'" << buffer << "'" << endl;

  replaceSpaces(buffer, len);

  cout << "'" << buffer << "'" << endl;


  return 0;
}
