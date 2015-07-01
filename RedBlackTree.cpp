#include "RedBlackTree.hpp"
#include <stack>
#include <utility>
#include <sstream>
#include <iostream>

RedBlackTree::RedBlackTree(int rv) {
  root = new RedBlackNode(rv);
  root->SetColor(true);
}

void RedBlackTree::Insert(int val) {
  // Start with the root node
  std::stack<RedBlackNode *> stk;
  stk.push(root);

  // Insert child by traversing the tree
  while (stk.top() != nullptr) {
    if (stk.top()->Value() == val)
      return;
    bool dir = val > stk.top()->Value();
    stk.push(stk.top()->Child(dir));
  }

  // Insert the newly created child into the tree
  stk.pop();
  bool dir = val > stk.top()->Value();
  RedBlackNode *child = stk.top()->Child(dir) = new RedBlackNode(val);

  // We know that the newly created child will be red, so if its parent is red,
  // we have a problem
  RedBlackNode *parent = stk.top();
  RedBlackNode *grandparent;
  stk.pop();

  while (stk.size() > 0) {
    grandparent = stk.top();
    if (!parent->IsBlack() && !child->IsBlack()) {
      // Fix problems with the tree
      bool parentdir = val > grandparent->Value();
      bool childdir = val > parent->Value();
      if (IsBlackNode(grandparent->Child(!parentdir))) {
        if (childdir != parentdir) {
          FixInside(parent, childdir);
        }
        FixBlackUncle(grandparent, childdir);
      } else {
        FixRedUncle(grandparent, childdir);
      }
    }
    child = parent;
    parent = grandparent;
    stk.pop();
  }
  root->SetColor(true);
}

RedBlackNode *RedBlackTree::Search(int val) {
  // Start with the root node
  RedBlackNode *current = root;
  // Find child by traversing the tree
  while (current != nullptr && current->Value() != val) {
    current = current->Child(val > current->Value());
  }
  return current;
}

void RedBlackTree::Rotate(RedBlackNode *gp, bool dir) {
  if (!gp->Child(dir))
    return;

  // Save the current value
  RedBlackNode grandparent = *gp;
  RedBlackNode parent = *(gp->Child(dir));

  // Save the child connections from the nodes
  RedBlackNode *connectionL = grandparent.Child(!dir);
  RedBlackNode *connectionM = parent.Child(!dir);
  RedBlackNode *connectionR = parent.Child(dir);

  // Copy the old parent node into the grandparent
  gp->Value() = parent.Value();
  gp->SetColor(parent.IsBlack());

  // Use the old dir node as the new !dir node
  gp->Child(!dir) = grandparent.Child(dir);
  // Copy the old grandparent node into the parent
  gp->Child(!dir)->Value() = grandparent.Value();
  gp->Child(!dir)->SetColor(grandparent.IsBlack());

  // Rebind the old connections
  gp->Child(dir) = connectionR;
  gp->Child(!dir)->Child(!dir) = connectionL;
  gp->Child(!dir)->Child(dir) = connectionM;
}

void RedBlackTree::FixRedUncle(RedBlackNode *grandparent, bool dir) {
  grandparent->FlipColor();
  grandparent->Child(!dir)->FlipColor();
  grandparent->Child(dir)->FlipColor();
}

void RedBlackTree::FixBlackUncle(RedBlackNode *grandparent, bool dir) {
  Rotate(grandparent, dir);
  grandparent->FlipColor();
  grandparent->Child(!dir)->FlipColor();
}

void RedBlackTree::FixInside(RedBlackNode *parent, bool dir) {
  Rotate(parent, dir);
}

RedBlackNode *RedBlackTree::Grandchild(RedBlackNode *grandparent, bool dir) {
  if (!grandparent->Child(dir)) {
    return nullptr;
  } else if (!grandparent->Child(dir)->Child(dir)) {
    return nullptr;
  } else {
    return grandparent->Child(dir)->Child(dir);
  }
}

bool RedBlackTree::IsChildSameDir(RedBlackNode *grandparent,
                                  RedBlackNode *child, bool dir) {
  return Grandchild(grandparent, dir) == child;
}

bool RedBlackTree::IsBlackNode(RedBlackNode *node) {
  if (node == nullptr)
    return true;
  else
    return node->IsBlack();
}

std::string RedBlackTree::ToString() {
  std::stringstream ss;
  std::stack<std::pair<RedBlackNode *, int>> stk;
  stk.push(std::make_pair(root, 0));
  while (!stk.empty()) {
    if (stk.top().second == 0) {
      for (int i = 0; i < stk.size(); i++) {
        ss << " ";
      }
      ss << stk.top().first->Value() << ": "
         << (stk.top().first->IsBlack() ? "black" : "red") << '\n';

      stk.top().second++;
      if (stk.top().first->Child(false)) {
        stk.push(std::make_pair(stk.top().first->Child(false), 0));
      }
    } else if (stk.top().second == 1) {
      stk.top().second++;
      if (stk.top().first->Child(true)) {
        stk.push(std::make_pair(stk.top().first->Child(true), 0));
      }
    } else {
      stk.pop();
    }
  }
  return ss.str();
}

/*****************************DEBUG FUNCTIONS********************************
 * THESE FUNCTIONS ARE FOR DEBUGGING PURPOSES ONLY. DO NOT USE THEM IN AN
 * ACTUAL APPLICATION, AS THEY ALL RUN IN O(n) TIME
 ***************************************************************************/

int RedBlackTree::Deepest() {
  std::stack<std::pair<int, RedBlackNode *>> nodeStack;
  int maxDepth = 0;
  nodeStack.push(std::make_pair(0, root));
  while (!nodeStack.empty()) {
    if (nodeStack.top().first == 0) {
      nodeStack.top().first++;
      if (nodeStack.top().second->Child(0)) {
        nodeStack.push(std::make_pair(0, nodeStack.top().second->Child(0)));
      }
    } else if (nodeStack.top().first == 1) {
      nodeStack.top().first++;
      if (nodeStack.top().second->Child(1)) {
        nodeStack.push(std::make_pair(0, nodeStack.top().second->Child(1)));
      }
    } else {
      maxDepth = nodeStack.size() > maxDepth ? nodeStack.size() : maxDepth;
      nodeStack.pop();
    }
  }
  return maxDepth;
}

int RedBlackTree::Shallowest() {
  std::stack<std::pair<int, RedBlackNode *>> nodeStack;
  int minDepth = 0xFFFFFFFF;
  nodeStack.push(std::make_pair(0, root));
  while (!nodeStack.empty()) {
    if (nodeStack.top().first == 0) {
      nodeStack.top().first++;
      if (nodeStack.top().second->Child(0)) {
        nodeStack.push(std::make_pair(0, nodeStack.top().second->Child(0)));
      }
    } else if (nodeStack.top().first == 1) {
      nodeStack.top().first++;
      if (nodeStack.top().second->Child(1)) {
        nodeStack.push(std::make_pair(0, nodeStack.top().second->Child(1)));
      }
    } else {
      if (nodeStack.top().second->Child(0) == nullptr &&
          nodeStack.top().second->Child(1) == nullptr) {
        minDepth = nodeStack.size() < minDepth ? nodeStack.size() : minDepth;
      }
      nodeStack.pop();
    }
  }
  return minDepth;
}

/* END DEBUGGING */
