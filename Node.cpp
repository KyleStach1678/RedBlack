#include "Node.hpp"

#include <sstream>
#include <iostream>

Node::Node(int val) {
  value = val;
  children[0] = nullptr;
  children[1] = nullptr;
}

Node *&Node::Child(bool dir) { return children[dir]; }
int &Node::Value() { return value; }
