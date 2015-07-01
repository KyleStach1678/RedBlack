#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include "BinarySearchTree.hpp"
#include "RedBlackNode.hpp"

#include <string>

class RedBlackTree : public BinarySearchTree {
public:
  RedBlackTree(int root);
  void Insert(int val);

  // Search for a specific node
  RedBlackNode *Search(int val);

  // Get a string representation of the tree (Debugging)
  std::string ToString();
  // Find the depth of the deepest leaf node (Debugging)
  int Deepest();
  // Find the depth of the shallowest leaf node (Debugging)
  int Shallowest();

private:
  // Perform a tree rotate, moving the child in direction dir to the parent
  void Rotate(RedBlackNode *parent, bool dir);

  // Fix the red parent, red child case where the parent's sibling is red by
  // recoloring the grandparent, parent, and uncle nodes
  void FixRedUncle(RedBlackNode *grandparent, bool dir);

  // Fix the red parent, red child case where the parent's sibling is black and
  // the child and the parent are both either left or right children
  void FixBlackUncle(RedBlackNode *parent, bool dir);

  // Fix the red parent, red child case where the parent's sibling is black and
  // the child is in the opposite direction from the parent by rotating around
  // the parent. Note: you must call FixBlackUncle afterwards
  void FixInside(RedBlackNode *parent, bool dir);

  // Check if the child and its parent are both children in the direction of dir
  bool IsChildSameDir(RedBlackNode *grandparent, RedBlackNode *child, bool dir);

  // Check if the node is black - null nodes also count as black
  bool IsBlackNode(RedBlackNode *node);

  // Get the node's grandchild in direction dir twice
  RedBlackNode *Grandchild(RedBlackNode *grandparent, bool dir);

  // The root of the tree;
  RedBlackNode *root;
};

#endif
