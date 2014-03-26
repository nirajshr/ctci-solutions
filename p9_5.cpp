#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef set<char> Charset;
typedef vector<Charset> Charsets;

void printSet(Charset const& set) {
  for (Charset::const_iterator it = set.begin(); it != set.end(); ++it) {
    cout << *it << "  ";
  }
  cout << endl;
}

Charsets findSubsets2(Charset& letters) {
  int size = letters.size();
  if (size == 0) {
    Charset empty_set;
    Charsets subsets; subsets.push_back(empty_set);
    return subsets;
  }
  else {
    char letter = *letters.begin();
    letters.erase(letters.begin());
    
    Charsets subsets = findSubsets2(letters);
    Charsets mysubsets(subsets);

    for (int i=0; i<subsets.size(); ++i) {
      subsets[i].insert(letter);
      mysubsets.push_back(subsets[i]);
    }
    return mysubsets;
  }
}

void printWordList(vector<string> const& word_list) {
  for (int i=0; i<word_list.size(); ++i) {
    cout << word_list[i] << "  ";
  }
  cout << endl;
}

vector<string> findAllPermutation(string word) {
  cout << "called for:" << word << endl;
  vector<string> word_list;
  if (word.length() == 1) {
    word_list.push_back(word);
  }
  else if (word.length() > 1) {
    string sub_word(next(word.begin(), 1), word.end());
    vector<string> sub_word_list = findAllPermutation(sub_word);
    printWordList(sub_word_list);
      for(int i=0; i<sub_word_list.size(); ++i) {
        string& curr_word = sub_word_list[i];
        for (int j=0; j<curr_word.length()+1; ++j) {
          string first_part = curr_word.substr(0, j);
          string last_part = curr_word.substr(j);
          string new_word = first_part + *word.begin() + last_part;
          word_list.push_back(new_word);
        }
      }
  }

  return word_list;
}

int main() {
  string word("MonK");

  vector<string> word_list = findAllPermutation(word);

  cout << "Permuation" << endl;
  printWordList(word_list);

  return 0;
}
