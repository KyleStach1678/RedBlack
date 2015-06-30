#include "Node.hpp"

#include <iostream>

int main() {
  Node *root = new Node(1);
  for (int i = 2; i <= 100; i++) {
    root->Insert(i);
    if (!root->IsBlack())
      root->FlipColor();
  }

  bool allFound = true;
  for (int i = 0; i <= 100; i++) {
    allFound = allFound && root->Search(i) != nullptr;
  }
  std::cout << root->ToString() << std::endl;
  std::cout << allFound << std::endl;
  std::cout << root->Search(30) << std::endl;
}
