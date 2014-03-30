#include <iostream>
#include <vector>

namespace CTCI {

template <typename T>
void printVec(std::vector<T> const& vec) {
  for (typename std::vector<T>::const_iterator it=vec.begin();
       it != vec.end(); ++it) {
    std::cout << *it;
    if (it != vec.end() -1) std::cout << ", ";
  }
  std::cout << std::endl;
}

};
