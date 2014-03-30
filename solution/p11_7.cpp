#include <iostream>
#include <vector>

using namespace std;

struct Person {
  Person() {};
  Person(int h, int w) : height(h), weight(w) {}

  bool canWithStand(Person const& p) const {
    return (height > p.height && weight > p.weight);
  }
  int height;
  int weight;
};

typedef vector<Person> Tower;

int towerHeightR(Person const& person, Tower const& tower) {
  int ht = 0;
  for (int i=0; i<tower.size(); ++i) {
    if (person.canWithStand(tower[i])) ht++;
  }

  return ht;
}

int maxTowerHeight(Tower const& tower) {
  if (tower.size() < 1) return 0;

  int max_ht = 1;

  for (int i=0; i<tower.size(); ++i) {
    int ht = towerHeightR(tower[i], tower);
    if (ht > max_ht) max_ht = ht;
  }

  return max_ht;
}

int main() {
  Tower tower;
  tower.push_back(Person(65, 100));
  tower.push_back(Person(70, 150));
  tower.push_back(Person(56, 90));
  tower.push_back(Person(75, 190));
  tower.push_back(Person(60, 95));
  tower.push_back(Person(68, 110));

  int height = maxTowerHeight(tower);
  cout << "Max tower ht: " << height << endl;

  return 0;
}
