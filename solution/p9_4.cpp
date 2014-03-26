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

void findSubsetsImpl(Charset const& letters, Charset::const_iterator start_it, Charset& curr_subset, Charsets& agg_subsets) {
  if (start_it == letters.end()) return;

  Charset::const_iterator it = start_it;
  curr_subset.insert(*it);
  agg_subsets.push_back(curr_subset);

  for(++it; it != letters.end(); ++it) {
    Charset next_subset(curr_subset);
    findSubsetsImpl(letters, it, next_subset, agg_subsets);
  }
}

void findSubsets(Charset const& letters) {
  Charsets agg_subsets;

  for (Charset::const_iterator it = letters.begin(); it != letters.end(); ++it) {
    Charset curr_subset;
    findSubsetsImpl(letters, it, curr_subset, agg_subsets);
  }

  cout << "Subsets" << endl;
  for (int i=0; i<agg_subsets.size(); ++i) {
    printSet(agg_subsets[i]);
  }
}

int main() {
  char foo[] = {'A', 'B', 'C'};
  Charset letters(foo, foo + sizeof(foo)/sizeof(char));  

  findSubsets(letters);

  cout << "Method#2" << endl;
  Charsets subsets = findSubsets2(letters);
  for (int i=0; i<subsets.size(); ++i) {
    printSet(subsets[i]);
  }

  return 0;
}
