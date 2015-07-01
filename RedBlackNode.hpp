#ifndef REDBLACKNODE_HPP
#define REDBLACKNODE_HPP

#include "Node.hpp"

class RedBlackNode : public Node {
public:
  RedBlackNode(int value);
  bool IsBlack();
  void SetColor(bool b);
  bool FlipColor();
  RedBlackNode *&Child(bool dir);

private:
  bool black;
};

#endif
