#include "Node.hpp"

#include <sstream>
#include <iostream>

Node::Node(int val) {
  value = val;
  children[0] = nullptr;
  children[1] = nullptr;
  black = false;
}

int Node::Insert(int val) {
  if (val == Value())
    return 0;
  bool dir = val > Value();
  if (!children[dir]) {
    children[dir] = new Node(val);
    int code = 0;
    if (!IsBlack()) {
      return 1;
    }
  } else {
    int code = children[dir]->Insert(val);
    if (code == 1) {
      if (!children[!dir]) {
        Rotate(dir);
      } else if (children[!dir]->IsBlack()) {
        Rotate(dir);
      } else {
        FlipColor();
        children[dir]->FlipColor();
        children[!dir]->FlipColor();
        return 2;
      }
    }
    if (code == 2) {
      return 1;
    }
    return 0;
  }
}

Node *Node::Search(int val) {
  if (Value() == val)
    return this;
  else if (children[val > Value()])
    return children[val > Value()]->Search(val);
  else
    return nullptr;
}

Node *Node::Child(bool dir) { return children[dir]; }

bool Node::IsBlack() { return black; }

int Node::Value() { return value; }

void Node::FlipColor() { black = !black; }

void Node::Rotate(bool dir) {
  if (!children[dir])
    return;

  // Save the current value
  Node grandparent = *this;
  Node parent = *(this->children[dir]);

  this->children[!dir] = grandparent.children[dir];
  this->children[!dir]->value = grandparent.Value();
  this->children[!dir]->children[!dir] = grandparent.children[!dir];
  this->children[!dir]->children[dir] = nullptr;
  this->children[!dir]->black = grandparent.IsBlack();
  this->children[!dir]->children[dir] = parent.children[!dir];

  this->children[dir] = parent.children[dir];

  this->value = parent.Value();
  this->black = parent.IsBlack();

  this->FlipColor();
  children[!dir]->FlipColor();
}

std::string Node::ToString(int depth) {
  std::stringstream ret;
  for (int i = 0; i < depth; i++) {
    ret << "--";
  }
  ret << Value() << (black ? ": black" : ": red") << '\n';
  if (children[0]) {
    ret << children[0]->ToString(depth + 1);
  }
  if (children[1]) {
    ret << children[1]->ToString(depth + 1);
  }
  return ret.str();
}
