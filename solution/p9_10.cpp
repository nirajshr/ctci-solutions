#include <iostream>
#include <vector>

using namespace std;

struct Box {
  Box(int w, int d, int h) : width(w), depth(d), height(h) {}

  bool canBeAbove(Box const& box) const {
    return box.width > width && box.depth > depth && box.height > height;
  }

  int width;
  int depth;
  int height;
};

ostream& operator<<(ostream& oss, Box const& box) {
  oss << "[" <<  box.width << " X " << box.depth << " X " << box.height << "]";
  return oss;
}

typedef vector<Box> StackOfBoxes;

ostream& operator<<(ostream& oss, StackOfBoxes const& boxes) {
  for (int i=0; i<boxes.size(); ++i) {
    oss << boxes[i] << "  ";
  }
  return oss;
}

StackOfBoxes getMaxBoxStackR(StackOfBoxes const& boxes, Box const& bottom) {
  cout << "Bottom box " << bottom << endl;
  StackOfBoxes max_boxes;
  int max_height = 0;

  for (int i=0; i<boxes.size(); ++i) {
    if (boxes[i].canBeAbove(bottom)) {
      cout << boxes[i] << " can be above box " << bottom << endl;
      StackOfBoxes next_boxes = getMaxBoxStackR(boxes, boxes[i]);
      cout << "Next boxes -->" << next_boxes << " size=" << next_boxes.size() << endl;
      if (next_boxes.size() >= max_height) {
        max_boxes = next_boxes;
        max_height = next_boxes.size();
      }
    }
  }
  max_boxes.insert(max_boxes.begin(), bottom);

  cout << "------------------------------------------" << endl;
  return max_boxes;
}

StackOfBoxes getMaxBoxStack(StackOfBoxes const& boxes) {
  StackOfBoxes max_boxes = getMaxBoxStackR(boxes, boxes[0]);

  return max_boxes;
}

int main() {
  StackOfBoxes boxes;
  boxes.push_back(Box(20, 20, 20));
  boxes.push_back(Box(10, 10, 10));
  boxes.push_back(Box(10, 10, 5));

  boxes.push_back(Box(2, 1, 9));
  boxes.push_back(Box(5, 5, 3));

  boxes.push_back(Box(2, 2, 5));
  boxes.push_back(Box(1, 1, 1));

  cout << boxes << endl;

  StackOfBoxes max_boxes = getMaxBoxStack(boxes);
  cout << "max box stack" << endl;
  cout << max_boxes << endl;


  return 0;
}
