#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node {
public:
  Node(int val);
  Node *&Child(bool dir);
  int &Value();

protected:
  int value;
  Node *children[2];
};

#endif
