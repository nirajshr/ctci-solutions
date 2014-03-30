#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef std::string Word;
typedef std::vector<Word> Words;

void printWords(Words const& list) {
  for (int i=0; i<list.size(); ++i) {
    cout << list[i] << ", ";
  }
  cout << endl;
}

struct word_comparator{
  bool operator()(Word const& lhs, Word const& rhs) {
    std::string lhs_copy = lhs;
    std::string rhs_copy = rhs;

    std::sort(lhs_copy.begin(), lhs_copy.end());
    std::sort(rhs_copy.begin(), rhs_copy.end());

    return lhs_copy < rhs_copy;
  }
};

Words sortWords(Words const& words) {
  Words output;
  multiset<Word, word_comparator> word_set;

  for (int i=0; i<words.size(); ++i) {
    word_set.insert(words[i]);
  }

  for (multiset<Word, word_comparator>::const_iterator it = word_set.begin();
       it != word_set.end(); ++it) {
    output.push_back(*it);
  }
  cout << endl;
  return output;
}

int main() {
  Words list;
  list.push_back("tops");
  list.push_back("do");
  list.push_back("post");
  list.push_back("tip");
  list.push_back("mull");
  list.push_back("pit");
  list.push_back("orange");
  list.push_back("stop");
  list.push_back("erango");
  list.push_back("opsu");
  list.push_back("opss");

  printWords(list);
  Words sorted_by_anagram = sortWords(list);
  printWords(sorted_by_anagram);

  return 0;
}
