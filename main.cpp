#include "RedBlackTree.hpp"

#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>

int main(int argc, char **argv) {
  RedBlackTree *rbt = new RedBlackTree(1);
  rbt->Insert(1);

  int numElements = (argc > 1 ? std::atoi(argv[1]) : 1000000);

  std::clock_t start = std::clock();
  for (int i = 2; i <= numElements; i++) {
    rbt->Insert(std::rand() % (numElements * 10));
    std::cout << rbt->ToString() << std::endl;
    std::cout << "---------------------------" << std::endl;
  }
  // double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
  // std::cout << "Done inserting " << numElements << " elements. Insertion took
  // "
  //           << duration << " seconds. That is equal to "
  //           << numElements / duration << " insertions per second.\n"
  //           << std::endl;
  //
  // bool foundAll = true;
  // start = std::clock();
  // for (int i = 2; i <= numElements; i++) {
  //   foundAll = foundAll && (rbt->Search(i) != nullptr);
  // }
  // duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
  //
  // std::cout << "Done searching " << numElements << " elements, "
  //           << (foundAll ? "found all" : "did not find all")
  //           << " elements. Search took " << duration
  //           << " seconds. That is equal to " << numElements / duration
  //           << " searches per second.\n" << std::endl;
  std::cout << rbt->Deepest() << std::endl;
  std::cout << rbt->Shallowest() << std::endl;
}
