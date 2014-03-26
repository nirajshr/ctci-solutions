#include <iostream>
#include <string>
#include <sstream>
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

string compressString(string& str) {
  if (str.length() < 2) return str;

  ostringstream oss;
  bool saving = false;

  char prev = str[0];
  int char_cnt = 1;
  for (int i=1; i<str.length(); ++i) {
    int curr_char = str[i];
    if (curr_char != prev) {
      oss << prev;
      if (char_cnt > 1) oss << char_cnt;
      char_cnt = 1;
      saving = true;
    }
    else {
      char_cnt++;
    }
    prev = curr_char;
  }

  oss << prev;
  if (char_cnt > 1) oss << char_cnt;

  return saving ? oss.str() : str;
}

int main() {
  const char* sentence = "aabcbbbbaaaccb";

  string buffer(sentence);

  cout << "Enter a sentence:";
  getline(std::cin,  buffer);

  cout << "'" << buffer << "'" << endl;

  string compressed = compressString(buffer);

  cout << "'" << compressed  << "'" << endl;


  return 0;
}
