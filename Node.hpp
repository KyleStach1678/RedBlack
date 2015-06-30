#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node {
public:
  Node(int val);
  int Insert(int val);
  bool IsBlack();
  int Value();
  Node *Child(bool dir);
  void Rotate(bool dir);
  std::string ToString(int depth = 0);
  void FlipColor();
  Node *Search(int val);

private:
  int value;
  bool black;
  Node *children[2];
};

#endif
