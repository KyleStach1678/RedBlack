#include "RedBlackNode.hpp"

RedBlackNode::RedBlackNode(int val) : Node::Node(val) {
  black = false;
  children[0] = nullptr;
  children[1] = nullptr;
}

bool RedBlackNode::IsBlack() { return black; }

void RedBlackNode::SetColor(bool c) { black = c; }

bool RedBlackNode::FlipColor() { return black = !black; }

RedBlackNode *&RedBlackNode::Child(bool dir) {
  return (RedBlackNode *&)children[dir];
}
