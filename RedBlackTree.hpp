#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include "BinarySearchTree.hpp"
#include "Node.hpp"

#include <string>

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

class RedBlackTree : public BinarySearchTree {
public:
  RedBlackTree(int root);
  void Insert(int val);
  RedBlackNode *Search(int val);
  std::string ToString();
  int Deepest();
  int Shallowest();

private:
  void Rotate(RedBlackNode *parent, bool dir);
  void FixRedUncle(RedBlackNode *parent, bool dir);
  void FixBlackUncle(RedBlackNode *parent, bool dir);
  void FixInside(RedBlackNode *parent, bool dir);
  bool IsChildSameDir(RedBlackNode *grandparent, RedBlackNode *child, bool dir);
  bool IsBlackNode(RedBlackNode *node);
  RedBlackNode *Grandchild(RedBlackNode *grandparent, bool dir);
  RedBlackNode *root;
};

#endif
