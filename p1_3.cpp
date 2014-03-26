#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unordered_map<char, int> CharDictionary;

void createCharDict(string const& str, CharDictionary& dict) {
  for(int i=0; i < str.length(); ++i) {
    char char_at_pos = str[i];

    CharDictionary::iterator it = dict.find(char_at_pos);
    if (it == dict.end()) {
      dict[char_at_pos] = 1;
    }
    else {
      (it->second)++;
    }
  }
}

void printDict(CharDictionary const& dict) {
  for(CharDictionary::const_iterator it = dict.begin(); it != dict.end(); ++it) {
    cout << " " << it->first << ":" << it->second;
  }
  cout << endl;
}

bool isPermutationOf(string const& subset, string const& superset) {
  CharDictionary dict;
  createCharDict(superset, dict);

  printDict(dict);

  for(int i=0; i < subset.length(); ++i) {
    char char_at_pos = subset[i];
    CharDictionary::iterator it = dict.find(char_at_pos);

    if (it == dict.end()) {
      return false; 
    } 
    else {
      if (it->second < 1) return false;
      --(it->second);
    }
  }

  return true;
}

int main() {
  const char* superset = "MATERNAL";
  const char* subset = "NATE";
  string subset_input(subset);

  cout << "Enter a subset:";
  getline(std::cin, subset_input);

  bool result = isPermutationOf(subset_input, superset);

  cout << subset_input << " is " << (result ? "" : "not ");
  cout << "a subset of " << superset << endl;

  return 0;
}
